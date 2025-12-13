/**
 * @file    SessionManager.c
 * @brief   Session state tracking for EMP protocol.
 *
 * This module manages a single session context for EMP communication,
 * including session creation, validation, replacement, and tracking
 * of the first message in the session.
 *
 * (C) Copyright Centum T&S Group 2025. All rights reserved.
 * This computer program may not be used, copied, distributed, translated, transmitted or assigned
 * without the prior written authorization of Centum T&S Group.
 */

#include <stdbool.h>
#include "SessionManager.h"
#include "common/CommonDefs.h"
#include"HAL/TimerModule/timer.h"

/*******************************************************************************
* Definitions
******************************************************************************/

/**
 * @brief Special value indicating an invalid or uninitialized session ID.
 */
#define SESSION_INVALID_ID    (0xFFFFU)

/*******************************************************************************
* Static Variables
******************************************************************************/

static uint16_t s_usCurrentSessionId;
static uint8_t s_ubSessionActive;
static uint8_t s_ubFirstMessage;
static uint16_t s_usLastTransactionId;
static bool s_usFirstTransaction;
static uint32_t s_ulTimeoutPeriod;
static void *spSessionTimer;


/*******************************************************************************
* Public Functions
******************************************************************************/

/**
 * @brief Initializes all static session variables.
 *
 * This function resets the session state by marking the session ID as invalid
 * and clearing both the active session and first message flags.
 */
void SessionManager_Init(void)
{
    s_usCurrentSessionId = SESSION_INVALID_ID;
    s_ubSessionActive = 0U;
    s_ubFirstMessage = 0U;
    s_usLastTransactionId = 0U;
    s_usFirstTransaction = true;
    s_ulTimeoutPeriod  = 0U;
    spSessionTimer  = NULL;
}

/**
 * @brief Creates a new session with the specified session ID.
 *
 * If no session is currently active, this will set the session ID,
 * mark the session as active, and note the first message flag.
 *
 * @param us_sessionId  The session ID to initialize.
 */
void SessionManager_CreateSession(uint16_t us_sessionId)
{
    if (s_ubSessionActive == 0U)
    {
    	s_usCurrentSessionId = us_sessionId;
        s_ubSessionActive = 1U;
        s_ubFirstMessage = 1U;

    }
    else
    {
    	COSLOG_ERROR("Session already active (ID = %u)\r\n",
    			s_usCurrentSessionId);
    }
}

/**
 * @brief Deletes the currently active session.
 *
 * This resets the session ID to an invalid state and clears
 * both the active session and first message flags.
 */
void SessionManager_DeleteSession(void)
	{
		s_usCurrentSessionId = SESSION_INVALID_ID;
		s_ubSessionActive = 0U;
		s_ubFirstMessage = 0U;
		s_ulTimeoutPeriod  = 0U;
	}

/**
 * @brief Checks if a session is currently active.
 *
 * @return 1 if a session is active, 0 otherwise.
 */
uint8_t SessionManager_HasActiveSession(void)
{
    uint8_t ub_result = 0U;

    if (s_ubSessionActive == 1U) {
        ub_result = 1U;
    }
    else
    {
    	COSLOG_INFO("No active session\r\n");
    }
    return ub_result;
}

/**
 * @brief Validates if the given session ID matches the active session.
 *
 * @param us_sessionId  The session ID to validate.
 *
 * @return 1 if the session ID matches the active session, 0 otherwise.
 */
uint8_t SessionManager_IsValidSession(uint16_t us_sessionId)
{
    uint8_t ub_result = 0U;

    if ((s_ubSessionActive == 1U) &&
        (s_usCurrentSessionId == us_sessionId)) {
        ub_result = 1U;
    }
    else
    {
    	COSLOG_ERROR("Invalid session. Expected = %u, Received = %u, Active = %u\r\n",
			   s_usCurrentSessionId, us_sessionId, s_ubSessionActive);
    }

    return ub_result;
}

/**
 * @brief Retrieves the currently active session ID.
 *
 * @return The current session ID, or SESSION_INVALID_ID if none is active.
 */
uint16_t SessionManager_GetCurrentSession(void)
	{
		return s_usCurrentSessionId;
	}

/**
 * @brief Replaces the current session with a new session ID.
 *
 * This function updates the session ID and marks it as a new session.
 *
 * @param us_newSessionId  The new session ID to set.
 */
void SessionManager_ReplaceSession(uint16_t us_newSessionId)
	{
		s_usCurrentSessionId = us_newSessionId;
		s_ubSessionActive = 1U;
		s_ubFirstMessage = 1U;
	}

/**
 * @brief Checks if the first message of the session has not yet been handled.
 *
 * @return 1 if this is the first message in the session, 0 otherwise.
 */
uint8_t SessionManager_IsFirstMessageInSession(void)
	{
		uint8_t ub_result = 0U;

		if (s_ubFirstMessage == 1U) {
			ub_result = 1U;
		}
		else
		{
			COSLOG_INFO("First message already handled\r\n");
		}

		return ub_result;
	}

/**
 * @brief Marks that the first message of the session has been processed.
 *
 * This function clears the "first message" flag so subsequent
 * session messages are not treated as the first one.
 */
void SessionManager_MarkFirstMessageHandled(void)
	{
		s_ubFirstMessage = 0U;
	}

/**
 * @brief Handles EMP session logic for Create, Validate, Delete, or Replace.
 *
 * Depending on the message type in the parsed EMP message, this function will:
 * - Delete the active session (MsgType = 1)
 * - Replace the active session with a new one (MsgType = 2)
 * - Create a new session if none exists
 * - Validate the session ID if a session already exists
 *
 * @param pstOutMsg Pointer to parsed EMP message structure containing SessionID and MsgType.
 *
 * @return SUCCESS if session handling was performed successfully,
 *         FAILURE if validation fails or invalid parameters are detected.
 */
void SessionManager_ResetTransactionState(void)
{
    s_usLastTransactionId = 0U;
    s_usFirstTransaction = true;
}

uint8_t SessionManager_SessionHandling(const parsed_emp_message_t *pstOutMsg)
{
    uint8_t ubStatus = FAILURE;
    uint16_t ubMsgType = MessageProtocolParser_GetMessageType(pstOutMsg);

    if (pstOutMsg == NULL)
    {
        COSLOG_ERROR("Null pointer received (pstOutMsg = %p)\r\n", (void *)pstOutMsg);
        return FAILURE;
    }

    if (ubMsgType == 1U)
    {
        SessionManager_DeleteSession();
        SessionManager_ResetTransactionState();
        COSLOG_INFO("Session deleted (ID was 0x%04X)\r\n",
                    MessageProtocolParser_GetSessionId(pstOutMsg));
        return SUCCESS;
    }

    if (ubMsgType == 2U)
    {
        COSLOG_INFO("Replace session. Old: 0x%04X, New: 0x%04X\r\n",
                    SessionManager_GetCurrentSession(),
                    MessageProtocolParser_GetSessionId(pstOutMsg));
        SessionManager_ReplaceSession(MessageProtocolParser_GetSessionId(pstOutMsg));
        SessionManager_ResetTransactionState();
        return SUCCESS;
    }

    if (SessionManager_HasActiveSession() == 0U)
    {
        SessionManager_CreateSession(MessageProtocolParser_GetSessionId(pstOutMsg));
        COSLOG_INFO("Session started with Session ID: 0x%04X\r\n",
                    MessageProtocolParser_GetSessionId(pstOutMsg));
    }
    else
    {
        if (SessionManager_IsValidSession(MessageProtocolParser_GetSessionId(pstOutMsg)) == 0U)
        {
            COSLOG_ERROR("Invalid Session ID. Expected 0x%04X, Got 0x%04X\r\n",
                         SessionManager_GetCurrentSession(),
                         MessageProtocolParser_GetSessionId(pstOutMsg));
            return FAILURE;
        }
        else
        {
            COSLOG_INFO("Session ID is valid (0x%04X)\r\n",
                        MessageProtocolParser_GetSessionId(pstOutMsg));
        }
    }

    SessionManager_UpdateTimeoutFromMessage(pstOutMsg);

    ubStatus = SUCCESS;
    return ubStatus;
}

/**
 * @brief Starts or updates the session timeout period.
 *
 * This function configures a timeout in seconds, which is internally
 * converted to microseconds. If the timeout value is 0, timeout is disabled.
 *
 * @param usTimeoutSec Timeout duration in seconds.
 */

void SessionManager_StartTimeout(uint16_t usTimeoutSec)
{
    if (usTimeoutSec == 0U)
    {
        /* Disable timeout */
        s_ulTimeoutPeriod = 0U;
        if (spSessionTimer != NULL)
        {
            Timer_Delete(spSessionTimer);
            spSessionTimer = NULL;
        }
        return;
    }

    /* Convert seconds → microseconds */
    uint32_t ulNewTimeoutUs = (uint32_t)usTimeoutSec * 1000000U;

    /* If value changed, recreate timer */
    if (s_ulTimeoutPeriod != ulNewTimeoutUs)
    {
        s_ulTimeoutPeriod = ulNewTimeoutUs;

        if (spSessionTimer != NULL)
        {
            Timer_Delete(spSessionTimer);
            spSessionTimer = NULL;
        }

        if (Timer_Create(&spSessionTimer, usTimeoutSec, TIMER_SEC) == 0U)
        {
            COSLOG_ERROR("Failed to create session timer\r\n");
            return;
        }
    }

    /* Always restart to refresh */
    if (spSessionTimer != NULL)
    {
        Timer_Start(spSessionTimer);
    }
}


/**
 * @brief Resets the timeout counter to extend the session life.
 *
 * Should be called whenever a valid packet is received in order
 * to prevent session expiry.
 */
void SessionManager_ResetTimeout(void)
{
    if (s_ulTimeoutPeriod > 0U)
    {
    	Timer_Start(spSessionTimer);
    }
}

/**
 * @brief Checks whether the active session has expired due to timeout.
 *
 * If the elapsed time since the last packet exceeds the configured timeout
 * period, the session is deleted and transaction tracking is reset.
 */
void SessionManager_CheckTimeout(void)
{
    if ((s_usCurrentSessionId != SESSION_INVALID_ID) &&
        (s_ulTimeoutPeriod > 0U))
    {
        if (Timer_IsExpired(spSessionTimer))
        {
        	COSLOG_INFO("Session 0x%04X expired \r\n",s_usCurrentSessionId);

            SessionManager_DeleteSession();

            /* Reset transaction handling */
            s_usLastTransactionId = 0U;
            s_usFirstTransaction   = true;
        }
    }
}


/**
 * @brief Validates and tracks transaction IDs for duplicate detection.
 *
 * For request messages:
 * - If this is the first transaction, it is always accepted.
 * - If it is not the first transaction, the ID is compared against the last one.
 *   Duplicate IDs result in failure.
 *
 * For response messages:
 * - Transaction tracking is skipped.
 *
 * @param usTransactionId Transaction ID from the message.
 * @param ubIsResponse    1U if response message, 0U if request message.
 *
 * @return SUCCESS if valid, FAILURE if duplicate or invalid.
 */
uint8_t SessionManager_ValidateTransactionId(uint16_t usTransactionId, uint8_t ubIsResponse)
{
    uint8_t ubStatus = SUCCESS;

    if (ubIsResponse == 0U) /* Request message */
    {
        if (s_usFirstTransaction == 0U)
        {
            if (usTransactionId == s_usLastTransactionId)
            {
            	COSLOG_ERROR("Duplicate Transaction ID detected: 0x%04X\r\n",
                       usTransactionId);
                ubStatus = FAILURE;
            }
            else
            {
            	COSLOG_INFO("Transaction ID is unique\r\n");
            }
        }
        else
        {
        	COSLOG_INFO("First transaction, no duplicate check\r\n");
        }

        s_usFirstTransaction = 0U;
        s_usLastTransactionId = usTransactionId;
    }
    else /* Response message */
    {
    	COSLOG_INFO("Response message, skipping transaction tracking\r\n");
    }

    return ubStatus;
}

/**
 * @brief Configure and refresh session timeout based on EMP message.
 *
 * This function extracts the session timeout value from the parsed EMP message
 * and applies it to the session manager. It also resets the timeout timer to
 * keep the session alive on every valid packet.
 *
 * @param pstOutMsg Pointer to parsed EMP message structure.
 */
void SessionManager_UpdateTimeoutFromMessage(const parsed_emp_message_t* pstOutMsg)
{
    if (pstOutMsg == NULL)
    {
        COSLOG_ERROR("SessionManager_UpdateTimeoutFromMessage: NULL message pointer\r\n");
        return;
    }

    uint16_t usTimeout = MessageProtocolParser_GetSessionTimeout(pstOutMsg);

    /* Setup timeout from parsed session value */
    SessionManager_StartTimeout(usTimeout);

    /* Reset timeout on every valid packet */
    SessionManager_ResetTimeout();
}

/**
 * @brief Validate first-message rules and transaction ID for a parsed EMP message.
 *
 * This function enforces:
 * - The first message of a new session must be Initialization (requestNumber = 0).
 * - Transaction ID validation (duplicate detection).
 *
 * @param pstOutMsg Pointer to parsed EMP message.
 * @param usRequestNumber Request number extracted from the Messaging Layer.
 *
 * @return SUCCESS if valid, FAILURE if rule violated.
 */
uint8_t SessionManager_ValidateMessage(const parsed_emp_message_t* pstOutMsg,
                                       uint16_t usRequestNumber)
{
    uint8_t ubStatus = FAILURE;

    if (pstOutMsg == NULL)
    {
        COSLOG_ERROR("SessionManager_ValidateMessage: NULL pointer\r\n");
        return FAILURE;
    }

    /* Check first-message rules */
    if (SessionManager_IsFirstMessageInSession() != 0U)
    {
        if (usRequestNumber != 0U)
        {
            COSLOG_ERROR("First message must be Initialization (requestNumber 0). Got: %u\r\n",
                         usRequestNumber);
            return FAILURE;
        }
        else
        {
            COSLOG_INFO("Initialization command accepted as first message.\r\n");
            SessionManager_MarkFirstMessageHandled();
        }
    }
    else
    {
        COSLOG_INFO("Not the first message in session.\r\n");
    }

    /* Validate transaction ID */
    if (SessionManager_ValidateTransactionId(MessageProtocolParser_GetTransactionId(pstOutMsg),
            MessageProtocolParser_IsResponse(pstOutMsg)) == SUCCESS)
    {
        ubStatus = SUCCESS;
    }
    else
    {
        COSLOG_ERROR("Invalid or duplicate Transaction ID: 0x%04X\r\n",
        		MessageProtocolParser_GetTransactionId(pstOutMsg));
    }

    return ubStatus;
}
