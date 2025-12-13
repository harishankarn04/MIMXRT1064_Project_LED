/**
 * @file    TftpClient.h
 * @brief   Header file for TFTP client functionality using lwIP.
 *
 * This file provides the interface for starting a TFTP client session
 * to request and download a file from a TFTP server.
 *
 * (C) Copyright Centum T&S Group 2025. All rights reserved.
 * This computer program may not be used, copied, distributed, translated, transmitted or assigned
 * without the prior written authorization of Centum T&S Group.
 */

#ifndef ETHERNETINTERFACE_PROTOCOLS_TFTPCLIENT_H_
#define ETHERNETINTERFACE_PROTOCOLS_TFTPCLIENT_H_


//------------------------------------ [ INCLUDE FILES ] ----------------------------

#include "lwip/ip_addr.h"

//----------------------------------------[ DEFINES ] ------------------------------
//

//----------------------------------------[ TYPEDEF ] ------------------------------
//

//-------------------------------------- [ PROTOTYPES ] -----------------------------


void TFTPCLIENT_Start(const ip_addr_t *psServerIP, const char *pFilename, uint8_t *ubFileBuffer);

extern ip_addr_t psServerIP;


#endif /* ETHERNETINTERFACE_PROTOCOLS_TFTPCLIENT_H_ */
