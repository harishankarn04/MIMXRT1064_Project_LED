/**
 * @file    LogManager.h
 * @brief   Logging framework for EMP stack. Provides configurable log levels,
 *          timestamped log printing, and formatted output macros.
 *
 * (C) Copyright Centum T&S Group 2025. All rights reserved.
 * This computer program may not be used, copied, distributed, translated,
 * transmitted or assigned without the prior written authorization of
 * Centum T&S Group.
 */

#ifndef LOG_MANAGER_H
#define LOG_MANAGER_H

#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include "fsl_debug_console.h"

/*******************************************************************************
 * Enumerations
 ******************************************************************************/

/**
 * @name Syslog Severity Levels (RFC 5424 style)
 *
 */
#define LOG_LEVEL_EMERG     0   /* System is unusable */
#define LOG_LEVEL_ALERT     1   /* Action must be taken immediately */
#define LOG_LEVEL_CRIT      2   /* Critical conditions */
#define LOG_LEVEL_ERROR     3   /* Error conditions */
#define LOG_LEVEL_WARNING   4   /* Warning conditions */
#define LOG_LEVEL_NOTICE    5   /* Normal but significant condition */
#define LOG_LEVEL_INFO      6   /* Informational messages */
#define LOG_LEVEL_DEBUG     7   /* Debug-level messages */

/*******************************************************************************
 * API Functions
 ******************************************************************************/

/**
 * @brief Initializes the Log Manager.
 *
 * Sets up internal state and default logging level.
 * Must be called once before using any other LogManager functions.
 */
void LogManager_Init(void);

/**
 * @brief Sets the minimum log threshold level.
 *
 * Only messages at or above this severity level will be logged.
 *
 * @param[in] level Minimum severity level (see @ref LOG_LEVEL_DEBUG, etc.).
 */
void LogManager_SetThreshold(uint8_t level);

/**
 * @brief Logs a formatted message with severity level, file, and line info.
 *
 * This function is the core logging API. It is typically invoked
 * via simplified macros such as @ref COSLOG_INFO or @ref COSLOG_ERROR.
 *
 * @param[in] eLevel   Log severity level.
 * @param[in] pfile    Source file name (automatically provided by macro).
 * @param[in] line     Source line number (automatically provided by macro).
 * @param[in] pFormat  printf-style format string.
 * @param[in] ...      Variable arguments for the format string.
 */
void LogManager_Log(uint8_t eLevel,
        			const char* pfile,
					int line,
                    const char* pFormat,
                    ...);

/*******************************************************************************
 * Macros for Simplified Logging
 ******************************************************************************/

/**
 * @name Simplified Logging Macros
 *
 * These macros wrap @ref LogManager_Log and automatically
 * include file and line number information.
 *
 * Example usage:
 * @code
 * COSLOG_ERROR("Failed to open port %d", portNumber);
 * COSLOG_INFO("System initialized successfully");
 */
#define COSLOG_EMERG(fmt, ...)   LogManager_Log(LOG_LEVEL_EMERG,  __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define COSLOG_ALERT(fmt, ...)   LogManager_Log(LOG_LEVEL_ALERT,  __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define COSLOG_CRIT(fmt, ...)    LogManager_Log(LOG_LEVEL_CRIT,   __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define COSLOG_ERROR(fmt, ...)   LogManager_Log(LOG_LEVEL_ERROR,  __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define COSLOG_WARN(fmt, ...)    LogManager_Log(LOG_LEVEL_WARNING,__FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define COSLOG_NOTICE(fmt, ...)  LogManager_Log(LOG_LEVEL_NOTICE, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define COSLOG_INFO(fmt, ...)    LogManager_Log(LOG_LEVEL_INFO,   __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define COSLOG_DEBUG(fmt, ...)   LogManager_Log(LOG_LEVEL_DEBUG,  __FILE__, __LINE__, fmt, ##__VA_ARGS__)

#endif /* LOG_MANAGER_H */

