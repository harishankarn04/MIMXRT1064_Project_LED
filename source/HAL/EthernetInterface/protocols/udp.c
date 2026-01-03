/**
 * @file    udp.c
 * @brief   Implementation of the UDP server and communication functions.
 *
 * This file contains the implementation of functions to initialize a UDP server,
 * handle incoming UDP packets, and send periodic UDP Messages to a remote PC.
 *
 * (C) Copyright Centum T&S Group 2025. All rights reserved.
 *	This computer program may not be used, copied, distributed, translated, transmitted or assigned
 *	without the prior written authorization of Centum T&S Group.
*/

//------------------------------------ [ INCLUDE FILES ] ----------------------------


#include <HAL/EthernetInterface/Ethernet.h>
#include <HAL/EthernetInterface/protocols/udp.h>
#include "lwip/udp.h"
#include "lwip/ip4_addr.h"
#include "lwip/pbuf.h"
#include <string.h>

//---------------------------------------- [ DEFINES ] ------------------------------

//---------------------------------------- [ TYPEDEF ] ------------------------------

//------------------------------- [ STATIC VARIABLE ] --------------------------------

//------------------------------- [ LOCAL PROTOTYPES ] ------------------------------

//------------------------------- [ GLOBAL FUNCTIONS ] -------------------------------


/**
 * @brief Initializes the UDP server and returns the PCB.
 *
 * This function creates and binds a UDP socket to the specified server port.
 * It also registers a callback to handle incoming UDP packets.
 * If the IP is NULL, it defaults to IP_ADDR_ANY.
 *
 * @param psServerIP   Pointer to the IP address to bind to. Pass NULL to bind to all interfaces.
 * @param usServerPort UDP port number to bind to.
 * @param pfctAcceptCallback Function to call when a client connects (NULL to use default).
 * @param arg            User-defined argument to pass to the callback (optional).
 * *
 * @return Pointer to the created and bound UDP PCB, or NULL on failure.
 */
struct udp_pcb *UDP_ServerInit(const ip_addr_t *psServerIP, u16_t usServerPort, UDPReceiveCallback pfctReceiveCallback, void *CallbackArgument)
{
    struct udp_pcb *psPcb = udp_new();
    if (psPcb==NULL)
    {
		return NULL;
    }

    if (psServerIP == NULL)
    {
        psServerIP = IP_ADDR_ANY;  // default to listen on all interfaces
    }

    if (udp_bind(psPcb, psServerIP, usServerPort) != ERR_OK)
    {
    	udp_remove(psPcb);
    	return NULL;
	}

    udp_recv(psPcb, pfctReceiveCallback, CallbackArgument);

    return psPcb;

}



/**
 * @brief Sends a UDP packet to a specified IP and port.
 *
 * @param psPcb          Pointer to the UDP control block used for sending.
 * @param psDestIP      Pointer to the destination IP address.
 * @param usDestPort    Destination UDP port number.
 * @param pMessage      Pointer to the data to be sent.
 * @param usMessageLen  Length of the data in bytes.
 *
 * @return ERR_OK on success, or lwIP error code on failure.
 */

err_t UDP_Send(struct udp_pcb *psPcb, const ip_addr_t *psDestIP, u16_t usDestPort, const void *pMessage, u16_t usMessageLen)

{

	err_t sbErr;
	struct pbuf *psUDPBuffer;

	if ((psPcb == NULL) || (psDestIP == NULL) || (pMessage == NULL) || (usMessageLen == 0))
	{
		return ERR_ARG;
	}

	psUDPBuffer = pbuf_alloc(PBUF_TRANSPORT, usMessageLen, PBUF_RAM);
	if (psUDPBuffer == NULL)
	{
		return ERR_MEM;
	}
	memcpy(psUDPBuffer->payload, pMessage, usMessageLen);
	sbErr = udp_sendto(psPcb, psUDPBuffer, psDestIP, usDestPort);
	pbuf_free(psUDPBuffer);

	return sbErr;
}
