/**
 * @file    tcp_test.c
 * @brief   TCP server test application using lwIP.
 *
 * This file implements a simple TCP server that accepts client connections
 * and sends a welcome message. It also sets a receive callback for further handling.
 *
 * (C) Copyright Centum T&S Group 2025. All rights reserved.
 * This computer program may not be used, copied, distributed, translated, transmitted or assigned
 * without the prior written authorization of Centum T&S Group.
 */

//------------------------------------ [ INCLUDE FILES ] ----------------------------

#include <HAL/EthernetInterface/Ethernet.h>
#include <HAL/EthernetInterface/protocols/tcp.h>

#include "lwip/init.h"
#include "lwip/netif.h"
#include "lwip/timeouts.h"
#include "lwip/tcp.h"
#include "lwip/ip_addr.h"
#include <stdio.h>

//-------------------------------------- [ DEFINES ] --------------------------------

#define SERVER_PORT     12345
#define TEST_MESSAGE "Welcome to TCP Echo Server!\r\n"

//---------------------------------- [ LOCAL PROTOTYPES ] ---------------------------

/**
 * @brief Callback when a TCP client connects.
 *
 * Sends a welcome message to the connected client and sets the default receive callback.
 *
 * @param arg       Custom user argument (unused).
 * @param psNewPcb   New TCP PCB representing the connection.
 * @param err       Error code for the connection.
 *
 * @return ERR_OK if successful, or an lwIP error code otherwise.
 */
static err_t TestAcceptCallback(void *arg, struct tcp_pcb *psNewPcb, err_t ubErr);

//---------------------------------- [ GLOBAL FUNCTIONS ] ---------------------------

/**
 * @brief Initializes the TCP server test.
 *
 * Binds the server to any IP address and a fixed port, and sets the custom accept callback.
 */
void TCPTestInit(void) {
    ip_addr_t sServerIP;

    // Bind to any IP address
    IP_ADDR4(&sServerIP, 0, 0, 0, 0);

    // Start TCP server on SERVER_PORT
    struct tcp_pcb *psServerPcb = TCP_ServerInit(&sServerIP, SERVER_PORT, TestAcceptCallback, NULL);
    if (psServerPcb == NULL) {
        PRINTF("TCPTestStart: Failed to initialize TCP server\r\n");
        return;
    }

    PRINTF("TCPTestStart: TCP server listening on port %d\r\n", SERVER_PORT);
}

//---------------------------------- [ LOCAL FUNCTIONS ] ----------------------------

static err_t TestAcceptCallback(void *arg, struct tcp_pcb *psNewPcb, err_t ubErr) {
    if (ubErr != ERR_OK || psNewPcb == NULL) {
        return ERR_VAL;
    }

    ip_addr_t *client_ip = &psNewPcb->remote_ip;
    PRINTF("Client connected: %s:%d\r\n", ipaddr_ntoa(client_ip), psNewPcb->remote_port);

    // Send welcome message using TCPSend (explicit use)
    err_t ubSendResult = TCP_SendMessage(psNewPcb, TEST_MESSAGE, strlen(TEST_MESSAGE));
    if (ubSendResult != ERR_OK) {
        PRINTF("Failed to send test message: %d\r\n", ubSendResult);
    }

    // Setup the default receive callback (calls TCPDefaultReceive)
    tcp_recv(psNewPcb, TCPDefaultReceive);

    return ERR_OK;
}

