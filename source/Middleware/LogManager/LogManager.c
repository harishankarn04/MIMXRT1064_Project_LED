/**
 * @file    LogManager.c
 * @brief   Implementation of the logging framework for EMP stack.
 *
 * (C) Copyright Centum T&S Group 2025. All rights reserved.
 * This computer program may not be used, copied, distributed, translated,
 * transmitted or assigned without the prior written authorization of
 * Centum T&S Group.
 */

#include "LogManager.h"
#include "common/CommonDefs.h"
#include <stdio.h>
#include <stdarg.h>

/*******************************************************************************
 * Static Variables
 ******************************************************************************/

/**
 * @brief Active log threshold level.
 *
 * Any log message with severity greater than this level will be suppressed.
 */
static uint8_t s_ubLogThreshold;

/**
 * @brief Human-readable string representations of log levels.
 */
static const char* s_apcLevelStr[] =
{
	    "EMERG",   /* 0 */
	    "ALERT",   /* 1 */
	    "CRIT",    /* 2 */
	    "ERROR",   /* 3 */
	    "WARN",    /* 4 */
	    "NOTICE",  /* 5 */
	    "INFO",    /* 6 */
	    "DEBUG"    /* 7 */
};

/*******************************************************************************
 * Public Functions
 ******************************************************************************/

/**
 * @brief Initializes the Log Manager module.
 *
 * Sets the default log threshold to @ref LOG_LEVEL_DEBUG (all logs enabled).
 */
void LogManager_Init(void)
{
    s_ubLogThreshold = LOG_LEVEL_DEBUG;  /* Default: enable all logs */
}

/**
 * @brief Updates the log threshold level.
 *
 * Any message with a level greater than the threshold will not be logged.
 *
 * @param[in] level Minimum severity level to log. Valid range:
 *                  @ref LOG_LEVEL_EMERG to @ref LOG_LEVEL_DEBUG.
 */
void LogManager_SetThreshold(uint8_t level)
{
    if (level <= LOG_LEVEL_DEBUG)
    {
        s_ubLogThreshold = level;
    }
}

/**
 * @brief Logs a formatted message with syslog-style metadata.
 *
 * Includes severity, timestamp, file name, and line number.
 * Called indirectly via macros such as @ref COSLOG_ERROR, @ref COSLOG_INFO.
 *
 * @param[in] eLevel   Log severity level.
 * @param[in] pFile    Source file name.
 * @param[in] line     Source line number.
 * @param[in] pFormat  printf-style format string.
 * @param[in] ...      Additional arguments for the format string.
 */
void LogManager_Log(uint8_t eLevel,
                    const char* pFile,
					int line,
                    const char* pFormat,
                    ...)
{
    if (eLevel > s_ubLogThreshold)
    {
        return; /* Skip if above threshold */
    }

    /* Example timestamp – replace with RTC/system time */

    /*--- TODO ----*/
    date_time_t now = {2025, 8, 9, 12, 30, 45, 123};

    /* Print syslog-style header */
    PRINTF("%s %04u-%u-%uT%u:%u:%u.%u [%s:%d]:: ",
           s_apcLevelStr[eLevel],
           (uint16_t)now.usYear,
           (uint8_t) now.ubMonth,
           (uint8_t) now.ubDay,
           (uint8_t) now.ubHour,
           (uint8_t) now.ubMinute,
           (uint8_t) now.ubSecond,
           (uint16_t)now.usMilliSec,
           pFile,
		   line);


    /* Print message */
    va_list args;
    va_start(args, pFormat);
    DbgConsole_Vprintf(pFormat, args);   /* use DbgConsole_Vprintf so var args are expanded correctly */
    va_end(args);

    PRINTF("\r\n");
}
