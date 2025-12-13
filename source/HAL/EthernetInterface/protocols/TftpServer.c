/**
 * @file    TftpServer.c
 * @brief   TFTP server implementation using lwIP stack.
 *
 * This module implements a simple TFTP server that responds to RRQ (read requests)
 * by serving pre-defined files, and WRQ (write requests) by acknowledging received data blocks.
 *
 * (C) Copyright Centum T&S Group 2025. All rights reserved.
 * This computer program may not be used, copied, distributed, translated, transmitted or assigned
 * without the prior written authorization of Centum T&S Group.
 */

//------------------------------------ [ INCLUDE FILES ] ----------------------------

#include <HAL/EthernetInterface/protocols/TftpServer.h>
#include "lwip/udp.h"
#include "lwip/ip_addr.h"
#include "lwip/mem.h"
#include "lwip/pbuf.h"
#include "lwip/inet.h"
#include <string.h>
#include <stdio.h>

//------------------------------------- [ DEFINES ] ----------------------------------

#define TFTP_OPCODE_RRQ   1
#define TFTP_OPCODE_WRQ   2
#define TFTP_OPCODE_DATA  3
#define TFTP_OPCODE_ACK   4
#define TFTP_OPCODE_ERROR 5

#define TFTP_DATA_SIZE 512

//------------------------------------- [ TYPEDEF ] ----------------------------------

typedef struct {
    const char *filename;
    const uint8_t *data;
    uint32_t length;
} FileEntry;


//------------------------------------- [ STATIC VARIABLE ] --------------------------

static const uint8_t ubFile1Data[] = {0xAA, 0xBB, 0xCC, 0xDD };
static const uint8_t ubFile2Data[] = {0xEE, 0xFF, 0xAB, 0xCD };
static const uint8_t ubFile3Data[] = {0xFF, 0xEE, 0xDD, 0xCC };

static const FileEntry sFileTable[] = {
    { "eeprom.bin", ubFile1Data, sizeof(ubFile1Data) },
    { "application.bin", ubFile2Data, sizeof(ubFile2Data) },
	{ "font.bin", ubFile3Data, sizeof(ubFile3Data) },
};

static u16_t usBlockNumber = 0;
static const FileEntry *psCurrentFile = NULL;
static uint32_t ulFileOffset = 0;


//------------------------------------- [ LOCAL PROTOTYPES ] -------------------------

static void SendError(struct udp_pcb *psPcb, const ip_addr_t *psAddr, u16_t usPort, u16_t usErrorCode, const char *pErrMsg);
static void SendDataBlock(struct udp_pcb *psPcb, const ip_addr_t *psAddr, u16_t usPort, u16_t usBlock, const FileEntry *psCurrentFile, uint32_t *pulOffset);
static void SendAck(struct udp_pcb *psPcb, const ip_addr_t *psAddr, u16_t usPort, u16_t usBlock);
static void TftpReceive(void *arg, struct udp_pcb *psPcb, struct pbuf *psBuf, const ip_addr_t *psAddr, u16_t usPort);

//------------------------------------- [ GLOBAL FUNCTIONS ] -------------------------

/**
 * @brief Initializes the TFTP server and binds to the specified port.
 *
 * Creates and configures a UDP PCB for handling TFTP read/write requests.
 *
 * @param usServerPort Port number to bind the server to.
 * @return Pointer to the UDP PCB if successful, or NULL on failure.
 */
TFTPError_t TFTP_ServerInit(struct udp_pcb *psPcb, u16_t usServerPort)
{
	if (psPcb == NULL)
	{
		return TFTP_ERR_MEM_ALLOC;
	}

	if (udp_bind(psPcb, IP_ADDR_ANY, usServerPort) == ERR_OK)
	{
		udp_recv(psPcb, TftpReceive, NULL);
		return TFTP_OK;
	}

	else
	{
		udp_remove(psPcb);
		return TFTP_ERR_BIND_FAILED;
	}

}

//------------------------------------- [ LOCAL FUNCTIONS ] --------------------------

/**
 * @brief Sends a TFTP error packet to the client.
 *
 * @param psPcb       Pointer to the UDP PCB.
 * @param addr      Client IP address.
 * @param usPort      Client port number.
 * @param usErrorCode TFTP error code.
 * @param pErrMsg    Human-readable error message.
 */
static void SendError(struct udp_pcb *psPcb, const ip_addr_t *psAddr, u16_t usPort, u16_t usErrorCode, const char *pErrMsg)
{
    uint8_t ubaBuffer[512];
    size_t MsgLen = strlen(pErrMsg);
    ubaBuffer[0] = 0;
    ubaBuffer[1] = TFTP_OPCODE_ERROR;
    ubaBuffer[2] = (usErrorCode >> 8) & 0xFF;
    ubaBuffer[3] = usErrorCode & 0xFF;
    memcpy(&ubaBuffer[4], pErrMsg, MsgLen);
    ubaBuffer[4 + MsgLen] = 0;

    struct pbuf *psBuf = pbuf_alloc(PBUF_TRANSPORT, 5 + MsgLen, PBUF_RAM);
    if (psBuf)
    {
        memcpy(psBuf->payload, ubaBuffer, 5 + MsgLen);
        udp_sendto(psPcb, psBuf, psAddr, usPort);
        pbuf_free(psBuf);
    }
}

/**
 * @brief Sends a data block to the client in response to a read request.
 *
 * @param psPcb         Pointer to the UDP PCB.
 * @param psAddr        Client IP address.
 * @param usPort        Client port.
 * @param block       Block number to send.
 * @param psCurrentFile Pointer to the file entry.
 * @param offset      Pointer to the current offset in the file.
 */
static void SendDataBlock(struct udp_pcb *psPcb,
                          const ip_addr_t *psAddr,
                          u16_t usPort,
                          u16_t usBlock,
                          const FileEntry *psCurrentFile,
                          uint32_t *pulOffset)
{
    uint8_t ubaTxBuffer[4 + TFTP_DATA_SIZE];
    uint16_t usDataLength = 0;

    if (!psCurrentFile || !pulOffset || *pulOffset >= psCurrentFile->length)
    {
        usDataLength = 0;
    }
    else
    {
        usDataLength = psCurrentFile->length - *pulOffset;
        if (usDataLength > TFTP_DATA_SIZE)
            usDataLength = TFTP_DATA_SIZE;
    }

    ubaTxBuffer[0] = 0;
    ubaTxBuffer[1] = TFTP_OPCODE_DATA;
    ubaTxBuffer[2] = (usBlock >> 8) & 0xFF;
    ubaTxBuffer[3] = usBlock & 0xFF;

    memcpy(&ubaTxBuffer[4], &psCurrentFile->data[*pulOffset], usDataLength);
    *pulOffset += usDataLength;

    struct pbuf *psBuf = pbuf_alloc(PBUF_TRANSPORT, 4 + usDataLength, PBUF_RAM);
    if (psBuf)
    {
        memcpy(psBuf->payload, ubaTxBuffer, 4 + usDataLength);
        udp_sendto(psPcb, psBuf, psAddr, usPort);
        pbuf_free(psBuf);
    }
}

/**
 * @brief Sends an ACK packet to the client (used during WRQ).
 *
 * @param psPcb   Pointer to UDP PCB.
 * @param psAddr  Client IP address.
 * @param usPort  Client port.
 * @param usBlock Block number to acknowledge.
 */
static void SendAck(struct udp_pcb *psPcb, const ip_addr_t *psAddr, u16_t usPort, u16_t usBlock)
{
    uint8_t ubaTxBuffer[4] = {0, TFTP_OPCODE_ACK, (usBlock >> 8) & 0xFF, usBlock & 0xFF};

    struct pbuf *psBuf = pbuf_alloc(PBUF_TRANSPORT, 4, PBUF_RAM);
    if (psBuf)
    {
        memcpy(psBuf->payload, ubaTxBuffer, 4);
        udp_sendto(psPcb, psBuf, psAddr, usPort);
        pbuf_free(psBuf);
    }
}

/**
 * @brief UDP receive callback for handling TFTP packets.
 *
 * Processes RRQ, WRQ, DATA, and ACK TFTP messages.
 *
 * @param arg   Unused argument.
 * @param psPcb   Pointer to UDP PCB.
 * @param psBuf     Pointer to received pbuf.
 * @param psAddr  Sender IP address.
 * @param usPort  Sender port number.
 */
static void TftpReceive(void *arg, struct udp_pcb *psPcb, struct pbuf *psBuf,
                        const ip_addr_t *psAddr, u16_t usPort)
{
    if (!psBuf || psBuf->len < 4)
    {
        pbuf_free(psBuf);
        return;
    }
    uint8_t *pubData = (uint8_t *)psBuf->payload;
    uint16_t usOpcode = (pubData[0] << 8) | pubData[1];


    if (usOpcode == TFTP_OPCODE_WRQ || usOpcode == TFTP_OPCODE_RRQ)
    {
        char aFilename[128];
        int i = 2, j = 0;
        while (i < psBuf->len && pubData[i] != 0 && j < sizeof(aFilename) - 1)
        {
            aFilename[j++] = pubData[i++];
        }
        aFilename[j] = '\0';

        if (usOpcode == TFTP_OPCODE_RRQ)
        {
            psCurrentFile = NULL;
            for (size_t k = 0; k < sizeof(sFileTable)/sizeof(FileEntry); k++)
            {
                if (strcmp(sFileTable[k].filename, aFilename) == 0)
                {
                    psCurrentFile = &sFileTable[k];
                    break;
                }
            }

            ulFileOffset = 0;
            usBlockNumber = 1;

            if (psCurrentFile)
            {
                SendDataBlock(psPcb, psAddr, usPort, usBlockNumber, psCurrentFile, &ulFileOffset);

            }
            else
            {
            	SendError(psPcb, psAddr, usPort, 1, "File not found");
            }
        }

        else
        {
            usBlockNumber = 0;
            SendAck(psPcb, psAddr, usPort, usBlockNumber);
        }
    }

    else if (usOpcode == TFTP_OPCODE_ACK)
    {
    	uint16_t usBlock = (pubData[2] << 8) | pubData[3];
		if (usBlock == usBlockNumber)
		{
			usBlockNumber++;
			SendDataBlock(psPcb, psAddr, usPort, usBlockNumber, psCurrentFile, &ulFileOffset);
		}
    }

    else if (usOpcode == TFTP_OPCODE_DATA)
    {
        uint16_t usBlock = (pubData[2] << 8) | pubData[3];

        PRINTF("Received WRQ block %d: ", usBlock);
        for (int i = 4; i < psBuf->len; i++)
        {
            PRINTF("%02X ", pubData[i]);
        }
        PRINTF("\r\n");

        SendAck(psPcb, psAddr, usPort, usBlock);
    }

    pbuf_free(psBuf);
}
