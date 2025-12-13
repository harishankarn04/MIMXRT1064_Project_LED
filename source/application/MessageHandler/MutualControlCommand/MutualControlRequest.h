/**
 * @file    MutualControlCommandProcess.h
 * @brief   Provides helper functions to generate Mutual control Request fields.
 *
 * (C) Copyright Centum T&S Group 2025. All rights reserved.
 * This computer program may not be used, copied, distributed, translated, transmitted or assigned
 * without the prior written authorization of Centum T&S Group.
 */

#ifndef MUTUALCONTROLREQUEST_H_
#define MUTUALCONTROLREQUEST_H_

#include <stdint.h>
#include "common/CommonDefs.h"

/**
 * @brief Decode Mutual Control Request payload.
 *
 * @param[in] pubReq Raw buffer.
 * @param[in] usLen  Length of buffer.
 * @return SUCCESS if valid, else FAILURE.
 */
uint8_t MutualControlRequest_Decode(const uint8_t *pubReq, uint16_t usLen);

/**
 * @brief Reset stored request state.
 */
void MutualControlRequest_Reset(void);

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
                                       uint8_t *pHundredSeconds);

#endif /* MUTUALCONTROLREQUEST_H_ */
