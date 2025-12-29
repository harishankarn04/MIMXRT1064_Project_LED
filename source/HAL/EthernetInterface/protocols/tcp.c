/**
 * @file    tcp.c
 * @brief   TCP server implementation for accepting client connections and handling data.
 *
 * Provides initialization for a TCP server, sending data, and basic echo-based receive callbacks
 * using the LwIP stack.
 * (C) Copyright Centum T&S Group 2025. All rights reserved.
 *	This computer program may not be used, copied, distributed, translated, transmitted or assigned
 *	without the prior written authorization of Centum T&S Group.
*/

//------------------------------------ [ INCLUDE FILES ] ----------------------------

#include <HAL/EthernetInterface/Ethernet.h>
#include <HAL/EthernetInterface/protocols/tcp.h>

#include "lwip/pbuf.h"
#include "lwip/timeouts.h"
#include <string.h>
#include "fsl_phy.h"
#include "lwip/tcp.h"
#include "ethernetif.h"

//-------------------------------------[ DEFINES ] ----------------------------------

//-------------------------------------[ TYPEDEF ] ----------------------------------

//-------------------------------------[ STATIC VARIABLE ] --------------------------

//-------------------------------------[ LOCAL PROTOTYPES ] -------------------------

err_t TCPDefaultReceive(void *arg, struct tcp_pcb *psPcb, struct pbuf *psBuf, err_t sbErr);

static err_t TCPDefaultAccept(void *arg, struct tcp_pcb *psNewPcb, err_t sbErr);

//-------------------------------------[ GLOBAL FUNCTIONS ] -------------------------

/**
 * @brief Initializes the TCP server socket and sets up the accept callback.
 *
 * Binds to the specified IP address and port, starts listening for incoming connections,
 * and registers a callback to handle new client connections.
 *
 * @param psServerIP       Pointer to the server's IP address (can be NULL to bind to any IP).
 * @param usServerPort     Port number on which the server should listen.
 * @param pfctAcceptCallback Function to call when a client connects (NULL to use default).
 * @param arg            User-defined argument to pass to the callback (optional).
 *
 * @return Pointer to the listening TCP PCB, or NULL on failure.
 */
struct tcp_pcb *TCP_ServerInit(const ip_addr_t *psServerIP, u16_t usServerPort, TCPAcceptCallback pfctAcceptCallback, void *arg)
{
    struct tcp_pcb *psPcb = tcp_new();
    err_t sbErr;
    if (psPcb == NULL)
    {
    	return NULL;
    }

    if (psServerIP == NULL)
    {
    	psServerIP = IP_ADDR_ANY;
    }

    sbErr = tcp_bind(psPcb, psServerIP, usServerPort);
    if (sbErr != ERR_OK)
    {
    	tcp_close(psPcb);
    	if (sbErr == ERR_VAL)
    	{
    		PRINTF("PCB is not in valid state");
    	}
    	else if(sbErr == ERR_USE)
    	{
    		PRINTF("Port is already in use");
    	}
    	return NULL;
    }

	struct tcp_pcb *sListenPcb = tcp_listen_with_backlog(psPcb, TCP_DEFAULT_LISTEN_BACKLOG);
	if(!sListenPcb)
	{
		tcp_close(psPcb);
		return NULL;
	}

	if (!pfctAcceptCallback)
		pfctAcceptCallback = TCPDefaultAccept;

	tcp_accept(sListenPcb, pfctAcceptCallback);

	return sListenPcb;

}

/**
 * @brief Sends a TCP message over an active connection.
 *
 * @param psPcb         Pointer to the TCP PCB representing the connection.
 * @param pTcpMessage   Pointer to the data buffer to send.
 * @param usTcpMessageLen Length of the data in bytes.
 *
 * @return ERR_OK on success, or lwIP error code on failure.
 */
err_t TCP_SendMessage(struct tcp_pcb *psPcb, const void *pTcpMessage, u16_t usTcpMessageLen)
{
    if ((psPcb == NULL) || (pTcpMessage == NULL) || (usTcpMessageLen == 0))
    {
        return ERR_ARG;
    }

    err_t sbErr = tcp_write(psPcb, pTcpMessage, usTcpMessageLen, TCP_WRITE_FLAG_COPY);
    if (sbErr != ERR_OK)
    {
        return sbErr;
    }

    sbErr = tcp_output(psPcb);
    return sbErr;
}

//-------------------------------------[ LOCAL FUNCTIONS ] -------------------------

/**
 * @brief TCP receive callback for handling incoming data from the client.
 *
 * This function is invoked when data is received on the TCP connection.
 * If the connection is closed (i.e., psBuf is NULL), the connection is cleaned up.
 * Otherwise, it echoes back the received data to the client.
 *
 * @param arg User-supplied argument (not used here).
 * @param psPcb Pointer to the TCP protocol control block for the connection.
 * @param psBuf Pointer to the received pbuf (packet buffer). NULL if connection is closed.
 * @param sbErr Error status (can be used for diagnostics).
 * @return err_t Returns ERR_OK after processing or closing the connection.
 */
err_t TCPDefaultReceive(void *arg, struct tcp_pcb *psPcb, struct pbuf *psBuf, err_t sbErr)
{
    if (psBuf == NULL)
    {
        // Connection closed
        tcp_close(psPcb);
        return ERR_OK;
    }

    // Echo received data
    tcp_write(psPcb, psBuf->payload, psBuf->len, TCP_WRITE_FLAG_COPY);
    tcp_output(psPcb);
    pbuf_free(psBuf);

    return ERR_OK;
}


/**
 * @brief TCP accept callback for handling new client connections.
 *
 * Called by LwIP when a new client successfully connects to the server port.
 * Stores the client PCB and sets up the receive callback.
 * Sends an initial welcome message to the connected client.
 *
 * @param arg User-supplied argument (not used here).
 * @param psNewPcb Pointer to the new TCP control block for the incoming connection.
 * @param sbErr Error status for the connection attempt.
 * @return err_t Returns ERR_OK to accept the connection.
 */
static err_t TCPDefaultAccept(void *arg, struct tcp_pcb *psNewPcb, err_t sbErr)
{
    tcp_recv(psNewPcb, TCPDefaultReceive);
    return ERR_OK;
}


