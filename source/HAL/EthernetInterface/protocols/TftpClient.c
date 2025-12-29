/**
 * @file    TftpClient.c
 * @brief   TFTP Client implementation using lwIP UDP.
 *
 * This module implements a TFTP client to download files from a TFTP server.
 *
 * (C) Copyright Centum T&S Group 2025. All rights reserved.
 * This computer program may not be used, copied, distributed, translated, transmitted or assigned
 * without the prior written authorization of Centum T&S Group.
 */

//------------------------------------ [ INCLUDE FILES ] ----------------------------

#include <HAL/EthernetInterface/protocols/TftpClient.h>
#include "lwip/udp.h"
#include "lwip/pbuf.h"
#include "lwip/ip_addr.h"
#include "string.h"
#include "stdio.h"

//-------------------------------------[ DEFINES ] ----------------------------------

#define TFTP_PORT                69
#define TFTP_OPCODE_RRQ          1
#define TFTP_OPCODE_DATA         3
#define TFTP_OPCODE_ACK          4
#define TFTP_BLOCK_SIZE          512
#define MODE                     "octet"

//-------------------------------------[ TYPEDEF ] ----------------------------------

//-------------------------------------[ STATIC VARIABLE ] --------------------------

static struct udp_pcb *psTftpPcb = NULL;
static u16_t usExpectedBlock = 1;
static size_t FileOffset = 0;
static uint8_t *ubFileBuffer = NULL;

//-------------------------------------[ LOCAL PROTOTYPES ] -------------------------

static void SendAck(struct udp_pcb *psPcb, const ip_addr_t *psAddr, u16_t usPort, u16_t usBlock);
static void TftpClientReceive(void *arg, struct udp_pcb *psPcb, struct pbuf *psBuf, const ip_addr_t *psAddr, u16_t usPort);

//-------------------------------------[ GLOBAL FUNCTIONS ] -------------------------

/**
 * @brief Starts the TFTP client to download a file from the server.
 *
 * Initializes UDP PCB, binds it, sets up the receive callback, and sends a Read Request (RRQ).
 *
 * @param psServerIP   Pointer to the TFTP server's IP address.
 * @param pFilename    Name of the file to be requested.
 * @param ubFileBuffer  Pointer to the buffer where file data will be stored.void *arg, struct tcp_pcb *psNewPcb, err_t sbErr
 */
void TFTPCLIENT_Start(const ip_addr_t *psServerIP, const char *pFilename, uint8_t *ubFileBuffer)
{
    PRINTF("TFTP Client starting...\r\n");
    ubFileBuffer = ubFileBuffer;
    FileOffset = 0;
    usExpectedBlock = 1;

    psTftpPcb = udp_new();
    if (!psTftpPcb) {
        PRINTF("Failed to create UDP PCB\r\n");
        return;
    }

    if (udp_bind(psTftpPcb, IP_ADDR_ANY, 0) != ERR_OK) {
        PRINTF("UDP bind failed\r\n");
        return;
    }

    udp_recv(psTftpPcb, TftpClientReceive, NULL);

    uint8_t ubBuffer[100];
    size_t Len = 0;

    ubBuffer[Len++] = 0;
    ubBuffer[Len++] = TFTP_OPCODE_RRQ;

    strcpy((char *)&ubBuffer[Len], pFilename);
    Len += strlen(pFilename) + 1;

    strcpy((char *)&ubBuffer[Len], MODE);
    Len += strlen(MODE) + 1;

    struct pbuf *psBuf = pbuf_alloc(PBUF_TRANSPORT, Len, PBUF_RAM);
    if (!psBuf)
    {
        PRINTF("Failed to allocate pbuf\r\n");
        return;
    }

    memcpy(psBuf->payload, ubBuffer, Len);

    err_t sbErr = udp_sendto(psTftpPcb, psBuf, psServerIP, TFTP_PORT);
    if (sbErr != ERR_OK)
    {
        PRINTF("udp_sendto failed: %d\r\n", sbErr);
    }
    else
    {
        PRINTF("TFTP RRQ sent to %s\r\n", ipaddr_ntoa(psServerIP));
    }

    pbuf_free(psBuf);
}

//-------------------------------------[ LOCAL FUNCTIONS ] --------------------------

/**
 * @brief Sends a TFTP ACK packet for the given block number to the server.
 *
 * @param psPcb Pointer to the UDP protocol control block.
 * @param psAddr Pointer to the server's IP address.
 * @param usPort Server port number to send the ACK to.
 * @param usBlock usBlock number being acknowledged.
 */
static void SendAck(struct udp_pcb *psPcb, const ip_addr_t *psAddr, u16_t usPort, u16_t usBlock)
{
	 uint8_t ubAcknowledgement[4] = { 0, TFTP_OPCODE_ACK, usBlock >> 8, usBlock & 0xFF };

    struct pbuf *psBuf = pbuf_alloc(PBUF_TRANSPORT, 4, PBUF_RAM);
    if (psBuf)
    {
        memcpy(psBuf->payload, ubAcknowledgement, 4);
        udp_sendto(psPcb, psBuf, psAddr, usPort);
        pbuf_free(psBuf);
    }
}


/**
 * @brief UDP receive callback for processing incoming TFTP DATA packets.
 *
 * Verifies block number, stores data in buffer, and sends ACK.
 * Detects transfer completion when data length < 512 bytes.
 *
 * @param arg   Unused user argument.
 * @param psPcb   Pointer to the UDP protocol control block.
 * @param psBuf     Pointer to the received pbuf.
 * @param psAddr  Pointer to sender's IP address.
 * @param usPort  Sender's port number.
 */

static void TftpClientReceive(void *arg, struct udp_pcb *psPcb,
                              struct pbuf *psBuf, const ip_addr_t *psAddr, u16_t usPort)
{
    if (!psBuf || psBuf->len < 4)
    {
    	//Discards packets less than 4 bytes, not valid TFTP data
        pbuf_free(psBuf);
        return;
    }

    uint8_t *pubPayload = (uint8_t *)psBuf->payload;
    uint16_t usOpcode = (pubPayload[0] << 8) | pubPayload[1];

    if (usOpcode == TFTP_OPCODE_DATA)
    {
        uint16_t usBlock = (pubPayload[2] << 8) | pubPayload[3];

        if (usBlock == usExpectedBlock)
        {
            size_t DataLen = psBuf->len - 4;
            memcpy(&ubFileBuffer[FileOffset], &pubPayload[4], DataLen);

            for (size_t i = 0; i < DataLen; i++)
            {
                PRINTF("%c", pubPayload[4 + i]);
            }

            FileOffset += DataLen;
            usExpectedBlock++;

            SendAck(psPcb, psAddr, usPort, usBlock);

            if (DataLen < TFTP_BLOCK_SIZE)
            {
                PRINTF("\nTFTP file transfer complete.\r\n");
            }
        }
    }

    pbuf_free(psBuf);
}


