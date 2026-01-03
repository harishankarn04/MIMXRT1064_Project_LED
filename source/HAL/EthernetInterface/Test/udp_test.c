/**
 * @file    udp_test.c
 * @brief   UDP test application with 3 server ports and 1 client.
 *
 * This test demonstrates UDP communication using three servers and a client.
 * Upon receiving a packet on any server, all three servers respond to the sender.
 *
 * (C) Copyright Centum T&S Group 2025. All rights reserved.
 * This computer program may not be used, copied, distributed, translated, transmitted or assigned
 * without the prior written authorization of Centum T&S Group.
 */

//------------------------------------ [ INCLUDE FILES ] ----------------------------


#include <HAL/EthernetInterface/Ethernet.h>
#include <HAL/EthernetInterface/protocols/udp.h>

#include "lwip/init.h"
#include "lwip/netif.h"
#include "lwip/timeouts.h"
#include "lwip/udp.h"
#include "lwip/ip_addr.h"
#include "lwip/pbuf.h"
#include "netif/ethernet.h"
#include <stdio.h>
#include <string.h>


//------------------------------------ [ DEFINES ] ----------------------------------

#define SERVER_PORT1 1234
#define SERVER_PORT2 SERVER_PORT1+1
#define SERVER_PORT3 SERVER_PORT1+2
#define TEST_MESSAGE "Hello from UDP test!"

#define TEST_MESSAGE1 "Hello from Server1"
#define TEST_MESSAGE2 "Hello from Server2"
#define TEST_MESSAGE3 "Hello from Server3"

//------------------------------------ [ STATIC VARIABLES ] -------------------------

static struct udp_pcb *psServerPcb1 = NULL;
static struct udp_pcb *psServerPcb2 = NULL;
static struct udp_pcb *psServerPcb3 = NULL;

#define CLIENT_PORT 6000
static struct udp_pcb *psClientPcb;
static ip_addr_t sClientIPaddr;
uint8_t gubDataRxed = 0;
uint32_t gulPacketNumber = 0;

//------------------------------------ [ LOCAL FUNCTIONS ] --------------------------

/**
 * @brief Callback function for receiving UDP packets on any server.
 *
 * This function is registered with each server PCB to process
 * incoming UDP packets and remember the sender's IP address.
 *
 * @param arg     User argument (unused).
 * @param psPcb    Pointer to the UDP PCB.
 * @param psBuf       Pointer to the received pbuf.
 * @param addr    Pointer to the sender's IP address.
 * @param port    Sender's port number.
 */
static void UDPTestReceiveCallback(void *arg, struct udp_pcb *psPcb, struct pbuf *psBuf, const ip_addr_t *psAddr, u16_t port)
{
    if (psBuf != NULL)
    {
        PRINTF("\r\n[RECEIVED] From %s:%d | Length: %d | Data: %s\r\n",
               ipaddr_ntoa(psAddr), port, psBuf->len, (char *)psBuf->payload);

        gubDataRxed = 1;

        sClientIPaddr = *psAddr;

        pbuf_free(psBuf);
    }
}

//------------------------------------ [ GLOBAL FUNCTIONS ] -------------------------

/**
 * @brief Initializes three UDP servers and one UDP client.
 *
 * Each server binds to a different port. A common receive
 * callback is registered. Client PCB is used to send responses.
 */
void UDPTestinit(void)
{
	PRINTF("\r\nInitializing UDP test\r\n");
	psClientPcb = udp_new();
	if (psClientPcb == NULL)
	{
		PRINTF("\r\nFailed to create client PCB\n");
		return;
	}

    psServerPcb1 = UDP_ServerInit(IP_ADDR_ANY, SERVER_PORT1, UDPTestReceiveCallback, NULL);
    psServerPcb2 = UDP_ServerInit(IP_ADDR_ANY, SERVER_PORT2, UDPTestReceiveCallback, NULL);
    psServerPcb3 = UDP_ServerInit(IP_ADDR_ANY, SERVER_PORT3, UDPTestReceiveCallback, NULL);

    if (psServerPcb1 == NULL)
    {
        PRINTF("\r\nFailed to initialize UDP Server on port %d\n", SERVER_PORT1);
        return;
    }

    if (psServerPcb2 == NULL)
    {
        PRINTF("\r\nFailed to initialize UDP Server on port %d\n", SERVER_PORT2);
        return;
    }

    if (psServerPcb3 == NULL)
    {
        PRINTF("\r\nFailed to initialize UDP Server on port %d\n", SERVER_PORT3);
        return;
    }
}

/**
 * @brief Periodically sends UDP messages if data was received.
 *
 * For every packet received on any server, all three servers send
 * a message back to the sender IP using the stored client PCB.
 */
void UDPTestHandler(void)
{
    if (gubDataRxed)
    {
    	if(psServerPcb1)
    	{
    		char Msg[128];
    		snprintf(Msg, sizeof(Msg), "Pkt#%lu: %s", gulPacketNumber++, TEST_MESSAGE1);
    		UDP_Send(psServerPcb1, &sClientIPaddr, CLIENT_PORT, Msg, strlen(Msg));
    	}
		if (psServerPcb2)
		{
			char Msg[128];
			snprintf(Msg, sizeof(Msg), "Pkt#%lu: %s", gulPacketNumber++, TEST_MESSAGE2);
			UDP_Send(psServerPcb2, &sClientIPaddr, CLIENT_PORT, Msg, strlen(Msg));

		}
		if (psServerPcb3)
		{
			char Msg[128];
			snprintf(Msg, sizeof(Msg), "Pkt#%lu: %s", gulPacketNumber++, TEST_MESSAGE3);
			UDP_Send(psServerPcb3, &sClientIPaddr, CLIENT_PORT, Msg, strlen(Msg));

		}
    	gubDataRxed = 0;
    }



}
