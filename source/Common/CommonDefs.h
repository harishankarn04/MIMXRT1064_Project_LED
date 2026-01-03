/**
 * @file    CommonDefs.h
 * @brief   Common Function will be kept here to access .
 *
 * (C) Copyright Centum T&S Group 2025. All rights reserved.
 * This computer program may not be used, copied, distributed, translated, transmitted or assigned
 * without the prior written authorization of Centum T&S Group.
 */

#ifndef COMMON_H_
#define COMMON_H_

#include <stdint.h>
#include "Middleware/LogManager/LogManager.h"
#define SUCCESS (1U)
#define FAILURE (0U)


typedef enum
{
	TIMER_SEC = 1,
	TIMER_MILLI_SEC,
	TIMER_MICRO_SEC,

}eTimeUnit;

/**
 * @brief Swap 16-bit value endianness
 */
static inline uint16_t swap16(uint16_t value)

{
    return (uint16_t)((value >> 8) | (value << 8));
}
/**
 * @brief Swap 24-bit value endianness (stored in 32-bit container).
 * Only lowest 24 bits are swapped.
 */
inline uint32_t swap24(uint32_t value)
{
    value &= 0x00FFFFFFU; /* mask to 24 bits */
    return ((value & 0x0000FFU) << 16) |
           ((value & 0x00FF00U)) |
           ((value & 0xFF0000U) >> 16);
}

/**
 * @brief Swap 32-bit value endianness
 */
inline uint32_t swap32(uint32_t value)
{
    return ((value >> 24) & 0x000000FFU) |
           ((value >> 8)  & 0x0000FF00U) |
           ((value << 8)  & 0x00FF0000U) |
           ((value << 24) & 0xFF000000U);
}
/*******************************************************************************
 * Structures
 ******************************************************************************/

/**
 * @brief Timestamp structure for logs.
 *
 * Provides structured representation of log time,
 * including date and millisecond resolution.
 */
typedef struct
{
    uint16_t usYear;
    uint8_t  ubMonth;
    uint8_t  ubDay;
    uint8_t  ubHour;
    uint8_t  ubMinute;
    uint8_t  ubSecond;
    uint8_t  usMilliSec;
} date_time_t;
#endif /* COMMON_H_ */
