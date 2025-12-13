/**
 * @file    igmp_test.h
 * @brief   Header for IGMP multicast test implementation.
 *
 * This file declares functions used to initialize multicast,
 * handle multicast reception, and send multicast test messages.
 *
 * (C) Copyright Centum T&S Group 2025. All rights reserved.
 * This computer program may not be used, copied, distributed, translated, transmitted or assigned
 * without the prior written authorization of Centum T&S Group.
 */

#ifndef ETHERNETINTERFACE_TEST_IGMP_TEST_H_
#define ETHERNETINTERFACE_TEST_IGMP_TEST_H_

//------------------------------------ [ INCLUDE FILES ] ----------------------------

//-------------------------------------- [ PROTOTYPES ] -----------------------------

void CustomMulticastReceive(void *arg, struct udp_pcb *psPcb, struct pbuf *psBuf, const ip_addr_t *psAddr, u16_t usPort);

void MulticastInit(void);

void MulticastTestHandler(void);

#endif /* ETHERNETINTERFACE_TEST_IGMP_TEST_H_ */
