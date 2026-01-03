/**
 * @file    icmp.h
 * @brief   Header file for ICMP (ping) functionality using LwIP.
 *
 * This module initializes the ICMP (Internet Control Message Protocol) echo functionality,
 * commonly used for ping operations to test connectivity between devices.
 *
 * (C) Copyright Centum T&S Group 2025. All rights reserved.
 *	This computer program may not be used, copied, distributed, translated, transmitted or assigned
 *	without the prior written authorization of Centum T&S Group.
*/

#ifndef ETHERNETINTERFACE_PROTOCOLS_ICMP_H_
#define ETHERNETINTERFACE_PROTOCOLS_ICMP_H_

//------------------------------------ [ INCLUDE FILES ] ----------------------------

#include "lwip/ip4_addr.h"
#include "lwip/netif.h"

//-------------------------------------[ DEFINES ] ----------------------------------

//-------------------------------------[ TYPEDEF ] ----------------------------------

//-------------------------------------[ PROTOTYPES ] -------------------------------


void ICMP_PingInit(const ip_addr_t *psIPAddr);


#endif /* ETHERNETINTERFACE_PROTOCOLS_ICMP_H_ */
