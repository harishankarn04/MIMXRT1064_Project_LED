/**
 * @file    ethernet.h
 * @brief   Ethernet hardware and network stack initialization for embedded MCU.
 *
 * This header declares functions and configurations for setting up the Ethernet interface,
 * handling PHY communication via MDIO, and initializing system clocks for ENET peripherals.
 *
 * (C) Copyright Centum T&S Group 2025. All rights reserved.
 *	This computer program may not be used, copied, distributed, translated, transmitted or assigned
 *	without the prior written authorization of Centum T&S Group.
*/

#ifndef ETHERNETINTERFACE_ETHERNET_H
#define ETHERNETINTERFACE_ETHERNET_H

//------------------------------------ [ INCLUDE FILES ] ----------------------------
//
#include "lwip/netif.h"
#include "fsl_common.h"
#include "fsl_phy.h"
#include "netif.h"
#include "fsl_phyksz8081.h"

//-------------------------------------[ DEFINES ] ----------------------------------
//
#define PHY_BASIC_STATUS_REG    0x01
#define PHY_CONTROL_REG         0x00

#ifndef NETIF_INIT_FN
#define NETIF_INIT_FN ethernetif0_init
#endif


#ifndef CONFIG_IP_ADDR0
#define CONFIG_IP_ADDR0 192
#endif
#ifndef CONFIG_IP_ADDR1
#define CONFIG_IP_ADDR1 168
#endif
#ifndef CONFIG_IP_ADDR2
#define CONFIG_IP_ADDR2 131
#endif
#ifndef CONFIG_IP_ADDR3
#define CONFIG_IP_ADDR3 102
#endif

/* Netmask configuration. */
#ifndef CONFIG_NET_MASK0
#define CONFIG_NET_MASK0 255
#endif
#ifndef CONFIG_NET_MASK1
#define CONFIG_NET_MASK1 255
#endif
#ifndef CONFIG_NET_MASK2
#define CONFIG_NET_MASK2 255
#endif
#ifndef CONFIG_NET_MASK3
#define CONFIG_NET_MASK3 0
#endif

/* Gateway address configuration. */
#ifndef CONFIG_GW_ADDR0
#define CONFIG_GW_ADDR0 192
#endif
#ifndef CONFIG_GW_ADDR1
#define CONFIG_GW_ADDR1 168
#endif
#ifndef CONFIG_GW_ADDR2
#define CONFIG_GW_ADDR2 131
#endif
#ifndef CONFIG_GW_ADDR3
#define CONFIG_GW_ADDR3 1
#endif

/* Ethernet configuration. */
extern phy_ksz8081_resource_t PhyResource;
#define PHY_ENET         ENET
#define PHY_ADDRESS  BOARD_ENET0_PHY_ADDRESS
#define PHY_OPS      &phyksz8081_ops
#define PHY_RESOURCE &PhyResource
#define CLOCK_FREQ   CLOCK_GetFreq(kCLOCK_IpgClk)

extern struct netif gsNetif;
extern ip4_addr_t NetifGateway;

//-------------------------------------- [ PROTOTYPES ] -----------------------------
void ENET_Test(void);

void ENET_EthernetInit(void);

void ENET_InitModuleClock(void);

void ENET_SetStaticIP(struct netif *sNetif);

void MDIOInit(void);

status_t MDIOWrite(uint8_t phyAddr, uint8_t regAddr, uint16_t data);

status_t MDIORead(uint8_t phyAddr, uint8_t regAddr, uint16_t *pData);

#endif // ETHERNETINTERFACE_ETHERNET_H

