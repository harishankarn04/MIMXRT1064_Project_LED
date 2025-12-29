/**
 * @file    MessageProtocolParser.h
 * @brief   Provides functions to parse, validate, and respond to EMP protocol messages.
 *
 * This module handles parsing of the EMP Header and Messaging Layer, extracting key fields,
 * building responses, and managing message flow for a UDP-based EMP protocol stack.
 *
 * (C) Copyright Centum T&S Group 2025. All rights reserved.
 * This computer program may not be used, copied, distributed, translated, transmitted or assigned
 * without the prior written authorization of Centum T&S Group.
 */

#ifndef MESSAGE_PROTOCOL_PARSER_H_
#define MESSAGE_PROTOCOL_PARSER_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "HALInterface/Ethernet/UdpHandler.h"

// ============================================================================
// Opaque Types
// ============================================================================

/**
 * @brief Parsed EMP message structure (opaque to callers).
 *
 * The full definition is kept private in the implementation (.c) file.
 * Applications interact with it only through the API functions below.
 */
typedef struct parsed_emp_message_t parsed_emp_message_t;

/**
 * @brief Initializes internal message protocol parser state.
 */
void MessageProtocolParser_Init(void);
/**
 * @brief Extracts the session ID from a parsed EMP message.
 *
 * @param msg Pointer to a parsed EMP message.
 * @return Session ID, or 0 if msg is NULL.
 */
uint16_t MessageProtocolParser_GetSessionId(const parsed_emp_message_t* msg);

/**
 * @brief Extracts the message type from a parsed EMP message.
 *
 * @param msg Pointer to a parsed EMP message.
 * @return Message type, or 0 if msg is NULL.
 */
uint16_t MessageProtocolParser_GetMessageType(const parsed_emp_message_t* msg);


/**
 * @brief Extracts the transaction ID from a parsed EMP message.
 *
 * @param msg Pointer to a parsed EMP message.
 * @return Transaction ID, or 0 if msg is NULL.
 */
uint16_t MessageProtocolParser_GetTransactionId(const parsed_emp_message_t* msg);


/**
 * @brief Checks if the message is a response.
 *
 * @param msg Pointer to a parsed EMP message.
 * @return true if response, false otherwise or if msg is NULL.
 */
bool     MessageProtocolParser_IsResponse(const parsed_emp_message_t* msg);

/**
 * @brief Extracts the session timeout value from a parsed EMP message.
 *
 * @param msg Pointer to a parsed EMP message.
 * @return Timeout value, or 0 if msg is NULL.
 */
uint16_t MessageProtocolParser_GetSessionTimeout(const parsed_emp_message_t* msg);

/**
 * @brief Processes all messages in the receive queue.
 *
 * This function repeatedly dequeues raw messages, parses them,
 * and triggers appropriate response construction and sending.
 *
 * @return Status code (0 = success, non-zero = error).
 */
uint8_t MessageProtocolParser_ReceiveMessage(void);

/**
 * @brief Parses an EMP message buffer and extracts header and messaging fields.
 *
 * @param pubBuffer         Pointer to input EMP message buffer.
 * @param usLength          Length of the input buffer.
 * @param pstOutMsg         Pointer to structure to store parsed output.
 *
 * @return 0 if successful, otherwise error code.
 */
uint8_t MessageProtocolParser_ParseHeader(const uint8_t* pubBuffer, uint16_t usLength, parsed_emp_message_t* pstOutMsg);

/**
 * @brief Sends the final EMP response (header + payload) to source.
 *
 * @param ptubPayload       Pointer to payload to be sent.
 * @param usPayloadLength   Length of payload in bytes.
 *
 * @return 0 if successful, otherwise error code.
 */
uint8_t MessageProtocolParser_SendResponse(const uint8_t* ptubPayload, uint16_t usPayloadLength);

#endif // MESSAGE_PROTOCOL_PARSER_H_
