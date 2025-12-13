/**
 * @file    RTC_Driver.c
 * @brief   Provides helper functions to generate RTC time.
 *
 * (C) Copyright Centum T&S Group 2025. All rights reserved.
 * This computer program may not be used, copied, distributed, translated, transmitted or assigned
 * without the prior written authorization of Centum T&S Group.
 */


#include "RTC_Driver.h"
#include "fsl_snvs_lp.h"

/** @brief RTC instance used for SNVS_LP operations. */
#define RTC_INSTANCE SNVS

/**
 * @brief Initialize the RTC (SNVS_LP).
 *
 * Configures the SNVS_LP SRTC module with default settings and starts the timer.
 * If the RTC is already running, calling this function is still safe.
 *
 * @note This function must be called before using other RTC operations.
 */
void RTC_Init(void)
{

    snvs_lp_srtc_config_t snvsConfig;

    /* Load default configuration */
    SNVS_LP_SRTC_GetDefaultConfig(&snvsConfig);

    /* Initialize RTC with configuration */
    SNVS_LP_SRTC_Init(RTC_INSTANCE, &snvsConfig);

    /* Start RTC timer (safe to call even if already running) */
    SNVS_LP_SRTC_StartTimer(RTC_INSTANCE);
}

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
status_t RTC_SetTime(const date_time_t *datetime)
{
    status_t eStatus = kStatus_InvalidArgument;

    if (datetime != NULL) {
        snvs_lp_srtc_datetime_t rtcTime;

        rtcTime.year   = datetime->usYear;
        rtcTime.month  = datetime->ubMonth;
        rtcTime.day    = datetime->ubDay;
        rtcTime.hour   = datetime->ubHour;
        rtcTime.minute = datetime->ubMinute;
        rtcTime.second = datetime->ubSecond;

        eStatus = SNVS_LP_SRTC_SetDatetime(RTC_INSTANCE, &rtcTime);
    }
    else {
        /* else intentionally left blank: eStatus already set to kStatus_InvalidArgument */
    }

    return eStatus;
}

/**
 * @brief Get the current RTC date and time.
 *
 * Reads the current date and time from the SNVS_LP RTC.
 *
 * @param[out] datetime Pointer to a structure that will be filled with
 *                      the current date and time. Must not be NULL.
 *
 * @return
 * - kStatus_Success: Time was successfully retrieved.
 * - kStatus_InvalidArgument: @p datetime is NULL.
 */
status_t RTC_GetTime(date_time_t *datetime)
{
    status_t eStatus = kStatus_InvalidArgument;

    if (datetime != NULL) {
        snvs_lp_srtc_datetime_t rtcTime;

        SNVS_LP_SRTC_GetDatetime(RTC_INSTANCE, &rtcTime);

        datetime->usYear     = rtcTime.year;
        datetime->ubMonth    = rtcTime.month;
        datetime->ubDay      = rtcTime.day;
        datetime->ubHour     = rtcTime.hour;
        datetime->ubMinute   = rtcTime.minute;
        datetime->ubSecond   = rtcTime.second;
        datetime->usMilliSec = 0U;

        eStatus = kStatus_Success;
    }
    else {
        /* else intentionally left blank: eStatus already set to kStatus_InvalidArgument */
    }

    return eStatus;
}
