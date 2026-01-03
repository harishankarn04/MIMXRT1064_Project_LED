/**
 * @file    Ethernet.c
 * @brief   Ethernet driver and network stack initialization.
 *
 * (C) Copyright Centum T&S Group 2025. All rights reserved.
 * This computer program may not be used, copied, distributed, translated, transmitted or assigned
 * without the prior written authorization of Centum T&S Group.
 */

//------------------------------------ [ INCLUDE FILES ] ----------------------------//

#include <HAL/EthernetInterface/Ethernet.h>
#include <HAL/EthernetInterface/protocols/dhcp.h>

#include "netif/ethernet.h"
#include "lwip/init.h"
#include "ethernetif.h"
#include "fsl_phy.h"
#include "fsl_silicon_id.h"
#include "fsl_iomuxc.h"
#include "fsl_enet.h"
#include "pin_mux.h"
#include "board.h"
#include "app.h"
#include "lwip/opt.h"
#include "lwip/dhcp.h"
#include "lwip/ip_addr.h"

//-------------------------------------[ DEFINES ] ----------------------------------//


//-------------------------------------[ TYPEDEF ] ----------------------------------
//
phy_ksz8081_resource_t PhyResource;

//-------------------------------------[ STATIC VARIABLE ] --------------------------
//
static netif_ext_callback_t sLinkStatusCallbackInfo;

static phy_handle_t PhyHandle;

//-------------------------------------[ LOCAL PROTOTYPES ] -------------------------
//
void ENET_InitModuleClock(void);
void LinkStatusCallback(struct netif *sNetif, netif_nsc_reason_t usReason, const netif_ext_callback_args_t *puArgs);

//-------------------------------------[ GLOBAL VARIABLE ] --------------------------
//
struct netif gsNetif;

//-------------------------------------[ GLOBAL FUNCTIONS ] -------------------------
//

/**
 * @brief Initializes Ethernet hardware and attaches the interface to the LwIP stack.
 *
 * Sets up MAC address, IP settings, and configures the ENET interface.
 * Initializes LwIP and registers the network interface with the IP stack.
 */
void ENET_EthernetInit(void)
{
    ethernetif_config_t sEnetConfig = {
        .phyHandle = &PhyHandle,
        .phyAddr = PHY_ADDRESS,
        .phyOps = PHY_OPS,
        .phyResource = PHY_RESOURCE,
#ifdef configMAC_ADDR
        .macAddress = configMAC_ADDR
#endif
    };

    ENET_InitModuleClock();

    IOMUXC_EnableMode(IOMUXC_GPR, kIOMUXC_GPR_ENET1TxClkOutputDir, true);

    MDIOInit();

    BOARD_ENET_PHY_RESET;

    PhyResource.read  = MDIORead;
    PhyResource.write = MDIOWrite;

    time_init();

#ifndef configMAC_ADDR
    (void)SILICONID_ConvertToMacAddr(&sEnetConfig.macAddress);
#endif

    sEnetConfig.srcClockHz = CLOCK_FREQ;


    lwip_init();

    netif_add_ext_callback(&sLinkStatusCallbackInfo, LinkStatusCallback);

	netif_add(&gsNetif, NULL, NULL, NULL, &sEnetConfig, NETIF_INIT_FN, ethernet_input);


	netif_set_default(&gsNetif);

	netif_set_up(&gsNetif);

}

/**
 * @brief Waits for the Ethernet PHY link to become active.
 *
 * Continuously checks for PHY link-up status with a timeout.
 * If auto-negotiation fails, prints a diagnostic message.
 */
void ENET_Test(void)
{
    while (ethernetif_wait_linkup(&gsNetif, 5000) != ERR_OK)
    {
        PRINTF("PHY Auto-negotiation failed. Please check the cable connection and link partner setting.\r\n");
    }
}

/**
 * @brief Assigns a static IP configuration to the given network interface.
 *
 * This function stops any active DHCP client on the specified network interface
 * and sets a predefined static IP address, subnet mask, and gateway as configured
 * by macros in Ethernet.h (CONFIG_IP_ADDR*, CONFIG_NET_MASK*, CONFIG_GW_ADDR*).
 *
 * @param sNetif Pointer to the network interface (struct netif) to configure.
 *
 * @note After calling this function, the interface will no longer attempt DHCP.
 *       Ensure the static IP and gateway are in the correct subnet.
 */
void ENET_SetStaticIP(struct netif *sNetif)
{
    ip4_addr_t sIPAddr, sNetmask, sGateway;

    IP4_ADDR(&sIPAddr, CONFIG_IP_ADDR0, CONFIG_IP_ADDR1, CONFIG_IP_ADDR2, CONFIG_IP_ADDR3);
    IP4_ADDR(&sNetmask, CONFIG_NET_MASK0, CONFIG_NET_MASK1, CONFIG_NET_MASK2, CONFIG_NET_MASK3);
    IP4_ADDR(&sGateway, CONFIG_GW_ADDR0, CONFIG_GW_ADDR1, CONFIG_GW_ADDR2, CONFIG_GW_ADDR3);
    dhcp_stop(sNetif); // Stop DHCP if running
    netif_set_addr(sNetif, &sIPAddr, &sNetmask, &sGateway);

    PRINTF("Static IP assigned: %s\r\n", ip4addr_ntoa(&sIPAddr));
}

//-------------------------------------[ LOCAL FUNCTIONS ]-----------------------
//
/**
 * @brief Initializes the ENET PLL and clocks for the Ethernet module.
 *
 * Configures and enables the ENET PLL (Phase-Locked Loop) to provide a stable clock
 * source for the Ethernet MAC peripheral.
 */
void ENET_InitModuleClock(void)
{
    const clock_enet_pll_config_t config = {
        .enableClkOutput    = true,
        .enableClkOutput25M = false,
        .loopDivider        = 1,
    };
    CLOCK_InitEnetPll(&config);
}


/**
 * @brief Callback for link status changes.
 *
 * This function is triggered by the network stack when the link status
 * of a network interface changes (e.g., cable unplugged, reconnected).
 * It prints the current link state along with speed and duplex information.
 *
 * @param sNetif Pointer to the network interface structure.
 * @param usReason Reason for the callback (e.g., link state change).
 * @param puArgs Callback arguments containing link state data.
 */
void LinkStatusCallback(struct netif *sNetif, netif_nsc_reason_t usReason, const netif_ext_callback_args_t *puArgs)
{
    if (usReason != LWIP_NSC_LINK_CHANGED)
        return;

    PRINTF("[LINK STATE] netif=%d, state=%s", sNetif->num, puArgs->link_changed.state ? "up" : "down");

    if (puArgs->link_changed.state)
    {
        char *psbSpeedStr;
        switch (ethernetif_get_link_speed(sNetif))
        {
            case kPHY_Speed10M:
                psbSpeedStr = "10M";
                break;
            case kPHY_Speed100M:
                psbSpeedStr = "100M";
                break;
            case kPHY_Speed1000M:
                psbSpeedStr = "1000M";
                break;
            default:
                psbSpeedStr = "N/A";
                break;
        }

        char *psbDuplexStr;
        switch (ethernetif_get_link_duplex(sNetif))
        {
            case kPHY_HalfDuplex:
                psbDuplexStr = "half";
                break;
            case kPHY_FullDuplex:
                psbDuplexStr = "full";
                break;
            default:
                psbDuplexStr = "N/A";
                break;
        }

        PRINTF(", speed=%s_%s", psbSpeedStr, psbDuplexStr);
    }

    PRINTF("\r\n");
}

/**
 * @brief Initializes the MDIO interface for PHY communication.
 *
 * Enables the ENET clock and sets up the Serial Management Interface (SMI)
 * used for accessing the PHY registers over MDIO.
 */
void MDIOInit(void)
{
    (void)CLOCK_EnableClock(s_enetClock[ENET_GetInstance(PHY_ENET)]);
    ENET_SetSMI(PHY_ENET, CLOCK_FREQ, false);
}


/**
 * @brief Writes data to a PHY register using MDIO.
 *
 * @param phyAddr The address of the PHY device.
 * @param regAddr The PHY register to write to.
 * @param data The data to write.
 * @return status_t Returns kStatus_Success or an error code on failure.
 */
status_t MDIOWrite(uint8_t phyAddr, uint8_t regAddr, uint16_t data)
{
    return ENET_MDIOWrite(PHY_ENET, phyAddr, regAddr, data);
}


/**
 * @brief Reads data from a PHY register using MDIO.
 *
 * @param phyAddr The address of the PHY device.
 * @param regAddr The PHY register to read from.
 * @param pData Pointer to store the read data.
 * @return status_t Returns kStatus_Success or an error code on failure.
 */
status_t MDIORead(uint8_t phyAddr, uint8_t regAddr, uint16_t *pData)
{
    return ENET_MDIORead(PHY_ENET, phyAddr, regAddr, pData);
}



