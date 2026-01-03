/**
 * @file    igmp_test.c
 * @brief   Test implementation for IGMP multicast communication.
 *
 * This file demonstrates initializing and using multicast with IGMP and UDP.
 * It listens to a multicast group, receives messages, and echoes them back.
 *
 * (C) Copyright Centum T&S Group 2025. All rights reserved.
 * This computer program may not be used, copied, distributed, translated, transmitted or assigned
 * without the prior written authorization of Centum T&S Group.
 */

//------------------------------------ [ INCLUDE FILES ] ----------------------------


#include <HAL/EthernetInterface/Ethernet.h>
#include <HAL/EthernetInterface/protocols/igmp.h>

#include "lwip/ip_addr.h"
#include "lwip/init.h"
#include "lwip/netif.h"
#include "lwip/timeouts.h"
#include "lwip/udp.h"
#include "lwip/ip_addr.h"
#include "lwip/pbuf.h"
#include <string.h>

//---------------------------------------- [ DEFINES ] ------------------------------

#define MULTICAST_GROUP_IP  "239.1.1.1"
#define MULTICAST_PORT      5000
#define MULTICAST_TEST_MSG       "Hello Multicast Group!"

//---------------------------------- [ STATIC VARIABLE ] ----------------------------

static ip_addr_t sMulitcastIP;

//----------------------------------- [ LOCAL FUNCTIONS ] ---------------------------

/**
 * @brief Callback to handle received multicast messages.
 *
 * This function prints the received message and echoes it back to the sender.
 *
 * @param arg   Unused user argument.
 * @param psPcb   UDP PCB for the multicast.
 * @param psBuf     Pointer to received pbuf.
 * @param psAddr  Sender's IP address.
 * @param usPort  Sender's port number.
 */
void CustomMulticastReceive(void *arg, struct udp_pcb *psPcb, struct pbuf *psBuf, const ip_addr_t *psAddr, u16_t usPort)
{
    if (psBuf != NULL)
    {
        PRINTF("Received multicast packet: '%.*s' from %s:%d\r\n", psBuf->tot_len, (char *)psBuf->payload, ipaddr_ntoa(psAddr), usPort);

        err_t ubErr = udp_sendto(psPcb, psBuf, psAddr, usPort);
        if (ubErr == ERR_OK)
        {
            PRINTF("Echoed back to %s:%d\r\n", ipaddr_ntoa(psAddr), usPort);
        }
        else
        {
            PRINTF("Failed to echo: %d\r\n", ubErr);
        }

        pbuf_free(psBuf);
    }
}

//---------------------------------- [ GLOBAL FUNCTIONS ] ---------------------------

/**
 * @brief Initializes multicast IP, UDP, and joins the multicast group.
 */
void MulticastInit(void)
{

	ipaddr_aton(MULTICAST_GROUP_IP, &sMulitcastIP);
	IGMP_MulticastUDPInit(&gsNetif, &sMulitcastIP, MULTICAST_PORT, CustomMulticastReceive, NULL);
	IGMP_JoinGroup(&gsNetif, &sMulitcastIP);
}

/**
 * @brief Sends a multicast test message to the multicast group.
 */
void MulticastTestHandler(void)
{
	IGMP_MulticastUDPSend(MULTICAST_TEST_MSG, strlen(MULTICAST_TEST_MSG), &sMulitcastIP, MULTICAST_PORT, &gsNetif);
}


