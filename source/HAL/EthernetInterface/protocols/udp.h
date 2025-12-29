/**
 * @file    udp.h
 * @brief   Header file for UDP server and communication setup.
 *
 * This file defines the initialization and callback functions for the UDP server,
 * as well as the configuration of UDP sockets for sending and receiving data.
 *
 * (C) Copyright Centum T&S Group 2025. All rights reserved.
 *	This computer program may not be used, copied, distributed, translated, transmitted or assigned
 *	without the prior written authorization of Centum T&S Group.
*/

#ifndef ETHERNETINTERFACE_PROTOCOLS_UDP_H_
#define ETHERNETINTERFACE_PROTOCOLS_UDP_H_

//------------------------------------ [ INCLUDE FILES ] ----------------------------

#include "lwip/udp.h"

//---------------------------------------- [ DEFINES ] ------------------------------


//---------------------------------------- [ TYPEDEF ] ------------------------------

typedef void (*UDPReceiveCallback)(void *arg, struct udp_pcb *pcb, struct pbuf *p, const ip_addr_t *addr, u16_t port);

//---------------------------------------- [ PROTOTYPES ] ---------------------------

extern struct udp_pcb *UDP_ServerInit(const ip_addr_t *psServerIP, u16_t usServerPort, UDPReceiveCallback pfctReceiveCallback, void *CallbackArgument);

extern err_t UDP_Send(struct udp_pcb *psPcb, const ip_addr_t *psDestIP, u16_t usDestPort, const void *pMessage, u16_t usMessageLen);



#endif /* ETHERNETINTERFACE_PROTOCOLS_UDP_H_ */
