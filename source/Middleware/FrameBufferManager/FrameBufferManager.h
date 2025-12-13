/**
 * @file FrameBufferManager.h
 * @brief Public interface for the Frame Buffer Manager module.
 *
 * This header defines the functions used to initialize, manage, and access
 * the double-buffered display memory, ensuring atomic updates for flicker-free
 * rendering on the LED matrix.
 *
 * (C) Copyright Centum T&S Group 2025. All rights reserved.
 * This computer program may not be used, copied, distributed, translated,
 * transmitted or assigned without the prior written authorization of
 * Centum T&S Group.
 */


#ifndef MIDDLEWARE_FRAMEBUFFERMANAGER_FRAMEBUFFERMANAGER_H_
#define MIDDLEWARE_FRAMEBUFFERMANAGER_FRAMEBUFFERMANAGER_H_

//------------------------------------ [ INCLUDE FILES ] ----------------------------//
//
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//-------------------------------------[ PROTOTYPES ] -------------------------------//
//


uint8_t FBM_Init(uint16_t usDisplayRows, uint16_t usDisplayColumns, uint8_t  ubDoubleSidedDisplay, uint8_t  ubLedType, uint8_t ubNumPanels);

void FBM_DeinitializeSystem(uint16_t usDisplayRows);

uint8_t **FBM_GetActiveFrontBuffer(void);

uint8_t **FBM_GetReserveFrontBuffer(void);

uint8_t **FBM_GetActiveRearBuffer(void);

uint8_t **FBM_GetReserveRearBuffer(void);

void FBM_SwapBuffers(void);

void FBM_FreeBuffer(uint8_t **ptubBuffer, uint8_t usHeight);

void FBM_ClearBuffer(uint8_t **ptubBuffer, uint8_t usHeight, uint16_t usWidth);

#endif /* MIDDLEWARE_FRAMEBUFFERMANAGER_FRAMEBUFFERMANAGER_H_ */
