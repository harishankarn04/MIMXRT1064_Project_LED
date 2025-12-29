/**
 * @file    InitializationResponce.h
 * @brief   Provides helper functions to generate INIT response fields.
 *
 * (C) Copyright Centum T&S Group 2025. All rights reserved.
 * This computer program may not be used, copied, distributed, translated, transmitted or assigned
 * without the prior written authorization of Centum T&S Group.
 */

#ifndef INITIALIZATIONCOMMAND_INITIALIZATIONCOMMANDRESPONCE_H_
#define INITIALIZATIONCOMMAND_INITIALIZATIONCOMMANDRESPONCE_H_

#include <stdint.h>

/**
 * @brief Encode the INIT response payload into buffer.
 *
 * @param[out] ppResp Pointer to response payload pointer.
 * @param[out] pusLen Pointer to payload length.
 *
 * @return SUCCESS or FAILURE
 */
uint8_t InitializationResponce_Encode(const uint8_t** ppResp, uint16_t* pusLen);

/**
 * @brief Reset the INIT response payload to defaults.
 */
void InitializationResponce_Reset(void);

#endif /* INITIALIZATIONCOMMAND_INITIALIZATIONCOMMANDRESPONCE_H_ */

