/**
 * @file    ProcessCommand.h
 * @brief   Provides command routing and processing logic for EMP request numbers.
 *
 * This module handles decoding of parsed EMP request numbers and dispatches them to
 * corresponding processing functions. It also provides response payloads for the requests.
 *
 * (C) Copyright Centum T&S Group 2025. All rights reserved.
 * This computer program may not be used, copied, distributed, translated, transmitted or assigned
 * without the prior written authorization of Centum T&S Group.
 */

#ifndef MESSAGEHANDLER_PROCESSCOMMAND_H_
#define MESSAGEHANDLER_PROCESSCOMMAND_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/**
 * @brief Initializes internal state required for command processing.
 *
 */
void ProcessCommand_HandleRequest(void);


#endif /* MESSAGEHANDLER_PROCESSCOMMAND_H_ */
