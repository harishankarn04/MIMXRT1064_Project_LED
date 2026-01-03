/**
 * @file    SessionManager.h
 * @brief   Session state management for EMP (Ethernet Messaging Protocol).
 *
 * (C) Copyright Centum T&S Group 2025. All rights reserved.
 * This computer program may not be used, copied, distributed, translated, transmitted or assigned
 * without the prior written authorization of Centum T&S Group.
 *
 **/

#ifndef SESSION_MANAGER_H
#define SESSION_MANAGER_H

#include <stdint.h>
#include "../MessageLayerParser/MessageProtocolParser.h"

/**
 * @brief Initialize the EMP session manager state.
 *
 * This function resets all internal session-related variables to their
 * default state.
 *
 * @return None.
 */
void SessionManager_Init(void);

/**
 * @brief Performs session handling logic (Create, Validate, Delete, Replace).
 *
 * @param pstOutMsg Pointer to the parsed EMP message.
 * @return SUCCESS if session handling succeeded, FAILURE otherwise.
 */
uint8_t SessionManager_SessionHandling(const parsed_emp_message_t *pstOutMsg);

/**
 * @brief Validates the transaction ID against previous state.
 *
 * @param usTransactionId Transaction ID to validate.
 * @param ubIsResponse    Set to 1 if this is a response, 0 for a request.
 *
 * @return SUCCESS if transaction ID is valid, FAILURE otherwise.
 */
uint8_t SessionManager_ValidateTransactionId(uint16_t usTransactionId,
                                             uint8_t ubIsResponse);

/**
 * @brief Configure and refresh session timeout from parsed EMP message.
 *
 * This helper applies the timeout value from the parsed message and
 * resets the session timer on each valid packet.
 *
 * @param pstOutMsg Pointer to parsed EMP message structure.
 */
void SessionManager_UpdateTimeoutFromMessage(const parsed_emp_message_t* pstOutMsg);

/**
 * @brief Checks whether the current session has timed out.
 *
 * If the timeout period has elapsed since the last reset,
 * the session will be automatically closed.
 */
void SessionManager_CheckTimeout(void);

/**
 * @brief Validate an EMP message against the current session state.
 *
 * This function checks whether the given parsed EMP message is valid in the
 * context of the active session. Validation may include verifying transaction
 * IDs, response/request consistency, and session-related constraints.
 *
 * @param pstOutMsg       Pointer to the parsed EMP message structure to validate.
 *                        Must not be NULL.
 * @param usRequestNumber The request number extracted from the messaging layer.
 *
 * @return Status code indicating the result of validation:
 *         - SUCCESS if the message is valid,
 *         - ERROR_xxx (implementation-defined) if validation fails.
 */
uint8_t SessionManager_ValidateMessage(const parsed_emp_message_t* pstOutMsg,
                                       uint16_t usRequestNumber);
#endif /* SESSION_MANAGER_H */
