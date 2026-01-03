/**
 * @file    icmp.c
 * @brief   ICMP (ping) interface implementation using LwIP stack.
 *
 * This module provides initialization for sending ICMP echo (ping) requests
 * to a specified gateway IP address using LwIP.
 *
 * (C) Copyright Centum T&S Group 2025. All rights reserved.
 *	This computer program may not be used, copied, distributed, translated, transmitted or assigned
 *	without the prior written authorization of Centum T&S Group.
*/

//------------------------------------ [ INCLUDE FILES ] ----------------------------

#include <HAL/EthernetInterface/Ethernet.h>
#include <HAL/EthernetInterface/protocols/icmp.h>

#include "ping.h"

//-------------------------------------[ DEFINES ] ----------------------------------

//-------------------------------------[ TYPEDEF ] ----------------------------------

//-------------------------------------[ STATIC VARIABLE ] --------------------------

//-------------------------------------[ LOCAL PROTOTYPES ] -------------------------

//-------------------------------------[ GLOBAL FUNCTIONS ] -------------------------


/**
 * @brief Initializes ICMP echo (ping) functionality.
 *
 * This function starts the ping process using the provided gateway IP address.
 * It can be used to test connectivity from the MCU to the network gateway.
 *
 * @param gateway_ip Pointer to the IP address of the gateway to ping.
 */

void ICMP_PingInit(const ip_addr_t *psIPAddr)

{
        ping_init(psIPAddr);
}
