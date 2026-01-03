/**
 * @file    MutualControlResponse.c
 * @brief   Provides helper functions to generate Mutual control Response fields.
 *
 * (C) Copyright Centum T&S Group 2025. All rights reserved.
 * This computer program may not be used, copied, distributed, translated, transmitted or assigned
 * without the prior written authorization of Centum T&S Group.
 */

#include "MutualControlResponse.h"
#include <string.h>

/* ======================== Private Struct ======================== */

/**
 * @brief Response payload for Mutual Control.
 */
typedef struct __attribute__((__packed__)) {
    uint8_t ubEquipmentStatus; /**< 0=no fault, others=fault codes */
} MutualControlResponsePayload;

/* ======================== Static Variables ======================== */

/** @brief Latest response payload. */
static MutualControlResponsePayload s_stResp;

/* ======================== Public API ======================== */

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
                                     uint8_t ubStatus)
{
    if ((ppResp == NULL) || (pusLen == NULL)) {
        return FAILURE;
    }

    s_stResp.ubEquipmentStatus = 0; /*--- TODO get from Error Log ----*/

    *ppResp = (const uint8_t*)&s_stResp;
    *pusLen = sizeof(s_stResp);

    return SUCCESS;
}

/**
 * @brief Reset response payload to default values.
 */
void MutualControlResponse_Reset(void)
{
    memset(&s_stResp, 0, sizeof(s_stResp));
}
