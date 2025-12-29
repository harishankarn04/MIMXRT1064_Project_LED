/**
* @file timer.h
* @brief Software timer interface using PIT as a free-running timebase
* Provides APIs to initialize the PIT, start timers with microsecond
* resolution, and check for timer expiry in embedded applications.
*
* (C) Copyright Centum T&S Group 2025. All rights reserved.
* This computer program may not be used, copied, distributed, translated, transmitted or assigned
* without the prior written authorization of Centum T&S Group.
*
**/

#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>
#include <stdbool.h>
#include "../../Common/CommonDefs.h"

/**
 * @brief Initialize the hardware timer module.
 *
 * Configures the underlying hardware timer (e.g., PIT) to run in free-running
 * mode. Must be called before any other timer operations.
 */
uint8_t Timer_Create(void **ppT, uint32_t ulDuration, eTimeUnit eUnit);

/**
 * @brief Delete a software timer.
 *
 * Frees the memory associated with a software timer instance and
 * invalidates the pointer.
 *
 * @param[in] pT
 *        Pointer to the software timer object to be deleted. If NULL,
 *        no action is taken.
 */
void Timer_Delete(void *pT);

/**
 * @brief Start a software timer.
 *
 * @param[in,out] t Pointer to software timer object.
 * @param[in] ulDurationUs Duration in microseconds until expiration.
 *
 * The timer starts from the current system time and is marked active.
 */
uint8_t Timer_Start(void *pT);
/**
 * @brief Check if the software timer has expired.
 *
 * @param[in,out] t Pointer to software timer object.
 *
 * @return uint8_t
 *         - 1 (SUCCESS) if the timer has expired,
 *         - 0 (FAILURE) if the timer is still active or not started.
 *
 * If expired, the timer is marked inactive automatically.
 */
uint8_t Timer_IsExpired(void *t);

#endif
