/**
 * @file    MessageData.h
 * @brief   EMP Messaging Layer data storage and accessor module.
 *
 * (C) Copyright Centum T&S Group 2025. All rights reserved.
 * This computer program may not be used, copied, distributed, translated,
 * transmitted, or assigned without the prior written authorization of
 * Centum T&S Group.
 */


#ifndef MESSAGEDATA_H
#define MESSAGEDATA_H

#include <stdint.h>

/*******************************************************************************
 * Function Prototypes
 ******************************************************************************/

/**
 * @brief Initialize the internal message data storage.
 *
 * Clears all fields of the message data structure to ensure
 * a known starting state before parsing any messages.
 */
void MessageData_Init(void);

/**
 * @brief Stores all parsed Messaging Layer fields for global access.
 *
 * @param pstMsgData Pointer to structure containing parsed Messaging Layer fields.
 */
void MessageData_SetFields(uint8_t ubEquipmentAddr,
                           uint8_t ubOriginBit,
                           uint8_t ubVersion,
                           uint16_t usChannel,
                           uint8_t ubExtendedAddr,
                           uint16_t usRequestNumber,
                           uint16_t usDataLength,
                           const uint8_t* pubPayload);


/**
 * @brief Returns the Equipment Address field.
 *
 * @return Equipment Address (6-bit value).
 */
uint8_t MessageData_GetEquipmentAddress(void);

/**
 * @brief Returns the parsed Channel Number.
 *
 * @return Channel number.
 */
uint16_t MessageData_GetChannelNumber(void);

/**
 * @brief Returns the Extended Address field.
 *
 * @return Extended Address (8-bit value).
 */
uint8_t MessageData_GetExtendedAddress(void);

/**
 * @brief Returns the Request Number.
 *
 * @return Request Number (16-bit value).
 */
uint16_t MessageData_GetRequestNumber(void);

/**
 * @brief Returns the payload length.
 *
 * @return Payload length in bytes.
 */
uint16_t MessageData_GetDataLength(void);

/**
 * @brief Returns a pointer to the payload buffer.
 *
 * @return Pointer to payload data.
 */
const uint8_t* MessageData_GetPayloadPointer(void);


#endif /* MESSAGEDATA_H */
