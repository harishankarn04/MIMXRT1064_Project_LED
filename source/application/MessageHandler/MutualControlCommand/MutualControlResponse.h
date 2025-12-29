/**
 * @file    MutualControlResponse.h
 * @brief   Provides helper functions to generate Mutual control Response fields.
 *
 * (C) Copyright Centum T&S Group 2025. All rights reserved.
 * This computer program may not be used, copied, distributed, translated, transmitted or assigned
 * without the prior written authorization of Centum T&S Group.
 */

#ifndef MUTUALCONTROLRESPONSE_H_
#define MUTUALCONTROLRESPONSE_H_

#include <stdint.h>
#include "common/CommonDefs.h"

/**
 * @brief Encode Mutual Control Response.
 *
 * @param[out] ppResp  Pointer to response buffer.
 * @param[out] pusLen  Response length.
 * @param[in]  ubStatus Equipment status code.
 *
 * @return SUCCESS if encoded, FAILURE otherwise.
 */
uint8_t MutualControlResponse_Encode(const uint8_t **ppResp,
                                     uint16_t *pusLen,
                                     uint8_t ubStatus);

/**
 * @brief Reset response payload to default values.
 */
void MutualControlResponse_Reset(void);

#endif /* MUTUALCONTROLRESPONSE_H_ */
