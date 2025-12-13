/**
 * @file    MutualControlRequest.c
 * @brief   Provides helper functions to generate Mutual control Request fields.
 *
 * (C) Copyright Centum T&S Group 2025. All rights reserved.
 * This computer program may not be used, copied, distributed, translated, transmitted or assigned
 * without the prior written authorization of Centum T&S Group.
 */

#include "MutualControlRequest.h"
#include "common/CommonDefs.h"
#include <string.h>

/* ======================== Private Struct ======================== */

/**
 * @brief Structure representing the Mutual Control Request payload.
 *
 * Matches the exact byte layout of the EMP Mutual Control request.
 */
typedef struct __attribute__((__packed__)) {
    uint8_t ubDayOfWeek;      /**< 0=Sunday … 6=Saturday */
    uint8_t ubYear;           /**< Last 2 digits of year (0–99, ref=2000) */
    uint8_t ubMonth;          /**< 1–12 */
    uint8_t ubDay;            /**< 1–31 */
    uint8_t ubHour;           /**< 0–23 */
    uint8_t ubMinutes;        /**< 0–59 */
    uint8_t ubSeconds;        /**< 0–59 */
    uint8_t ubHundredSeconds; /**< 0–99 */
} MutualControlRequestPayload;

/* ======================== Static Variables ======================== */

/** @brief Stores last decoded valid request. */
static MutualControlRequestPayload s_stLastRequest;

/** @brief Flag if request is valid (1=valid, 0=invalid). */
static uint8_t s_ubIsValid;

/* ======================== Public API ======================== */
/**
 * @brief Decode Mutual Control Request payload.
 *
 * @param[in] pubReq Raw buffer.
 * @param[in] usLen  Length of buffer.
 * @return SUCCESS if valid, else FAILURE.
 */
uint8_t MutualControlRequest_Decode(const uint8_t *pubReq,
                                    uint16_t usLen)
{
    uint8_t ubStatus = FAILURE;

    if ((pubReq != NULL) && (usLen >= sizeof(MutualControlRequestPayload))) {
        MutualControlRequestPayload req;
        memcpy(&req, pubReq, sizeof(MutualControlRequestPayload));

        if ((req.ubDayOfWeek <= 6U) &&
            (req.ubYear <= 99U) &&
            (req.ubMonth >= 1U && req.ubMonth <= 12U) &&
            (req.ubDay >= 1U && req.ubDay <= 31U) &&
            (req.ubHour <= 23U) &&
            (req.ubMinutes <= 59U) &&
            (req.ubSeconds <= 59U) &&
            (req.ubHundredSeconds <= 99U))
        {
            memcpy(&s_stLastRequest, &req, sizeof(req));
            s_ubIsValid = 1U;
            ubStatus = SUCCESS;
        }
    }
    return ubStatus;
}
/**
 * @brief Reset stored request state.
 */
void MutualControlRequest_Reset(void)
{
    memset(&s_stLastRequest, 0, sizeof(s_stLastRequest));
    s_ubIsValid = 0U;
}

/**
 * @brief Retrieve the last decoded request fields.
 *
 * @param[out] pDayOfWeek      0=Sunday … 6=Saturday
 * @param[out] pYear           Last 2 digits of year (0–99, ref=2000)
 * @param[out] pMonth          1–12
 * @param[out] pDay            1–31
 * @param[out] pHour           0–23
 * @param[out] pMinutes        0–59
 * @param[out] pSeconds        0–59
 * @param[out] pHundredSeconds 0–99
 *
 * @return SUCCESS if valid request exists, FAILURE otherwise.
 */
uint8_t MutualControlRequest_GetValues(uint8_t *pDayOfWeek,
                                       uint8_t *pYear,
                                       uint8_t *pMonth,
                                       uint8_t *pDay,
                                       uint8_t *pHour,
                                       uint8_t *pMinutes,
                                       uint8_t *pSeconds,
                                       uint8_t *pHundredSeconds)
{
    if (s_ubIsValid == 0U) {
        return FAILURE;
    }

    if ((pDayOfWeek == NULL) || (pYear == NULL) || (pMonth == NULL) ||
        (pDay == NULL) || (pHour == NULL) || (pMinutes == NULL) ||
        (pSeconds == NULL) || (pHundredSeconds == NULL))
    {
        return FAILURE;
    }

    *pDayOfWeek      = s_stLastRequest.ubDayOfWeek;
    *pYear           = s_stLastRequest.ubYear;
    *pMonth          = s_stLastRequest.ubMonth;
    *pDay            = s_stLastRequest.ubDay;
    *pHour           = s_stLastRequest.ubHour;
    *pMinutes        = s_stLastRequest.ubMinutes;
    *pSeconds        = s_stLastRequest.ubSeconds;
    *pHundredSeconds = s_stLastRequest.ubHundredSeconds;

    return SUCCESS;
}
