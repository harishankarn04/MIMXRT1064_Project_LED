/**
 * @file    UdpHandler.h
 * @brief   UDP communication layer for receiving and sending EMP protocol packets.
 *
 * (C) Copyright Centum T&S Group 2025. All rights reserved.
 * This computer program may not be used, copied, distributed, translated, transmitted or assigned
 * without the prior written authorization of Centum T&S Group.
 *
 **/


#ifndef UDPHANDLER_H
#define UDPHANDLER_H

#include "lwip/udp.h"
#include "lwip/ip_addr.h"
#include <stddef.h>
#include <stdint.h>

extern struct udp_pcb *gptUdpPcbPid ;

#define SUCCESS (1U)
#define FAILURE (0U)

/**
 * @brief UDP port number used by LED PID protocol.
 */
#define LED_PID_PROTOCOL_UDP_PORT  5440

/**
 * @brief Initializes the UDP server and binds it to the specified IP address and port.
 *
 * This function creates a new UDP PCB, binds it to the provided IP address and port,
 * and registers a receive callback for handling incoming UDP messages.
 *
 * @param pxIpAddress Pointer to the IP address to bind the server to.
 * @param usPort      UDP port number to listen on.
 *
 * @return Pointer to the initialized UDP PCB on success, or NULL on failure.
 */
struct udp_pcb *UdpHandler_InitServer(const ip_addr_t *pxIpAddress, uint16_t usPort);

/**
 * @brief Sends a response message to a remote UDP client.
 *
 * This function constructs a UDP packet using the specified data and sends it
 * to the given destination IP address and port using the specified PCB.
 *
 * @param pxPcb         Pointer to the UDP PCB used for sending.
 * @param pxAddr        Pointer to the destination IP address.
 * @param usPort        Destination UDP port.
 * @param pubData       Pointer to the data buffer to send.
 * @param stDataLength  Length of the data in bytes.
 */
void UdpHandler_SendMessage(struct udp_pcb *pxPcb, const ip_addr_t *pxAddr, uint16_t usPort,
                        const uint8_t* pubData, size_t stDataLength);

#endif // UDPHANDLER_H
