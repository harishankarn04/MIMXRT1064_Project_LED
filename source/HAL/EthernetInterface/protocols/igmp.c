/**
 * @file    igmp.c
 * @brief   Implementation of IGMP (Internet Group Management Protocol) functionality.
 *
 * Contains functions for joining and leaving multicast groups, initializing a
 * multicast UDP server, sending multicast packets, and handling received multicast data.
 *
 * (C) Copyright Centum T&S Group 2025. All rights reserved.
 * This computer program may not be used, copied, distributed, translated,
 * transmitted, or assigned without the prior written authorization of Centum T&S Group.
 */

//------------------------------------ [ INCLUDE FILES ] ----------------------------
#include <HAL/EthernetInterface/Ethernet.h>
#include <HAL/EthernetInterface/protocols/igmp.h>
#include "lwip/udp.h"
#include "lwip/ip_addr.h"
#include "lwip/igmp.h"
#include "lwip/netif.h"
#include "lwip/tcpip.h"
#include "lwip/sys.h"
#include <stdio.h>

//-------------------------------------[ DEFINES ] ----------------------------------

//-------------------------------------[ TYPEDEF ] ----------------------------------

//-------------------------------------[ STATIC VARIABLE ] --------------------------

//-------------------------------------[ LOCAL PROTOTYPES ] -------------------------

//-------------------------------------[ GLOBAL FUNCTIONS ] -------------------------

/**
 * @brief Joins a specified multicast group on a network interface.
 *
 * @param sNetif        Pointer to the network interface.
 * @param psMulticastIP  Multicast IP address to join.
 *
 * @return ERR_OK on success, or lwIP error code on failure.
 */
err_t IGMP_JoinGroup(struct netif *sNetif, const ip_addr_t *psMulticastIP)
{
    if (!sNetif || !psMulticastIP)
        return ERR_ARG;


    err_t sbErr = igmp_joingroup(ip_2_ip4(&sNetif->ip_addr), ip_2_ip4(psMulticastIP));

     // Enable IGMP on the interface

    if (sbErr == ERR_OK)
    {
        PRINTF("Joined multicast group: %s\r\n", ipaddr_ntoa(psMulticastIP));
    }

    else
    {
        PRINTF("Failed to join multicast group: %s\r\n", ipaddr_ntoa(psMulticastIP));
    }

    return sbErr;
}

/**
 * @brief Leaves a previously joined multicast group on a network interface.
 *
 * @param sNetif        Pointer to the network interface.
 * @param psMulticastIP  Multicast IP address to leave.
 *
 * @return ERR_OK on success, or lwIP error code on failure.
 */
err_t IGMP_LeaveGroup(struct netif *sNetif, const ip_addr_t *psMulticastIP)
{
    if (!sNetif || !psMulticastIP)
        return ERR_ARG;

    err_t sbErr = igmp_leavegroup(ip_2_ip4(&sNetif->ip_addr), ip_2_ip4(psMulticastIP));

    if (sbErr == ERR_OK)
    {
        PRINTF("Left multicast group: %s\r\n", ipaddr_ntoa(psMulticastIP));
    }
    else
    {
        PRINTF("Failed to leave multicast group: %s\r\n", ipaddr_ntoa(psMulticastIP));
    }

    return sbErr;
}

/**
 * @brief Initializes a UDP socket to receive multicast packets.
 *
 * This function binds a UDP PCB to the given port and registers a callback
 * for receiving data. It also joins the specified multicast group.
 *
 * @param sNetif           Pointer to the network interface.
 * @param psMulticastIP     Multicast group IP address to join.
 * @param usPort            UDP port to bind to.
 * @param pfctReceiveFunction Callback function to handle received packets.
 * @param ReceiveArg      User argument passed to the callback.
 */
void IGMP_MulticastUDPInit(struct netif *sNetif, const ip_addr_t *psMulticastIP, u16_t usPort, UdpReceiveFunction pfctReceiveFunction, void *ReceiveArg)
{
    struct udp_pcb *psPcb;
    ip_addr_t sAllIP;

    if (!psMulticastIP || !sNetif)
    {
    	PRINTF("Error : Invalid arguments to MulticastUDPInit\r\n");
    	return;
    }

    IP_ADDR4(&sAllIP, 0, 0, 0, 0);  // Binding to all IPs

    psPcb = udp_new_ip_type(IPADDR_TYPE_V4); // Create new UDP PCB

    if (psPcb == NULL)
    {
    	PRINTF("Failed to create UDP PCB \r\n");
    	return;
    }

    if (udp_bind(psPcb, &sAllIP, usPort) != ERR_OK)
    {
        PRINTF("UDP bind failed on port %u\r\n", usPort);
        udp_remove(psPcb);
        return;
    }

    if (pfctReceiveFunction == NULL)
    {
    	pfctReceiveFunction = DefaultMulticastUDPReceive;
    }
	udp_recv(psPcb, pfctReceiveFunction, ReceiveArg);  // Set callback function
	PRINTF("Multicast UDP server initialized on port %u.\r\n", usPort);

	/* Join multicast group */
    if (IGMP_JoinGroup(sNetif, psMulticastIP) != ERR_OK)
    {
        PRINTF("Failed to join multicast group: %s\r\n", ipaddr_ntoa(psMulticastIP));
    }

    else
    {
    	//No else Statement
    }
}

/**
 * @brief Sends a UDP multicast message to the specified group.
 *
 * @param psbData             Pointer to the message data to send.
 * @param usLen              Length of the message in bytes.
 * @param psDestinationIP    Multicast destination IP address.
 * @param usDestinationPort  Multicast UDP destination port.
 * @param sNetif            Pointer to the sending network interface.
 */
void IGMP_MulticastUDPSend(const char *psbData, uint16_t usLen, const ip_addr_t *psDestinationIP, uint16_t usDestinationPort, struct netif *sNetif)
{
    struct udp_pcb *psPcb;
    struct pbuf *psBuf;

    err_t sbErr;

    if (!psbData || usLen ==0 || !sNetif || !psDestinationIP)
    {
    	PRINTF("Invalid arguments for multicast send\r\n");
    	return;
    }
    psPcb = udp_new();
    if (psPcb == NULL)
    {
        PRINTF("Failed to create UDP PCB for sending.\r\n");
        return;
    }

    // Set the multicast TTL to 1 (local subnet), change if needed
    udp_set_multicast_ttl(psPcb, UDP_TTL);

    psBuf = pbuf_alloc(PBUF_TRANSPORT, usLen, PBUF_RAM);
    if (!psBuf)
    {
        PRINTF("Failed to allocate pbuf for multicast send.\r\n");
        udp_remove(psPcb);
        return;
    }

    memcpy(psBuf->payload, psbData, usLen);

    // Send the packet to the multicast group
    sbErr = udp_sendto_if(psPcb, psBuf, psDestinationIP, usDestinationPort, sNetif);
    if (sbErr != ERR_OK)
    {
        PRINTF("udp_sendto_if failed: %d\r\n", sbErr);
    }
    else
    {
        PRINTF("Multicast message sent.\r\n");
    }

    pbuf_free(psBuf);
    udp_remove(psPcb);
}


/**
 * @brief Default callback for receiving multicast UDP packets.
 *
 * This function logs the sender's address and length of the received packet.
 *
 * @param arg   User-defined argument (unused).
 * @param psPcb   Pointer to the UDP control block.
 * @param psBuf     Pointer to the received pbuf.
 * @param psAddr  Source IP address of the packet.
 * @param usPort  Source UDP port of the packet.
 */
void DefaultMulticastUDPReceive(void *arg, struct udp_pcb *psPcb, struct pbuf *psBuf, const ip_addr_t *psAddr, u16_t usPort)
{
    if (psBuf != NULL)
    {
        PRINTF("Received multicast packet from %s:%d, len=%d\r\n", ipaddr_ntoa(psAddr), usPort, psBuf->tot_len);

        pbuf_free(psBuf);  // Free the buffer when done
    }
    else
    {
        PRINTF("Received empty packet.\r\n");
    }
}
