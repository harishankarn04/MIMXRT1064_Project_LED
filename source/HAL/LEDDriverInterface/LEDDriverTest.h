/**
 * @file LEDDriverTest.h
 * @brief Contains the LED configuration parameters used to test the LED driver
 *
 * (C) Copyright Centum T&S Group 2025. All rights reserved.
 * This computer program may not be used, copied, distributed, translated,
 * transmitted or assigned without the prior written authorization of
 * Centum T&S Group.
 */


#ifndef HAL_LEDDRIVERINTERFACE_LEDDRIVERTEST_H_
#define HAL_LEDDRIVERINTERFACE_LEDDRIVERTEST_H_

//------------------------------------ [ INCLUDE FILES ] ----------------------------//
//
#include "HAL/LEDDriverInterface/LEDDriver.h"
#include "stdint.h"

//-------------------------------------[ DEFINES ] ----------------------------------//
//
#define NUM_PANELS      2       // Total number of panels connected serially
#define ROWS_PER_PANEL  16      // Physical rows per panel (16)
#define COLS_PER_PANEL  64      // Physical columns per panel (64)
#define ROW_ADDR_BITS           3

#define DOUBLE_SIDED_DISPLAY 0
#define LED_TYPE 0

#define TOTAL_COLS_PER_ROW_BYTES ((NUM_PANELS * COLS_PER_PANEL)/8)

//-------------------------------------[ PROTOTYPES ] --------------------------//
//
extern uint8_t BitControlBuffer[ROWS_PER_PANEL][TOTAL_COLS_PER_ROW_BYTES];

extern uint8_t BitControlBufferHELLO[ROWS_PER_PANEL][TOTAL_COLS_PER_ROW_BYTES];

uint8_t LEDDriverTest_LoadData(uint8_t **ptubBuffer, uint8_t BitControlBuffer[ROWS_PER_PANEL][TOTAL_COLS_PER_ROW_BYTES]);

#endif /* HAL_LEDDRIVERINTERFACE_LEDDRIVERTEST_H_ */
