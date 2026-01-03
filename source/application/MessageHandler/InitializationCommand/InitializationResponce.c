/**
 * @file    InitializationResponce.c
 * @brief   Provides helper functions to generate INIT response fields.
 *
 * (C) Copyright Centum T&S Group 2025. All rights reserved.
 * This computer program may not be used, copied, distributed, translated, transmitted or assigned
 * without the prior written authorization of Centum T&S Group.
 */

#include "InitializationResponce.h"
#include <string.h>
#include "common/CommonDefs.h"

/* ======================== Private Struct ======================== */
typedef struct __attribute__((__packed__)) {
    uint8_t initOrigin;
    uint8_t autoTestResult;
    uint8_t majorFwVersion;
    uint8_t minorFwVersion;
    uint8_t fwVersionShort;
    uint8_t unused;
    uint8_t fontsVersion;
} InitResponsePayload;

/* ======================== Static State ======================== */
static InitResponsePayload s_initResp;

/* ======================== Public API ======================== */

/**
 * @brief Encode the INIT response payload into buffer.
 *
 * @param[out] ppResp Pointer to response payload pointer.
 * @param[out] pusLen Pointer to payload length.
 *
 * @return SUCCESS or FAILURE
 */
uint8_t InitializationResponce_Encode(const uint8_t** ppResp, uint16_t* pusLen)
{
    if ((ppResp == NULL) || (pusLen == NULL)) {
        return FAILURE;
    }
    s_initResp.initOrigin     = 1U;     /*--- TODO Startup origin flag ----*/
    s_initResp.autoTestResult = 1U;		/*--- TODO Auto test result (TestClass) ----*/
    s_initResp.majorFwVersion = 1U;		/*--- TODO download file command ----*/
    s_initResp.minorFwVersion = 0U;		/*--- TODO download file command ----*/
    s_initResp.fwVersionShort = 0x10;	/*--- TODO download file command ----*/
    s_initResp.unused = 0U;				/* unused */
    s_initResp.fontsVersion   = 255U;	/*--- TODO Fonts configuration version----*/

    *ppResp = (const uint8_t*)&s_initResp;
    *pusLen = sizeof(s_initResp);   /* 7 bytes */

    return SUCCESS;
}

/**
 * @brief Reset the INIT response payload to defaults.
 */
void InitializationResponce_Reset(void)
{
    memset(&s_initResp, 0, sizeof(s_initResp));

    s_initResp.initOrigin     = 1U;
    s_initResp.autoTestResult = 1U;
    s_initResp.majorFwVersion = 1U;
    s_initResp.minorFwVersion = 0U;
    s_initResp.fwVersionShort = 0x10;
    s_initResp.fontsVersion   = 255U;
}
