/**
 * @file    TftpServer.h
 * @brief   Header for TFTP server implementation on i.MX RT1064.
 *
 * Provides the interface to initialize a basic TFTP server over UDP using lwIP.
 *
 * (C) Copyright Centum T&S Group 2025. All rights reserved.
 * This computer program may not be used, copied, distributed, translated, transmitted or assigned
 * without the prior written authorization of Centum T&S Group.
 */
#ifndef ETHERNETINTERFACE_PROTOCOLS_TFTPSERVER_H_
#define ETHERNETINTERFACE_PROTOCOLS_TFTPSERVER_H_

//------------------------------------ [ INCLUDE FILES ] ----------------------------

#include "lwip/ip_addr.h"
#include "lwip/udp.h"

//---------------------------------------- [ DEFINES ] ------------------------------

//---------------------------------------- [ TYPEDEF ] ------------------------------
typedef enum
{
    TFTP_OK = 0,             /**< Initialization successful */
    TFTP_ERR_MEM_ALLOC,      /**< Failed to allocate UDP PCB */
    TFTP_ERR_BIND_FAILED     /**< Failed to bind to requested port */
} TFTPError_t;
//-------------------------------------- [ PROTOTYPES ] -----------------------------

/**
 * @brief Initializes the TFTP server and binds it to the specified UDP port.
 *
 * Sets up a UDP PCB and registers a receive callback for handling TFTP packets.
 *
 * @param ServerPort The UDP port on which the TFTP server should listen.
 * @return Pointer to the initialized UDP PCB, or NULL if initialization fails.
 */

TFTPError_t TFTP_ServerInit(struct udp_pcb *psPcb, u16_t usServerPort);

#endif /* ETHERNETINTERFACE_PROTOCOLS_TFTPSERVER_H_ */
