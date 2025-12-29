/**
 * @file    tftp_test.c
 * @brief   Test implementation for TFTP server and client.
 *
 * This file demonstrates the initialization of a TFTP server and client.
 * It starts the server and requests a file from a specified TFTP server IP address.
 *
 * (C) Copyright Centum T&S Group 2025. All rights reserved.
 * This computer program may not be used, copied, distributed, translated, transmitted or assigned
 * without the prior written authorization of Centum T&S Group.
 */

//------------------------------------ [ INCLUDE FILES ] ----------------------------

#include <HAL/EthernetInterface/protocols/TftpClient.h>
#include <HAL/EthernetInterface/protocols/TftpServer.h>


//-------------------------------------[ DEFINES ] ----------------------------------

#define TFTP_PORT 69
#define TFTP_FILENAME "eeprom.bin"
#define FILE_BUFFER_SIZE 512

//------------------------------------- [ STATIC VARIABLE ] --------------------------
struct udp_pcb *psPcb;

//--------------------------------- [ GLOBAL FUNCTIONS ] ----------------------------
/**
 * @brief Initializes both TFTP server and client for testing.
 *
 * This function starts the TFTP server and initiates a TFTP client
 * file request from the specified server IP. It uses a local buffer
 * to store the received file.
 *
 * @param ServerIPAddr Pointer to the IP address of the remote TFTP server.
 */
void TftpInit(const ip_addr_t *psServerIPAddr)
{

	psPcb = udp_new();

	static uint8_t ubaFileBuffer[FILE_BUFFER_SIZE];

	TFTP_ServerInit(psPcb, TFTP_PORT);


	TFTPCLIENT_Start(psServerIPAddr, TFTP_FILENAME, ubaFileBuffer);

}
