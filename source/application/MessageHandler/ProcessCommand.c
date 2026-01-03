/**
 * @file    ProcessCommand.c
 * @brief   Provides command routing and processing logic for EMP request numbers.
 *
 * This module handles decoding of parsed EMP request numbers and dispatches them to
 * corresponding processing functions. It also provides response payloads for the requests.
 *
 * (C) Copyright Centum T&S Group 2025. All rights reserved.
 * This computer program may not be used, copied, distributed, translated, transmitted or assigned
 * without the prior written authorization of Centum T&S Group.
 */

#include "lwip/udp.h"
#include "lwip/ip_addr.h"
#include "ProcessCommand.h"
#include "HALInterface/Ethernet/UdpHandler.h"
#include "Middleware/MessageLayerParser/MessageProtocolParser.h"
#include "Middleware/MessageLayerParser/ReceivingMessageQueue.h"
#include "Middleware/MessageLayerParser/MessageData.h"
#include "InitializationCommand/InitializationRequest.h"
#include "InitializationCommand/InitializationResponce.h"
#include "MutualControlCommand/MutualControlRequest.h"
#include "MutualControlCommand/MutualControlResponse.h"

#include "common/CommonDefs.h"

/**
 * @enum eEMPRequestNumber_t
 * @brief Enum representing supported EMP request types.
 *
 * Each value corresponds to a request number as defined in the EMP protocol specification.
 */

typedef enum {
	EMP_INITIALIZATION             = 0,
	EMP_MUTUAL_CONTROL             = 1,
	EMP_READ_FIRST_LOG             = 4,
	EMP_READ_NEXT_LOG              = 5,
	EMP_ERASE_LOGS                 = 6,
	EMP_DOWNLOAD_FILE              = 8,
	EMP_VISUAL_TEST                = 13,
	EMP_FONT_BITMAP_VERSION        = 14,
	EMP_STRING_COMMANDS            = 20,
	EMP_LARGE_DOWNLOAD_FILE        = 22,
	EMP_UPLOAD_FILE                = 25,
	EMP_GET_DISPLAY_INFO           = 32,
	EMP_GET_TEMPERATURE_INFO       = 33,
	EMP_LOGIN                      = 35
} eEMPRequestNumber_t;
/**
 * @brief Routes command to appropriate handler and sets response payload.
 *
 * @param[out] respPayload  Pointer to the generated response buffer
 * @param[out] respLen      Length of the generated response
 *
 * @return true if routing was successful, false otherwise
 */
static uint8_t RouteCommand(const uint8_t** ppResponsePayload, uint16_t* pusResponseLen)
{
    const uint8_t* pubRequestPayload = MessageData_GetPayloadPointer();
    uint16_t usRequestLength = MessageData_GetDataLength();
    uint16_t usRequestNumber = MessageData_GetRequestNumber();
    uint8_t status = FAILURE;

    switch (usRequestNumber) {
        case EMP_INITIALIZATION:
        	COSLOG_INFO("Handling EMP_INITIALIZATION\r\n");
            if (InitializationRequest_Decode(pubRequestPayload, usRequestLength) == SUCCESS)
            {
                if (InitializationResponce_Encode(ppResponsePayload, pusResponseLen) == SUCCESS)
                {
                    status = SUCCESS;
                }
                else
                {
                    COSLOG_ERROR("Initialization response encode failed\r\n");
                }
            }
            else
            {
                COSLOG_ERROR("Initialization request decode failed\r\n");
            }
            break;
        case EMP_MUTUAL_CONTROL:
            COSLOG_INFO("Handling EMP_MUTUAL_CONTROL\r\n");
            if (MutualControlRequest_Decode(pubRequestPayload, usRequestLength) == SUCCESS)
            {
                if (MutualControlResponse_Encode(ppResponsePayload, pusResponseLen, 0U) == SUCCESS)
                {
                    status = SUCCESS;
                }
                else
                {
                    COSLOG_ERROR("Mutual Control response encode failed\r\n");
                }
            }
            else
            {
                COSLOG_ERROR("Mutual Control request decode failed\r\n");
            }
            break;
        default:
            COSLOG_INFO("unknown request (%u)\r\n", usRequestNumber);
            *ppResponsePayload = NULL;
            *pusResponseLen = 0;
            break;
    }
    return status;
}

/**
 * @brief Entry point for command parsing and response processing.
 *
 * This function performs the complete sequence of:
 * 1. Parsing the received EMP message (header + payload)
 * 2. Routing the command and generating a response payload
 * 3. Building the full EMP response and sending it over UDP
 *
 * Should be called after a message is dequeued from the receive queue.
 */
void ProcessCommand_HandleRequest(void)
{
    uint8_t ubStatus = FAILURE;

    /* Step 1: Parse and validate received message */
    ubStatus = MessageProtocolParser_ReceiveMessage();
    if (ubStatus == SUCCESS) {
    	PRINTF("MessageProtocolParser_ReceiveMessage\r\n");
    	/* Step 2: Route request and get response payload */
        const uint8_t* pubResponsePayload = NULL;
        uint16_t usResponseLength = 0;

        ubStatus = RouteCommand(&pubResponsePayload, &usResponseLength);
        if (ubStatus == SUCCESS) {

            /* Step 3: Build and send full response (header + msgLayer + payload) */
            ubStatus = MessageProtocolParser_SendResponse(pubResponsePayload, usResponseLength);
            if (ubStatus != SUCCESS)
            {
                COSLOG_ERROR("MessageProtocolParser_SendResponse failed\r\n");
            }
            else
            {
                /* Response sent successfully */
            }

        }
        else
        {
            COSLOG_ERROR("RouteCommand failed\r\n");
        }

    }
    else
    {
        /* Message not valid or session expired; optionally delete session */
    }
}
