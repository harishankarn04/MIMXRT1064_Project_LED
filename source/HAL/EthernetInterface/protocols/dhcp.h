/**
 * @file    dhcp.h
 * @brief   DHCP client interface declarations.
 *
 * This header file declares the initialization and status functions
 * for DHCP, as well as link status callback handling for an Ethernet interface.
 *
 * (C) Copyright Centum T&S Group 2025. All rights reserved.
 * This computer program may not be used, copied, distributed, translated,
 * transmitted or assigned without the prior written authorization of Centum T&S Group.
 */

#ifndef ETHERNETINTERFACE_PROTOCOLS_DHCP_H_
#define ETHERNETINTERFACE_PROTOCOLS_DHCP_H_
//------------------------------------ [ INCLUDE FILES ] ----------------------------
//
#include "netif.h"

//-------------------------------------[ DEFINES ] ----------------------------------
//

//-------------------------------------[ TYPEDEF ] ----------------------------------
//

//-------------------------------------[ PROTOTYPES ] -------------------------------

void DHCP_Init(struct netif *sNetif);

void DHCP_PrintState(struct netif *sNetif);

#endif /* ETHERNETINTERFACE_PROTOCOLS_DHCP_H_ */
