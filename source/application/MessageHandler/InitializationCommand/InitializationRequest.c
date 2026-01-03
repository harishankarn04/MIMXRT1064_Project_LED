/**
 * @file    InitializationRequest.c
 * @brief   Structures and APIs for processing INIT command request.
 *
 * (C) Copyright Centum T&S Group 2025. All rights reserved.
 * This computer program may not be used, copied, distributed, translated, transmitted or assigned
 * without the prior written authorization of Centum T&S Group.
 */

#include "InitializationRequest.h"
#include "common/CommonDefs.h"
#include <string.h>

/* ======================== Private Struct ======================== */

/**
 * @brief Structure representing the INIT request payload.
 *
 * This structure is packed to match the exact byte layout of the
 * INIT request command received from the EMP protocol.
 */
typedef struct __attribute__((__packed__)) {
    uint8_t reserved;               // Byte 0
    uint16_t unused1;               // Bytes 1–2
    uint8_t unused2;                // Byte 3
    uint8_t maxWatchdog;            // Byte 4
    uint8_t lowLedIntensity;        // Byte 5
    uint8_t unused3;                // Byte 6
    uint8_t unused4;                // Byte 7
    uint8_t highLedIntensity;       // Byte 8
    uint8_t lowAmbientThreshold;    // Byte 9
    uint8_t unused5;                // Byte 10
    uint8_t highAmbientThreshold;   // Byte 11
} InitRequestPayload;

/* ======================== Static Variables ======================== */

/** @brief Static storage for the last validated INIT request payload. */

static InitRequestPayload s_initReq;

/* ======================== Init Request Implementation ======================== */

/**
 * @brief Parse and validate the INIT request payload.
 *
 * Copies raw request bytes into a structured format, converts endianness where
 * required, and validates all fields according to specification.
 *
 * @param[in]  pubReqData Pointer to raw request payload.
 * @param[in]  usReqLen   Length of the request payload in bytes.
 *
 * @return SUCCESS if the request is valid, FAILURE otherwise.
 */
uint8_t InitializationRequest_Decode(const uint8_t* pubReqData,
                                            uint16_t usReqLen)
{
    uint8_t ubResult = FAILURE;

    if (pubReqData != NULL) {
        if (usReqLen >= sizeof(InitRequestPayload)) {
            InitRequestPayload req;
            memcpy(&req, pubReqData, sizeof(InitRequestPayload));
            req.unused1 = swap16(req.unused1);

            uint8_t ubValid = SUCCESS;

            if ((req.maxWatchdog == 0U) || (req.maxWatchdog > 255U)) {
                ubValid = FAILURE;
            }
            if ((req.lowLedIntensity < 1U) || (req.lowLedIntensity > 100U)) {
                ubValid = FAILURE;
            }
            if (req.highLedIntensity > 255U) {
                ubValid = FAILURE;
            }
            if ((req.lowAmbientThreshold < 1U) || (req.lowAmbientThreshold > 100U)) {
                ubValid = FAILURE;
            }
            if ((req.highAmbientThreshold < 1U) || (req.highAmbientThreshold > 100U)) {
                ubValid = FAILURE;
            }
            if (req.lowAmbientThreshold > req.highAmbientThreshold) {
                ubValid = FAILURE;
            }

            if (ubValid == SUCCESS) {
                memcpy(&s_initReq, &req, sizeof(InitRequestPayload));
                ubResult = SUCCESS;
            }
        }
    }
    return ubResult;
}


/**
 * @brief Reset the stored INIT request payload to default values.
 */
void InitializationRequest_Reset(void)
{
    memset(&s_initReq, 0, sizeof(s_initReq));
}

/**
 * @brief Get the maximum watchdog count value.
 *
 * @param[out] pWatchdogCount Pointer to store watchdog count.
 * @return SUCCESS if value available, FAILURE otherwise.
 */
uint8_t InitializationRequest_GetMaxWatchdog(uint8_t* pWatchdogCount)
{
    uint8_t ubResult = FAILURE;
    if (pWatchdogCount != NULL) {
        *pWatchdogCount = s_initReq.maxWatchdog;
        ubResult = SUCCESS;
    }
    return ubResult;
}

/**
 * @brief Get the LED intensity thresholds.
 *
 * @param[out] pLow  Pointer to store low LED intensity.
 * @param[out] pHigh Pointer to store high LED intensity.
 * @return SUCCESS if values available, FAILURE otherwise.
 */
uint8_t InitializationRequest_GetLedIntensity(uint8_t* pLow, uint8_t* pHigh)
{
    uint8_t ubResult = FAILURE;
    if ((pLow != NULL) && (pHigh != NULL)) {
        *pLow  = s_initReq.lowLedIntensity;
        *pHigh = s_initReq.highLedIntensity;
        ubResult = SUCCESS;
    }
    return ubResult;
}


/**
 * @brief Get the ambient light thresholds.
 *
 * @param[out] pLow  Pointer to store low ambient threshold.
 * @param[out] pHigh Pointer to store high ambient threshold.
 * @return SUCCESS if values available, FAILURE otherwise.
 */
uint8_t InitializationRequest_GetAmbientThreshold(uint8_t* pLow, uint8_t* pHigh)
{
    uint8_t ubResult = FAILURE;
    if ((pLow != NULL) && (pHigh != NULL)) {
        *pLow  = s_initReq.lowAmbientThreshold;
        *pHigh = s_initReq.highAmbientThreshold;
        ubResult = SUCCESS;
    }
    return ubResult;
}
