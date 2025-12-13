/**
 * @file    dhcp.c
 * @brief   DHCP (Dynamic Host Configuration Protocol) client functions.
 *
 * This file implements DHCP initialization and monitoring functionality,
 * including link status and DHCP state changes.
 *
 * (C) Copyright Centum T&S Group 2025. All rights reserved.
 * This computer program may not be used, copied, distributed, translated,
 * transmitted or assigned without the prior written authorization of Centum T&S Group.
 */

//------------------------------------ [ INCLUDE FILES ] ----------------------------

#include <HAL/EthernetInterface/protocols/dhcp.h>
#include <HAL/EthernetInterface/Ethernet.h>
#include "lwip/timeouts.h"
#include "lwip/ip_addr.h"
#include "lwip/init.h"
#include "lwip/dhcp.h"
#include "lwip/netif.h"
#include "lwip/prot/dhcp.h"
#include "netif/ethernet.h"
#include "ethernetif.h"
#include "lwip/sys.h"


//-------------------------------------[ DEFINES ] ----------------------------------
#define DHCP_TIMEOUT_MIN	5
#define DHCP_TIMEOUT_MS   (DHCP_TIMEOUT_MIN * 60 * 1000)

//-------------------------------------[ TYPEDEF ] ----------------------------------


//-------------------------------------[ STATIC VARIABLE ] --------------------------


//-------------------------------------[ LOCAL PROTOTYPES ] -------------------------


//-------------------------------------[ GLOBAL FUNCTIONS ] -------------------------

/**
 * @brief Starts the DHCP client on the specified network interface.
 *
 * This function checks if DHCP is already running on the given network
 * interface. If not, it initiates the DHCP client to acquire an IP address
 * from a DHCP server.If DHCP fails, it jumps to ENET_SetStaticIP() to assign a static IP address
 *
 * @param sNetif Pointer to the network interface structure.
 */
void DHCP_Init(struct netif *sNetif)
{
    if (sNetif == NULL)
	{
		PRINTF("DHCP Init error: netif is NULL\r\n");
		return;
	}


	if (netif_dhcp_data(sNetif) != NULL)
	{
		PRINTF("DHCP already running on this interface\r\n");
		return;
	}
    err_t sbErr;
    sbErr = dhcp_start(sNetif);

    if (sbErr == ERR_OK)
    {
        PRINTF("DHCP started\r\n");
    }
    else
    {
        PRINTF("Failed to start DHCP: %d\r\n", sbErr);
        ENET_SetStaticIP(sNetif);
    }

    uint32_t ulStartTime = sys_now();

     // Wait for DHCP success or timeout
     while (1)
     {
         sys_check_timeouts();
         ethernetif_input(sNetif);

         if (!ip4_addr_isany_val(*netif_ip4_addr(sNetif)))
         {
             break;
         }

         if ((sys_now() - ulStartTime) > DHCP_TIMEOUT_MS)
         {
             PRINTF("DHCP Timeout! Switching to static IP...\r\n");
             ENET_SetStaticIP(sNetif);
             break;
         }
     }
}

/**
 * @brief Prints the current DHCP state if it has changed from the last known state.
 *
 * This function monitors the DHCP state machine and prints the state whenever it changes.
 * When the state becomes `BOUND`, it also prints the obtained IP address, subnet mask,
 * and gateway.
 *
 * @param sNetif Pointer to the network interface structure.
 */
void DHCP_PrintState(struct netif *sNetif)
{
    static u8_t ubDHCPLastState = DHCP_STATE_OFF;
    struct dhcp *psDHCP           = netif_dhcp_data(sNetif);

    if (psDHCP == NULL)
    {
        ubDHCPLastState = DHCP_STATE_OFF;
    }
    else if (ubDHCPLastState != psDHCP->state)
    {
        ubDHCPLastState = psDHCP->state;

        PRINTF(" DHCP state       : ");
        switch (ubDHCPLastState)
        {
            case DHCP_STATE_OFF:
                PRINTF("OFF");
                break;
            case DHCP_STATE_REQUESTING:
                PRINTF("REQUESTING");
                break;
            case DHCP_STATE_INIT:
                PRINTF("INIT");
                break;
            case DHCP_STATE_REBOOTING:
                PRINTF("REBOOTING");
                break;
            case DHCP_STATE_REBINDING:
                PRINTF("REBINDING");
                break;
            case DHCP_STATE_RENEWING:
                PRINTF("RENEWING");
                break;
            case DHCP_STATE_SELECTING:
                PRINTF("SELECTING");
                break;
            case DHCP_STATE_INFORMING:
                PRINTF("INFORMING");
                break;
            case DHCP_STATE_CHECKING:
                PRINTF("CHECKING");
                break;
            case DHCP_STATE_BOUND:
                PRINTF("BOUND");
                break;
            case DHCP_STATE_BACKING_OFF:
                PRINTF("BACKING_OFF");
                break;
            default:
                PRINTF("%u", ubDHCPLastState);
                assert(0);
                break;
        }
        PRINTF("\r\n");

        if (ubDHCPLastState == DHCP_STATE_BOUND)
        {
            PRINTF("\r\n IPv4 Address     : %s\r\n", ipaddr_ntoa(&sNetif->ip_addr));
            PRINTF(" IPv4 Subnet mask : %s\r\n", ipaddr_ntoa(&sNetif->netmask));
            PRINTF(" IPv4 Gateway     : %s\r\n\r\n", ipaddr_ntoa(&sNetif->gw));
        }
    }
}
