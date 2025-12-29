/**
 * @file    MessageData.c
 * @brief   EMP Messaging Layer data storage and accessor module.
 *
 * Provides functions to initialize, set, and retrieve Messaging Layer fields
 * extracted from EMP messages. This module acts as an internal data container
 * for parsed EMP message content such as equipment address, channel number,
 * request number, version, origin, and payload.
 *
 * (C) Copyright Centum T&S Group 2025. All rights reserved.
 * This computer program may not be used, copied, distributed, translated,
 * transmitted, or assigned without the prior written authorization of
 * Centum T&S Group.
 */

#include "MessageData.h"
#include <string.h>

/*******************************************************************************
 * Static Variables
 ******************************************************************************/

/**
 * @brief Structure to hold Messaging Layer fields.
 */
typedef struct
{
    uint8_t     ubEquipmentAddr;    /**< 6-bit Equipment Address (MSBs only). */
    uint8_t     ubOriginBit;        /**< Origin bit (0 = Request, 1 = Response). */
    uint8_t     ubVersion;          /**< 3-bit Messaging Layer version. */
    uint16_t    usChannel;          /**< 16-bit Channel Number. */
    uint8_t     ubExtendedAddr;     /**< 8-bit Extended Address field. */
    uint16_t    usRequestNumber;    /**< 16-bit Request Number field. */
    uint16_t    usDataLength;       /**< Length of the payload in bytes. */
    const uint8_t* pubPayload;      /**< Pointer to the request payload buffer. */
} MessageData_t;

/*******************************************************************************
 * Static Variables
 ******************************************************************************/
/**
 * @brief Internal storage of parsed Messaging Layer fields.
 *
 * This structure holds the most recently decoded message layer data
 * so it can be accessed globally by other modules (e.g., response builder).
 */
static MessageData_t s_stMsgData;

/*******************************************************************************
 * Public Functions
 ******************************************************************************/

/**
 * @brief Initialize the internal message data storage.
 *
 * Clears all fields of the message data structure to ensure
 * a known starting state before parsing any messages.
 */

void MessageData_Init(void)
{
    (void)memset(&s_stMsgData, 0, sizeof(s_stMsgData));
}

/**
 * @brief Set message data fields from a provided structure.
 *
 * Copies the contents of @p pstMsgData into the internal storage
 * if the pointer is not NULL.
 *
 * @param[in] pstMsgData Pointer to the message data structure with parsed values.
 */
void MessageData_SetFields(uint8_t ubEquipmentAddr,
                           uint8_t ubOriginBit,
                           uint8_t ubVersion,
                           uint16_t usChannel,
                           uint8_t ubExtendedAddr,
                           uint16_t usRequestNumber,
                           uint16_t usDataLength,
                           const uint8_t* pubPayload)
{
    s_stMsgData.ubEquipmentAddr = ubEquipmentAddr;
    s_stMsgData.ubOriginBit     = ubOriginBit;
    s_stMsgData.ubVersion       = ubVersion;
    s_stMsgData.usChannel       = usChannel;
    s_stMsgData.ubExtendedAddr  = ubExtendedAddr;
    s_stMsgData.usRequestNumber = usRequestNumber;
    s_stMsgData.usDataLength    = usDataLength;
    s_stMsgData.pubPayload      = pubPayload;
}


/**
 * @brief Get the equipment address from stored message data.
 *
 * @return Equipment address (6-bit value, LSB always set to 1).
 */
uint8_t MessageData_GetEquipmentAddress(void)
{
    return s_stMsgData.ubEquipmentAddr;
}

/**
 * @brief Get the origin bit from stored message data.
 *
 * @return Origin bit (0 = host, 1 = equipment).
 */
uint8_t MessageData_GetOrigin(void)
{
    return s_stMsgData.ubOriginBit;
}

/**
 * @brief Get the version number from stored message data.
 *
 * @return Protocol version (3-bit value).
 */
uint8_t MessageData_GetVersion(void)
{
    return s_stMsgData.ubVersion;
}

/**
 * @brief Get the channel number from stored message data.
 *
 * @return Channel number (0–63).
 */
uint16_t MessageData_GetChannelNumber(void)
{
    return s_stMsgData.usChannel;
}

/**
 * @brief Get the extended address from stored message data.
 *
 * @return Extended address field.
 */
uint8_t MessageData_GetExtendedAddress(void)
{
    return s_stMsgData.ubExtendedAddr;
}

/**
 * @brief Get the request number from stored message data.
 *
 * @return Request number indicating command type.
 */
uint16_t MessageData_GetRequestNumber(void)
{
    return s_stMsgData.usRequestNumber;
}

/**
 * @brief Get the data length of the payload.
 *
 * @return Length of payload in bytes.
 */
uint16_t MessageData_GetDataLength(void)
{
    return s_stMsgData.usDataLength;
}

/**
 * @brief Get a pointer to the payload buffer.
 *
 * @return Pointer to payload data, or NULL if not set.
 */
const uint8_t* MessageData_GetPayloadPointer(void)
{
    return s_stMsgData.pubPayload;
}

/**
 * @brief Update the origin bit in stored message data.
 *
 * Used when modifying message origin during response building.
 *
 * @param[in] ubOrigin Origin bit (0 = host, 1 = equipment).
 */
void MessageData_SetOrigin(uint8_t ubOrigin)
{
    s_stMsgData.ubOriginBit = ubOrigin;
}
