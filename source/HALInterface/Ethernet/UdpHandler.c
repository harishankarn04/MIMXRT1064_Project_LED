/**
 * @file    UdpHandler.c
 * @brief   UDP communication layer for receiving and sending EMP protocol packets.
 *
 * (C) Copyright Centum T&S Group 2025. All rights reserved.
 * This computer program may not be used, copied, distributed, translated, transmitted or assigned
 * without the prior written authorization of Centum T&S Group.
 *
 **/


#include "lwip/udp.h"
#include "lwip/ip4_addr.h"
#include "lwip/pbuf.h"
#include <string.h>
#include "UdpHandler.h"
#include "Middleware/MessageLayerparser/ReceivingMessageQueue.h"
#include "Middleware/MessageLayerparser/MessageProtocolParser.h"
#include "HAL/EthernetInterface/Ethernet.h"
#include "Common/CommonDefs.h"

#define UDP_HEX_DUMP_SIZE      ((MAX_UDP_PAYLOAD_SIZE * 3U) + 1U)

/// Global pointer to the UDP PCB instance
struct udp_pcb *gptUdpPcbPid  = NULL;

/**
 * @brief Callback invoked when a UDP packet is received.
 *
 * This function validates the incoming buffer, prints debug information,
 * enqueues the payload into the receiving queue, and frees the pbuf.
 *
 * @param pvArg    User-supplied callback argument (unused)
 * @param pxPcb    Pointer to UDP PCB
 * @param pxBuf    Pointer to pbuf containing received data
 * @param pxAddr   Pointer to source IP address
 * @param usPort   Source UDP port
 */
static void UdpHandler_ReceiveCallback(void *pvArg, struct udp_pcb *pxPcb, struct pbuf *pxBuf,
                                   const ip_addr_t *pxAddr, uint16_t usPort)
{
    if ((pxBuf == NULL) || (pxBuf->payload == NULL) || (pxBuf->len == 0U))
    {
    	COSLOG_ERROR("Received NULL or empty buffer "
               "(pxBuf = %p, payload = %p, len = %u)\r\n",
               (void *)pxBuf,
               (pxBuf != NULL) ? pxBuf->payload : NULL,
               (pxBuf != NULL) ? pxBuf->len : 0U);
        pbuf_free(pxBuf);
    }
    else
    {
        char acIpString[16];
        ipaddr_ntoa_r(pxAddr, acIpString, sizeof(acIpString));
        COSLOG_DEBUG("Received %u bytes from %s:%u\r\n", pxBuf->len, acIpString, usPort);

        char acHexDump[UDP_HEX_DUMP_SIZE];
        int iOffset = 0;
        uint8_t *pubPayload = (uint8_t *)pxBuf->payload;

        for (uint16_t usIndex = 0U; usIndex < pxBuf->len; usIndex++)
        {
            int written = snprintf(acHexDump + iOffset,
                                   sizeof(acHexDump) - iOffset,
                                   "%02X ",
                                   pubPayload[usIndex]);
            if ((written < 0) || ((size_t)written >= (sizeof(acHexDump) - (size_t)iOffset)))
            {
                break; /* Prevent buffer overflow */
            }
            iOffset += written;
        }
        acHexDump[iOffset] = '\0';

        COSLOG_DEBUG("Payload: %s\r\n", acHexDump);

        uint8_t ubEnqueueStatus = ReceivingMessageQueue_EnqueueUDPBuffer(pubPayload, pxBuf->len, pxAddr, usPort);
        if (ubEnqueueStatus == FAILURE)
        {
        	COSLOG_WARN("Queue full, message dropped\r\n");
        }
        else
        {
        	COSLOG_INFO("Message enqueued successfully\r\n");
        }

        pbuf_free(pxBuf);
    }
}

/**
 * @brief Initializes a UDP server socket and binds it to the specified IP and port.
 *
 * Creates a UDP PCB, binds to the given IP and port, and registers a receive callback.
 *
 * @param pxIpAddress Pointer to IP address to bind to
 * @param usPort      Port number to bind to
 * @return Pointer to initialized UDP PCB on success, NULL on failure
 */
struct udp_pcb *UdpHandler_InitServer(const ip_addr_t *pxIpAddress, uint16_t usPort)
{
    struct udp_pcb *pxPcb = NULL;
    char acIpString[16];
    err_t xErr;

    pxPcb = udp_new();
    if (pxPcb == NULL)
    {
    	COSLOG_ERROR("Could not allocate new UDP PCB\r\n");
        return NULL;
    }
    else
    {
    	COSLOG_INFO("Successfully created new UDP PCB\r\n");
    }

    xErr = udp_bind(pxPcb, pxIpAddress, usPort);
    if (xErr != ERR_OK) {
    	COSLOG_ERROR("Failed to bind UDP socket\r\n");
        udp_remove(pxPcb);
        return NULL;
    }
    else
    {
    	COSLOG_INFO("Successfully bound UDP PCB to port %u\r\n", usPort);
    }

    udp_recv(pxPcb, UdpHandler_ReceiveCallback, NULL);
    ipaddr_ntoa_r(&pxPcb->local_ip, acIpString, sizeof(acIpString));
    COSLOG_INFO("Server initialized on %s:%u\r\n",acIpString, usPort);

    gptUdpPcbPid  = pxPcb;
    return pxPcb;
}

/**
 * @brief Sends a UDP response packet to the specified IP address and port.
 *
 * Allocates a pbuf, copies the response data, sends the packet, and frees the pbuf.
 *
 * @param pxPcb         Pointer to initialized UDP PCB
 * @param pxAddr        Destination IP address
 * @param usPort        Destination port number
 * @param pubData       Pointer to response data buffer
 * @param stDataLength  Number of bytes to send
 */
void UdpHandler_SendMessage(struct udp_pcb *pxPcb,
                        const ip_addr_t *pxAddr,
                        uint16_t usPort,
                        const uint8_t* pubData,
                        size_t stDataLength)
{
    err_t udp_send_status = ERR_VAL;
    struct pbuf *pxResponseBuf = NULL;

    if ((pxPcb == NULL) || (pxAddr == NULL) || (pubData == NULL) || (stDataLength == 0U))
    {
    	COSLOG_ERROR("Invalid arguments\r\n");
    }
    else
    {
    	 char acHexDump[UDP_HEX_DUMP_SIZE];
    	        int iOffset = 0;

    	        for (size_t stIndex = 0U; stIndex < stDataLength; stIndex++)
    	        {
    	            int written = snprintf(acHexDump + iOffset,
    	                                   sizeof(acHexDump) - iOffset,
    	                                   "%02X ",
    	                                   pubData[stIndex]);
    	            if ((written < 0) || ((size_t)written >= (sizeof(acHexDump) - (size_t)iOffset)))
    	            {
    	                break; /* Prevent buffer overflow */
    	            }
    	            iOffset += written;
    	        }
    	        acHexDump[iOffset] = '\0';

    	        COSLOG_DEBUG("Sending UDP Payload (%u bytes): %s\r\n",
    	                     (uint32_t)stDataLength, acHexDump);

        pxResponseBuf = pbuf_alloc(PBUF_TRANSPORT, stDataLength, PBUF_RAM);
        if (pxResponseBuf == NULL)
        {
        	COSLOG_ERROR("Could not allocate pbuf\r\n");
        }
        else
        {
        	COSLOG_INFO("pbuf allocated (%u bytes)\r\n", (uint32_t)stDataLength);
            (void)memcpy(pxResponseBuf->payload, pubData, stDataLength);

            udp_send_status = udp_sendto(pxPcb, pxResponseBuf, pxAddr, usPort);
            if (udp_send_status != ERR_OK)
            {
            	COSLOG_ERROR("Failed to send UDP packet (err = %d)\r\n", udp_send_status);
            }
            else
            {
            	COSLOG_INFO("Response sent to %s:%u\r\n", ipaddr_ntoa(pxAddr), usPort);
            }

            pbuf_free(pxResponseBuf);
            COSLOG_INFO("Response pbuf freed\r\n");
        }
    }

    return;
}
