/**
 * @file    tcp.h
 * @brief   Header file for TCP server communication setup.
 *
 * This file contains declarations for initializing a TCP server,
 * handling client connections, and receiving TCP data.
 *
 * (C) Copyright Centum T&S Group 2025. All rights reserved.
 *	This computer program may not be used, copied, distributed, translated, transmitted or assigned
 *	without the prior written authorization of Centum T&S Group.
*/

#ifndef ETHERNETINTERFACE_PROTOCOLS_TCP_H_
#define ETHERNETINTERFACE_PROTOCOLS_TCP_H_

//------------------------------------ [ INCLUDE FILES ] ----------------------------

#include "lwip/tcp.h"

//-------------------------------------[ DEFINES ] ----------------------------------

//-------------------------------------[ TYPEDEF ] ----------------------------------
typedef err_t (*TCPAcceptCallback)(void *arg, struct tcp_pcb *psNewPcb, err_t sbErr);


//-------------------------------------[ PROTOTYPES ] -------------------------------

struct tcp_pcb *TCP_ServerInit(const ip_addr_t *psServerIP, u16_t usServerPort, TCPAcceptCallback pfctAcceptCallback, void *arg);

err_t TCP_SendMessage(struct tcp_pcb *psPcb, const void *pTcpMessage, u16_t usTcpMessageLen);

err_t TCPDefaultReceive(void *arg, struct tcp_pcb *psPcb, struct pbuf *psBuf, err_t sbErr);

#endif /* ETHERNETINTERFACE_PROTOCOLS_TCP_H_ */
