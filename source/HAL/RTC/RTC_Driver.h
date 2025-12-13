/**
 * @file    RTC_Driver.h
 * @brief   Provides helper functions to generate RTC time.
 *
 * (C) Copyright Centum T&S Group 2025. All rights reserved.
 * This computer program may not be used, copied, distributed, translated, transmitted or assigned
 * without the prior written authorization of Centum T&S Group.
 */


#ifndef HAL_RTC_RTC_DRIVER_H_
#define HAL_RTC_RTC_DRIVER_H_

#include "fsl_snvs_lp.h"
#include <stdint.h>
#include "common/CommonDefs.h"

/**
 * @brief Initialize the RTC (SNVS_LP).
 *
 * Configures the SNVS_LP SRTC module with default settings and starts the timer.
 * If the RTC is already running, calling this function is still safe.
 *
 * @note This function must be called before using RTC_SetTime() or RTC_GetTime().
 */
void RTC_Init(void);


/**
 * @brief Set the RTC date and time.
 *
 * Programs the SNVS_LP RTC with the specified date and time.
 *
 * @param[in] datetime Pointer to a structure containing the desired date and time.
 *                     Must not be NULL.
 *
 * @return
 * - kStatus_Success: Time was successfully set.
 * - kStatus_InvalidArgument: @p datetime is NULL.
 * - Other error codes returned by SNVS_LP_SRTC_SetDatetime().
 */
status_t RTC_SetTime(const date_time_t *datetime);

/**
 * @brief Get the current RTC date and time.
 *
 * Reads the current date and time from the SNVS_LP RTC.
 *
 * @param[out] datetime Pointer to a structure that will be filled with the current date and time.
 *                      Must not be NULL.
 *
 * @return
 * - kStatus_Success: Time was successfully retrieved.
 * - kStatus_InvalidArgument: @p datetime is NULL.
 */
status_t RTC_GetTime(date_time_t *datetime);

#endif /* HAL_RTC_RTC_DRIVER_H_ */
