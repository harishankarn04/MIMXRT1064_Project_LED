/**
 * @file    ProcessInitCommand.h
 * @brief   Structures and APIs for processing INIT command request.
 *
 * (C) Copyright Centum T&S Group 2025. All rights reserved.
 * This computer program may not be used, copied, distributed, translated, transmitted or assigned
 * without the prior written authorization of Centum T&S Group.
 */

#ifndef INITIALIZATIONCOMMAND_INITIALIZATIONCOMMANDPROCESS_H_
#define INITIALIZATIONCOMMAND_INITIALIZATIONCOMMANDPROCESS_H_

#include <stdint.h>
#include <stdbool.h>
#include "common/CommonDefs.h"

/**
 * @brief Reset the stored INIT request payload to default values.
 *
 * This function clears all fields of the stored Initialization Request
 * payload structure and sets them to their default values. It should be
 * called before decoding a new INIT request.
 */
void InitializationRequest_Reset(void);

/**
 * @brief Decode the Initialization Request payload.
 *
 * Parses the provided buffer and extracts fields according to the EMP
 * Initialization Request specification. On success, the parsed values
 * are stored internally and can be accessed through accessor functions.
 *
 * @param[in]  pubReqData  Pointer to the raw Initialization Request payload.
 * @param[in]  usReqLen    Length of the request payload in bytes.
 *
 * @return SUCCESS if the payload is valid and decoding completed,
 *         otherwise FAILURE.
 */
uint8_t InitializationRequest_Decode(const uint8_t* pubReqData,
                                            uint16_t usReqLen);
/**
 * @brief Get the maximum watchdog count value.
 *
 * @param[out] pWatchdogCount Pointer to store watchdog count.
 * @return SUCCESS if value available, FAILURE otherwise.
 */
uint8_t InitializationRequest_GetMaxWatchdog(uint8_t* pWatchdogCount);

/**
 * @brief Get the LED intensity thresholds.
 *
 * @param[out] pLow  Pointer to store low LED intensity.
 * @param[out] pHigh Pointer to store high LED intensity.
 * @return SUCCESS if values available, FAILURE otherwise.
 */
uint8_t InitializationRequest_GetLedIntensity(uint8_t* pLow, uint8_t* pHigh);

/**
 * @brief Get the ambient light thresholds.
 *
 * @param[out] pLow  Pointer to store low ambient threshold.
 * @param[out] pHigh Pointer to store high ambient threshold.
 * @return SUCCESS if values available, FAILURE otherwise.
 */
uint8_t InitializationRequest_GetAmbientThreshold(uint8_t* pLow, uint8_t* pHigh);

#endif /* INITIALIZATIONCOMMAND_INITIALIZATIONCOMMANDPROCESS_H_ */

