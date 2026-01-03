/**
 * @file    MessageProtocolParser.c
 * @brief   * @brief   EMP message processing module for parsing, payload extraction, and response generation.
 *
 * (C) Copyright Centum T&S Group 2025. All rights reserved.
 * This computer program may not be used, copied, distributed, translated, transmitted or assigned
 * without the prior written authorization of Centum T&S Group.
 *
 **/

#include "MessageProtocolParser.h"
#include "ReceivingMessageQueue.h"
#include "MessageData.h"
#include "../SessionManager/SessionManager.h"
#include "application/MessageHandler/ProcessCommand.h"
#include "common/CommonDefs.h"
#include <string.h>

// ------------------------ EMP Protocol Constants ------------------------
#define EMP_VERSION_MAJ             1
#define EMP_VERSION_MIN             0
#define EMP_TRANSACTION_ID_MAX      0x7FFF
#define EMP_SESSION_ID_MAX          0xFFFF
#define EMP_NLC                     0x8000
#define EMP_RR_MASK                 0x8000
#define EMP_RR_REQUEST              0x0000
#define EMP_RR_RESPONSE             0x8000
#define EMP_MSG_STDEXT              0x0000
#define EMP_MSG_DISC                0x0001
#define EMP_EQMT_180T               0x0001
#define EMP_MSG_TYPE_MASK   		0x7FFF

// Protocol header byte offsets
#define EMP_HDROFF_LEN              0
#define EMP_HDROFF_VERMAJ           1
#define EMP_HDROFF_VERMIN           2
#define EMP_HDROFF_SID              4
#define EMP_HDROFF_NLC_TID          6
#define EMP_HDROFF_RR_MSGTYPE       8
#define EMP_HDROFF_EQMTTYPE         10
#define EMP_HDROFF_STIMEOUT         12
#define EMP_HDROFF_RESERVED_1       14
#define EMP_HDROFF_HDRLEN           16  // Total header length

/*          Constants        */
#define MAX_RESPONSE_FRAME_LEN 	1536
#define MAX_RAW_MESSAGE_LEN 	1536

// ------------------- Static Variables -------------------

static uint8_t s_ubRawMsgBuffer[MAX_RAW_MESSAGE_LEN];
static uint16_t s_usRawMsgLength;
static ip_addr_t gsSourceIp;
static uint16_t gusSourcePort;

/* ------------------------------------------------------------------------- */
/* Internal Structures (Hidden from external modules)                        */
/* ------------------------------------------------------------------------- */

/**
 * @brief Messaging Layer header structure (raw wire format).
 */
typedef struct __attribute__((packed))
{
    uint8_t ubEquipmentAddress;       /* Byte 0: Equipment address, origin(bit1), fixed bit0=1 */
    uint8_t ubVersionAndReserved;     /* Byte 1: Bits 2-0 = version, Bits 7-3 = 11110 */
    uint8_t ubChannelNumberLSB;       /* Byte 2 */
    uint8_t ubChannelNumberMSB;       /* Byte 3 */
    uint8_t ubExtendedAddress;        /* Byte 4 */
    uint8_t ubRequestNumberLSB;       /* Byte 5 */
    uint8_t ubRequestNumberMSB;       /* Byte 6 */
    uint8_t ubDataLengthLSB;          /* Byte 7 */
    uint8_t ubDataLengthMSB;          /* Byte 8 */
} sMessagingLayerHeader_t;

/**
 * @brief Parsed EMP message structure holding all extracted fields.
 */
/* Parsed EMP Message */
struct parsed_emp_message_t
{
    uint8_t ubHeaderLength;
    uint8_t ubVersionMajor;
    uint8_t ubVersionMinor;
    uint16_t usSessionId;
    bool bNlc;
    uint16_t usTransactionId;
    bool bIsResponse;
    uint16_t usMessageType;
    uint16_t usEquipmentType;
    uint16_t usSessionTimeout;
    sMessagingLayerHeader_t sMessagingHeader;
    const uint8_t* pubPayloadPtr;
    uint16_t usPayloadLen;
};

/* ------------------------------------------------------------------------- */
/* Init Function                                                             */
/* ------------------------------------------------------------------------- */

/**
 * @brief Initializes internal message protocol parser state.
 */
void MessageProtocolParser_Init(void)
{
    s_usRawMsgLength = 0U;
    memset(s_ubRawMsgBuffer, 0, sizeof(s_ubRawMsgBuffer));
    memset(&gsSourceIp, 0, sizeof(ip_addr_t));
    gusSourcePort = 0U;
}

/**
 * @brief Processes all incoming EMP messages from the receive queue.
 *
 * This function dequeues raw UDP buffers, parses EMP headers, extracts payloads,
 * and invokes the response sender for valid messages.
 *
 * @note This function loops over all messages in the queue and processes them synchronously.
 * @warning Invalid frames are skipped and logged; the session state is updated accordingly.
 */
uint8_t MessageProtocolParser_ReceiveMessage(void)
{
    uint8_t ubIsprocessed = FAILURE;

    while (ReceivingMessageQueue_IsEmpty() == 0U)
    {
        uint8_t  aubPayload[MAX_UDP_PAYLOAD_SIZE];
        uint16_t usLength = 0U;
        ip_addr_t tsSourceIp;
        uint16_t usSourcePort = 0U;

        uint8_t ubDequeued = ReceivingMessageQueue_DequeueUDPBuffer(
                                aubPayload, &usLength,
                                &tsSourceIp, &usSourcePort);

        if (ubDequeued == 1U)
        {
            if (usLength <= MAX_RAW_MESSAGE_LEN)
            {
                memcpy(s_ubRawMsgBuffer, aubPayload, usLength);
                memcpy(&gsSourceIp, &tsSourceIp, sizeof(tsSourceIp));
                gusSourcePort = usSourcePort;
                s_usRawMsgLength  = usLength;

                parsed_emp_message_t stEmpParsed;
                uint8_t ubParseStatus = MessageProtocolParser_ParseHeader(
                                            s_ubRawMsgBuffer,
                                            s_usRawMsgLength,
                                            &stEmpParsed);

                if (ubParseStatus == 1U)
                {
                    uint16_t usPayloadLen = 0U;
                    COSLOG_INFO("Parsed and payload extracted. Len = %u\r\n", usPayloadLen);
                    ubIsprocessed = SUCCESS;
                }
                else
                {
                    COSLOG_ERROR("MessageProtocolParser_ParseHeader failed.\r\n");
                }
            }
            else
            {
                COSLOG_ERROR("Message too long (%u bytes)\r\n", (unsigned int)usLength);
            }
        }
        else
        {
            COSLOG_ERROR("Failed to dequeue raw UDP message\r\n");
        }
    }

    return ubIsprocessed;
}


/**
 * @brief Parses and validates the EMP protocol header and messaging layer.
 *
 * This function checks the EMP frame version, session ID, message type, transaction ID,
 * and messaging layer fields including origin, equipment address, channel, and request.
 * It populates the parsed_emp_message_t structure with decoded information.
 *
 * @param[in]  buffer    Pointer to raw EMP message buffer.
 * @param[in]  length    Length of the message buffer.
 * @param[out] outMsg    parsed_emp_message_t struct to fill with header information.
 *
 * @retval 1U  If the header is valid and parsed successfully.
 * @retval 0U If any validation fails or the buffer is too short.
 *
 * @note Updates session and transaction tracking state.
 */

uint8_t MessageProtocolParser_ParseHeader(const uint8_t* pubBuffer, uint16_t usLength, parsed_emp_message_t* pstOutMsg)
{
    uint8_t ubStatus = FAILURE;

    do {
        if (pubBuffer == NULL || pstOutMsg == NULL || usLength < EMP_HDROFF_HDRLEN)
        {
        	COSLOG_INFO("Invalid input or buffer too short. Length = %u\r\n", usLength);
            break;
        }
        else
        {
        	COSLOG_ERROR("Input buffer and pointers valid, length = %u\r\n", usLength);
        }

        pstOutMsg->ubHeaderLength = pubBuffer[EMP_HDROFF_LEN];
        if (pstOutMsg->ubHeaderLength != EMP_HDROFF_HDRLEN)
        {
        	COSLOG_INFO("Invalid header length. Got %u, expected %u\r\n",
                   pstOutMsg->ubHeaderLength, EMP_HDROFF_HDRLEN);
            break;
        }
        else
        {
        	COSLOG_ERROR("Valid header length = %u\r\n", pstOutMsg->ubHeaderLength);
        }

        pstOutMsg->ubVersionMajor = pubBuffer[EMP_HDROFF_VERMAJ];
        pstOutMsg->ubVersionMinor = pubBuffer[EMP_HDROFF_VERMIN];
        if (pstOutMsg->ubVersionMajor != EMP_VERSION_MAJ || pstOutMsg->ubVersionMinor != EMP_VERSION_MIN)
        {
            COSLOG_ERROR("Unsupported version %u.%u (expected %u.%u)\r\n",
                   pstOutMsg->ubVersionMajor, pstOutMsg->ubVersionMinor,
                   EMP_VERSION_MAJ, EMP_VERSION_MIN);
            break;
        }
        else
        {
            COSLOG_INFO("Version check passed: %u.%u\r\n",
                   pstOutMsg->ubVersionMajor, pstOutMsg->ubVersionMinor);
        }
        /* Session ID */
        memcpy(&pstOutMsg->usSessionId, &pubBuffer[EMP_HDROFF_SID], sizeof(uint16_t));
        pstOutMsg->usSessionId = swap16(pstOutMsg->usSessionId);

        /* Response flag + message type */
        uint16_t usRRMsgType;
        memcpy(&usRRMsgType, &pubBuffer[EMP_HDROFF_RR_MSGTYPE], sizeof(uint16_t));
        usRRMsgType = swap16(usRRMsgType);

        if ((usRRMsgType & EMP_RR_MASK) != 0U)
        {
            pstOutMsg->bIsResponse = SUCCESS;
        }
        else
        {
            pstOutMsg->bIsResponse = FAILURE;
        }
        pstOutMsg->usMessageType = usRRMsgType & EMP_MSG_TYPE_MASK;

        /* NLC + Transaction ID */
        uint16_t usNlcTid;
        memcpy(&usNlcTid, &pubBuffer[EMP_HDROFF_NLC_TID], sizeof(uint16_t));
        usNlcTid = swap16(usNlcTid);

        if ((usNlcTid & EMP_NLC) != 0U)
        {
            pstOutMsg->bNlc = SUCCESS;
        }
        else
        {
            pstOutMsg->bNlc = FAILURE;
        }
        pstOutMsg->usTransactionId = usNlcTid & EMP_TRANSACTION_ID_MAX;
        COSLOG_INFO("Transaction ID: %u\r\n", pstOutMsg->usTransactionId);

        /* Response flag + message type */
        pstOutMsg->usMessageType = usRRMsgType & EMP_MSG_TYPE_MASK;

        if ((pstOutMsg->bIsResponse == 1U) && (pstOutMsg->bNlc == 1U))
        {
        	COSLOG_ERROR("Response should not set NLC flag\r\n");
            break;
        }
        else
        {
        	COSLOG_INFO("Response/NLC flag combination OK\r\n");
        }

        if (pstOutMsg->usMessageType > 2U)
        {
        	COSLOG_ERROR("Invalid message type: %u\r\n", pstOutMsg->usMessageType);
            break;
        }
        else
        {
        	COSLOG_INFO("Valid message type = %u\r\n", pstOutMsg->usMessageType);
        }

        /* Equipment type */
        memcpy(&pstOutMsg->usEquipmentType, &pubBuffer[EMP_HDROFF_EQMTTYPE], sizeof(uint16_t));
        pstOutMsg->usEquipmentType = swap16(pstOutMsg->usEquipmentType);

        /* Session timeout */
        memcpy(&pstOutMsg->usSessionTimeout, &pubBuffer[EMP_HDROFF_STIMEOUT], sizeof(uint16_t));
        pstOutMsg->usSessionTimeout = swap16(pstOutMsg->usSessionTimeout);

        if (SessionManager_SessionHandling(pstOutMsg) == FAILURE)
        {
            break;
        }


        if (usLength < (EMP_HDROFF_HDRLEN + sizeof(sMessagingLayerHeader_t)))
        {
        	COSLOG_ERROR("Incomplete sMessagingLayerHeader_t\r\n");
            break;
        }
        else
        {
        	COSLOG_INFO("Enough length for MessagingLayerHeader: %u bytes\r\n", usLength);
        }

        memcpy(&pstOutMsg->sMessagingHeader, pubBuffer + EMP_HDROFF_HDRLEN, sizeof(sMessagingLayerHeader_t));
        const sMessagingLayerHeader_t* pstHeader = &pstOutMsg->sMessagingHeader;

        uint8_t ubEquipAddrRaw = pstHeader->ubEquipmentAddress;
        uint8_t ubOriginBit = (ubEquipAddrRaw >> 1U) & 0x01U;
        uint8_t ubEquipmentAddress = (ubEquipAddrRaw >> 2U) & 0x3FU;
        uint8_t ubVersion = pstHeader->ubExtendedAddress & 0x07U;
        uint16_t usChannel = ((uint16_t)pstHeader->ubChannelNumberMSB << 8U) | pstHeader->ubChannelNumberLSB;
        uint16_t usRequestNumber = ((uint16_t)pstHeader->ubRequestNumberMSB << 8U) | pstHeader->ubRequestNumberLSB;
        uint16_t usDataLength = ((uint16_t)pstHeader->ubDataLengthMSB << 8U) | pstHeader->ubDataLengthLSB;

        COSLOG_INFO("Messaging Layer:\r\n"
        "  Equipment Addr (Raw): 0x%02X | Parsed: 0x%02X\r\n"
        "  Origin: %s\r\n"
        "  Version: %u\r\n"
        "  Channel: %u\r\n"
        "  Extended Addr: 0x%02X\r\n"
        "  Request Number: %u\r\n"
        "  Data Length: %u\r\n",
        ubEquipAddrRaw,
        ubEquipmentAddress,
        (ubOriginBit != 0U ? "Response" : "Request"),
        ubVersion,
        usChannel,
        pstHeader->ubExtendedAddress,
        usRequestNumber,
        usDataLength
		);

        if (SessionManager_ValidateMessage(pstOutMsg, usRequestNumber) == FAILURE)
        {
            break;
        }

        pstOutMsg->pubPayloadPtr = pubBuffer + EMP_HDROFF_HDRLEN + sizeof(sMessagingLayerHeader_t);
        pstOutMsg->usPayloadLen = usLength - (EMP_HDROFF_HDRLEN + sizeof(sMessagingLayerHeader_t));

        COSLOG_INFO("Header parsed successfully. SessionID: 0x%04X | TID: 0x%04X | MsgType: %u\r\n",
               pstOutMsg->usSessionId, pstOutMsg->usTransactionId, pstOutMsg->usMessageType);

        MessageData_SetFields(ubEquipmentAddress,
                              ubOriginBit,
                              ubVersion,
                              usChannel,
                              pstHeader->ubExtendedAddress,
                              usRequestNumber,
                              usDataLength,
                              pstOutMsg->pubPayloadPtr);

        ubStatus = SUCCESS;
    } while (0U);

    return ubStatus;
}

/**
 * @brief Builds a response header with updated fields.
 *
 * @param pubOutBuffer Pointer to output buffer where header is written.
 * @param usOutBufferSize Size of the output buffer in bytes.
 * @param pusHeaderLengthOnly Pointer to store the length of the header written.
 * @return SUCCESS (1U) if header is built successfully, else FAILURE (0U).
 */
static uint8_t BuildResponseHeader(uint8_t* pubOutBuffer, uint16_t usOutBufferSize, uint16_t* pusHeaderLengthOnly)
{
    uint8_t ubStatus = FAILURE;

    if ((pubOutBuffer != NULL) && (pusHeaderLengthOnly != NULL))
    {
        uint16_t usRequiredHeaderLen = EMP_HDROFF_HDRLEN + (uint16_t)sizeof(sMessagingLayerHeader_t);

        if ((usOutBufferSize >= usRequiredHeaderLen) && (s_usRawMsgLength >= usRequiredHeaderLen))
        {
            (void)memcpy(pubOutBuffer, s_ubRawMsgBuffer, EMP_HDROFF_HDRLEN);

            pubOutBuffer[EMP_HDROFF_HDRLEN] = s_ubRawMsgBuffer[EMP_HDROFF_HDRLEN] | 0x80U;

            sMessagingLayerHeader_t* pstMsgHeader = (sMessagingLayerHeader_t*)(pubOutBuffer + EMP_HDROFF_HDRLEN);
            (void)memset(pstMsgHeader, 0, sizeof(sMessagingLayerHeader_t));

            pstMsgHeader->ubEquipmentAddress = MessageData_GetEquipmentAddress() | 0x01U;

            uint16_t usChannel = MessageData_GetChannelNumber();
            pstMsgHeader->ubChannelNumberLSB = (uint8_t)(usChannel & 0x00FFU);
            pstMsgHeader->ubChannelNumberMSB = (uint8_t)((usChannel >> 8U) & 0x00FFU);

            pstMsgHeader->ubExtendedAddress = MessageData_GetExtendedAddress();

            uint16_t usRequestNum = MessageData_GetRequestNumber();
            pstMsgHeader->ubRequestNumberLSB = (uint8_t)(usRequestNum & 0x00FFU);
            pstMsgHeader->ubRequestNumberMSB = (uint8_t)((usRequestNum >> 8U) & 0x00FFU);


            *pusHeaderLengthOnly = usRequiredHeaderLen;
            ubStatus = SUCCESS;
        }
        else
            {
            COSLOG_ERROR("Buffer too small. OutputSize = %u, RawMsgLen = %u, Required = %u\r\n",
                       usOutBufferSize, s_usRawMsgLength, usRequiredHeaderLen);
            }
    }
    else
        {
        COSLOG_ERROR("[NULL input. OutBuffer = %p, HeaderLenPtr = %p\r\n",
                   (void*)pubOutBuffer, (void*)pusHeaderLengthOnly);
        }

    return ubStatus;
}

/**
 * @brief Retrieves the response buffer constructed by BuildResponseHeader().
 *
 * @param[out] bufferOut   Pointer to pointer where response buffer address will be stored.
 * @param[out] lengthOut   Pointer to variable to receive the length of the response buffer.
 *
 * @retval 1U  If a valid response was built and returned.
 * @retval 0U If BuildResponseHeader() failed.
 */
uint8_t MessageProtocolParser_SendResponse(const uint8_t* ptubPayload, uint16_t usPayloadLength)
{
    uint8_t aubResponseFrame[MAX_RESPONSE_FRAME_LEN] = {0};
    uint16_t usResponseFrameLength = 0U;
    uint8_t ubSendStatus = FAILURE;
    uint8_t ubHeaderBuildStatus = FAILURE;
    uint8_t ubPayloadCheckStatus = FAILURE;
    uint8_t ubFinalStatus = FAILURE;

    ubHeaderBuildStatus = BuildResponseHeader(aubResponseFrame,
                                              sizeof(aubResponseFrame),
                                              &usResponseFrameLength);

    if (ubHeaderBuildStatus == SUCCESS)
    {
        if ((ptubPayload != NULL) && (usPayloadLength > 0U))
        {
            ubPayloadCheckStatus = SUCCESS;
        }
        else
        {
            COSLOG_ERROR("Invalid payload. Ptr = %p, Len = %u\r\n",
                   (const void*)ptubPayload, usPayloadLength);
        }

        if ((ubPayloadCheckStatus == SUCCESS) &&
            ((usResponseFrameLength + usPayloadLength) <= (uint16_t)sizeof(aubResponseFrame)))
        {
            (void)memcpy(&aubResponseFrame[usResponseFrameLength],
                         ptubPayload, usPayloadLength);

            usResponseFrameLength += usPayloadLength;
            ubFinalStatus = SUCCESS;
        }
        else
        {
            COSLOG_ERROR("Payload too large or invalid. "
                   "HeaderLen = %u, PayloadLen = %u, Max = %u\r\n",
                   usResponseFrameLength, usPayloadLength,
                   (uint16_t)sizeof(aubResponseFrame));
        }
    }
    else
    {
        COSLOG_ERROR("Failed to build response header.\r\n");
    }

    if (ubFinalStatus == SUCCESS)
    {
    	UdpHandler_SendMessage(gptUdpPcbPid , &gsSourceIp, gusSourcePort,
                           aubResponseFrame, usResponseFrameLength);

        ubSendStatus = SUCCESS;
    }
    else
    {
        COSLOG_ERROR("Failed to send message due to earlier error.\r\n");
    }

    return ubSendStatus;
}

/**
 * @brief Get the session ID from a parsed EMP message.
 *
 * @param msg Pointer to parsed EMP message structure.
 * @return Session ID, or 0 if msg is NULL.
 */
uint16_t MessageProtocolParser_GetSessionId(const parsed_emp_message_t* msg)
{
    uint16_t usValue = 0U;

    if (msg != NULL)
    {
        usValue = msg->usSessionId;
    }

    return usValue;
}


/**
 * @brief Get the message type from a parsed EMP message.
 *
 * @param msg Pointer to parsed EMP message structure.
 * @return Message type, or 0 if msg is NULL.
 */
uint16_t MessageProtocolParser_GetMessageType(const parsed_emp_message_t* msg)
{
    uint16_t usValue = 0U;

    if (msg != NULL)
    {
        usValue = msg->usMessageType;
    }

    return usValue;
}

/**
 * @brief Get the transaction ID from a parsed EMP message.
 *
 * @param msg Pointer to parsed EMP message structure.
 * @return Transaction ID, or 0 if msg is NULL.
 */
uint16_t MessageProtocolParser_GetTransactionId(const parsed_emp_message_t* msg)
{
    uint16_t usValue = 0U;

    if (msg != NULL)
    {
        usValue = msg->usTransactionId;
    }

    return usValue;
}

/**
 * @brief Check if the parsed EMP message is a response.
 *
 * @param msg Pointer to parsed EMP message structure.
 * @return true if it is a response, false if not or if msg is NULL.
 */
bool MessageProtocolParser_IsResponse(const parsed_emp_message_t* msg)
{
    bool bValue = false;

    if (msg != NULL)
    {
        bValue = msg->bIsResponse;
    }

    return bValue;
}

/**
 * @brief Get the equipment type from a parsed EMP message.
 *
 * @param msg Pointer to parsed EMP message structure.
 * @return Equipment type, or 0 if msg is NULL.
 */
uint16_t MessageProtocolParser_GetEquipmentType(const parsed_emp_message_t* msg)
{
    uint16_t usValue = 0U;

    if (msg != NULL)
    {
        usValue = msg->usEquipmentType;
    }

    return usValue;
}

/**
 * @brief Get the session timeout from a parsed EMP message.
 *
 * @param msg Pointer to parsed EMP message structure.
 * @return Session timeout in protocol units, or 0 if msg is NULL.
 */
uint16_t MessageProtocolParser_GetSessionTimeout(const parsed_emp_message_t* msg)
{
    uint16_t usValue = 0U;

    if (msg != NULL)
    {
        usValue = msg->usSessionTimeout;
    }

    return usValue;
}

