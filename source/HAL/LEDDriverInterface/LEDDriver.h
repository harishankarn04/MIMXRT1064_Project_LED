/**
 * @file LEDDriver.h
 * @brief Hardware Abstraction Layer (HAL) Interface for LED Matrix Panel Driver.
 *
 * (C) Copyright Centum T&S Group 2025. All rights reserved.
 * This computer program may not be used, copied, distributed, translated,
 * transmitted or assigned without the prior written authorization of
 * Centum T&S Group.
 */

#ifndef HAL_LEDDRIVERINTERFACE_LEDDRIVER_H_
#define HAL_LEDDRIVERINTERFACE_LEDDRIVER_H_

//------------------------------------ [ INCLUDE FILES ] ----------------------------//
//
#include "fsl_lpspi.h"
#include "fsl_edma.h"
#include "fsl_lpspi_edma.h"
#if defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT
#include "fsl_dmamux.h"
#endif
#include "app.h"
#include "peripherals.h"

//-------------------------------------[ DEFINES ] ----------------------------------//
//
/* Definition of peripheral ID */
#define BOARD_LED_LPSPI1_PERIPHERAL LPSPI1
/* Definition of clock source */
#define BOARD_LED_LPSPI1_CLOCK_FREQ 105600000UL
#define TRANSFER_SIZE     16UL     /* Transfer dataSize */
#define TRANSFER_BAUDRATE 500000UL /* Transfer baudrate - 500k */

#define LPSPI_MASTER_PCS_FOR_INIT     (kLPSPI_Pcs0)
#define LPSPI_MASTER_PCS_FOR_TRANSFER (kLPSPI_MasterPcs0)

#define LPSPI_MASTER_BASEADDR              (LPSPI1)
#define LPSPI_MASTER_DMA_MUX_BASE          (DMAMUX)
#define LPSPI_MASTER_DMA_RX_REQUEST_SOURCE kDmaRequestMuxLPSPI1Rx
#define LPSPI_MASTER_DMA_TX_REQUEST_SOURCE kDmaRequestMuxLPSPI1Tx
#define LPSPI_MASTER_DMA_BASE              (DMA0)
#define LPSPI_MASTER_DMA_RX_CHANNEL        0U
#define LPSPI_MASTER_DMA_TX_CHANNEL        1U
/* Select USB1 PLL PFD0 (480 MHz) as lpspi clock source */
#define LPSPI_CLOCK_SOURCE_SELECT (1U)
/* Clock divider for master lpspi clock source */
#define LPSPI_CLOCK_SOURCE_DIVIDER (7U)


//GPIOs for LE, OE and 3 address lines
//TODO: GPIO configuration for double sided display and RGB
#define LED_LE_ENABLE		HAL_GpioSetOutput(BOARD_LPSPI1_LED_PINS_LED_LE_handle, 1)
#define LED_LE_DISABLE		HAL_GpioSetOutput(BOARD_LPSPI1_LED_PINS_LED_LE_handle, 0)

#define LED_OE_ENABLE		HAL_GpioSetOutput(BOARD_LPSPI1_LED_PINS_LED_OE_handle, 0)
#define LED_OE_DISABLE		HAL_GpioSetOutput(BOARD_LPSPI1_LED_PINS_LED_OE_handle, 1)

#define LED_A0(x)		HAL_GpioSetOutput(BOARD_LPSPI1_LED_PINS_A0_handle, x)
#define LED_A1(x)		HAL_GpioSetOutput(BOARD_LPSPI1_LED_PINS_A1_handle, x)
#define LED_A2(x)		HAL_GpioSetOutput(BOARD_LPSPI1_LED_PINS_A2_handle, x)


//-------------------------------------[ PROTOTYPES ] -------------------------------//
//

void LEDDriver_Init();

void LEDDriver_ConfigurePanel(uint16_t usDisplayRows,
							  uint16_t usDisplayColumns,
							  uint8_t  ubDoubleSidedDisplay,
							  uint8_t  ubLedType,
							  uint8_t  ubNumPanels,
							  uint8_t  ubNumRowSelection);

void LEDDriver_PrepareDisplayBuffer(uint8_t **ptubActiveBufferNow);

void LEDDriver_DisplayOnLED();

#endif /* HAL_LEDDRIVERINTERFACE_LEDDRIVER_H_ */
