/**
 * @file    igmp1.h
 * @brief   Header for IGMP (Internet Group Management Protocol) implementation.
 *
 * Contains function prototypes for joining and leaving multicast groups,
 * initializing multicast UDP communication, sending multicast data, and handling
 * received multicast packets.
 *
 * (C) Copyright Centum T&S Group 2025. All rights reserved.
 * This computer program may not be used, copied, distributed, translated,
 * transmitted, or assigned without the prior written authorization of Centum T&S Group.
 */
#ifndef ETHERNETINTERFACE_PROTOCOLS_IGMP_H_
#define ETHERNETINTERFACE_PROTOCOLS_IGMP_H_

//------------------------------------ [ INCLUDE FILES ] ----------------------------
#include "lwip/opt.h"
#include "lwip/ip_addr.h"
#include "lwip/udp.h"
#include "lwip/netif.h"
#include "lwip/igmp.h"

//-------------------------------------[ DEFINES ] ----------------------------------

//-------------------------------------[ TYPEDEF ] ----------------------------------
typedef void (*UdpReceiveFunction)(void *arg, struct udp_pcb *psPcb, struct pbuf *pSbuf, const ip_addr_t *psAddr, u16_t usPort);

//-------------------------------------[ PROTOTYPES ] -------------------------------

err_t IGMP_JoinGroup(struct netif *sNetif, const ip_addr_t *psMulticastIP);
err_t IGMP_LeaveGroup(struct netif *sNetif, const ip_addr_t *psMulticastIP);
void IGMP_MulticastUDPInit(struct netif *sNetif, const ip_addr_t *psMulticastIP, u16_t usPort, UdpReceiveFunction pfctReceiveFunction, void *ReceiveArg);
void IGMP_MulticastUDPSend(const char *psbData, uint16_t usLen, const ip_addr_t *psDestinationIP, uint16_t usDestinationIP, struct netif *sNetif);
void DefaultMulticastUDPReceive(void *arg, struct udp_pcb *psPcb, struct pbuf *psBuf, const ip_addr_t *psAddr, u16_t usPort);

#endif /* ETHERNETINTERFACE_PROTOCOLS_IGMP_H_ */

