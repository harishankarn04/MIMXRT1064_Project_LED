/**
 * @file LEDDriver.c
 * @brief Low-level driver implementation for controlling the LED matrix via LPSPI and EDMA.
 *
 * This file contains the hardware configuration for the LPSPI master, EDMA, and DMAMUX,
 * as well as data preparation routines (Gray code conversion, row mapping) necessary
 * to stream frame buffer data to the LED panels.
 *
 * (C) Copyright Centum T&S Group 2025. All rights reserved.
 * This computer program may not be used, copied, distributed, translated,
 * transmitted or assigned without the prior written authorization of
 * Centum T&S Group.
 */

//------------------------------------ [ INCLUDE FILES ] ----------------------------//
//
#include "HAL/LEDDriverInterface/LEDDriver.h"
#include "string.h"

//-------------------------------------[ TYPEDEF ] ----------------------------------//
//
typedef struct {
    int dec;      // Scan Address
    int row;      // Physical Rows
} sRowAddress_t;

//-------------------------------------[ STATIC VARIABLE ] --------------------------//
//
static lpspi_master_config_t sLpspiConfig;
static lpspi_master_edma_handle_t sEdmaHandle;
static edma_config_t sEdmaConfig = {
		  .enableContinuousLinkMode = false,
		  .enableHaltOnError = true,
		  .enableRoundRobinArbitration = false,
		  .enableDebugMode = false};
static edma_handle_t sLpspiEdmaMasterRxRegToRxDataHandle;
static edma_handle_t sLpspiEdmaMasterTxRegToTxDataHandle;

// Array to store the mapping, filled programmatically at runtime.
static sRowAddress_t *psRowAddressMap = NULL;
static uint8_t **ubCombinedData = NULL;
static uint8_t ubRowSize = 0;
static lpspi_transfer_t sMasterXfer;

static volatile bool bIsTransferCompleted = true;

//Configuration parameters received from LEDDriver_ConfigurePanel()
static uint16_t usRowsPerPanel = 0;
static uint16_t usColumnsPerPanel = 0;
static uint8_t ubNumberofPanels = 0;
static uint8_t ubIsDoubleSidedDisplay = 0;
static uint8_t ubIsRGB = 0;
static uint8_t ubNumberofRowAddressBits = 0;

//Derived Parameters
static uint8_t ubScanRate = 0;
static uint8_t ubRowsPerScanAddress = 0;
static uint8_t ubTotalColumnsPerRowBytes = 0;
static uint32_t ulDataBitsPerScanCycle = 0;
static uint32_t ulSpiPayloadSizeBytes = 0;

//-------------------------------------[ LOCAL PROTOTYPES ] -------------------------//
//
static void LPSPIMasterUserCallback(LPSPI_Type *base, lpspi_master_edma_handle_t *handle, status_t status, void *userData);
static void InitializeRowAddressMap();
static void SPITransfer(void);

//-------------------------------------[ GLOBAL FUNCTIONS ] -------------------------//
//

/**
 * @brief Initializes the eDMA peripheral and LPSPI1 peripheral as a Master.
 *
 *
 * Configures the clock, sets standard SPI parameters (baud rate, bits per frame),
 * and creates the EDMA-aware transfer handle for asynchronous operations.
 */

void LEDDriver_Init()
{
	/*DMA Mux setting and EDMA init*/
	#if defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT
	    /* DMA MUX init*/
	    DMAMUX_Init(LPSPI_MASTER_DMA_MUX_BASE);

	    DMAMUX_SetSource(LPSPI_MASTER_DMA_MUX_BASE, LPSPI_MASTER_DMA_RX_CHANNEL,
	                     LPSPI_MASTER_DMA_RX_REQUEST_SOURCE);
	    DMAMUX_EnableChannel(LPSPI_MASTER_DMA_MUX_BASE, LPSPI_MASTER_DMA_RX_CHANNEL);

	    DMAMUX_SetSource(LPSPI_MASTER_DMA_MUX_BASE, LPSPI_MASTER_DMA_TX_CHANNEL,
	                     LPSPI_MASTER_DMA_TX_REQUEST_SOURCE);
	    DMAMUX_EnableChannel(LPSPI_MASTER_DMA_MUX_BASE, LPSPI_MASTER_DMA_TX_CHANNEL);
	#endif

    /* EDMA init*/
    EDMA_GetDefaultConfig(&sEdmaConfig);
#if defined(BOARD_GetEDMAConfig)
    BOARD_GetEDMAConfig(sEdmaConfig);
#endif
    EDMA_Init(LPSPI_MASTER_DMA_BASE, &sEdmaConfig);

    EDMA_EnableMinorLoopMapping(LPSPI_MASTER_DMA_BASE, true);


    memset(&(sLpspiEdmaMasterRxRegToRxDataHandle), 0, sizeof(sLpspiEdmaMasterRxRegToRxDataHandle));
    memset(&(sLpspiEdmaMasterTxRegToTxDataHandle), 0, sizeof(sLpspiEdmaMasterTxRegToTxDataHandle));

    EDMA_CreateHandle(&(sLpspiEdmaMasterRxRegToRxDataHandle), LPSPI_MASTER_DMA_BASE,
                      LPSPI_MASTER_DMA_RX_CHANNEL);
    EDMA_CreateHandle(&(sLpspiEdmaMasterTxRegToTxDataHandle), LPSPI_MASTER_DMA_BASE,
                      LPSPI_MASTER_DMA_TX_CHANNEL);

#if defined(FSL_FEATURE_EDMA_HAS_CHANNEL_MUX) && FSL_FEATURE_EDMA_HAS_CHANNEL_MUX
    EDMA_SetChannelMux(LPSPI_MASTER_DMA_BASE, LPSPI_MASTER_DMA_TX_CHANNEL,
                       DEMO_LPSPI_TRANSMIT_EDMA_CHANNEL);
    EDMA_SetChannelMux(LPSPI_MASTER_DMA_BASE, LPSPI_MASTER_DMA_RX_CHANNEL,
                       DEMO_LPSPI_RECEIVE_EDMA_CHANNEL);
#endif

    /*Set clock source for LPSPI*/
    	CLOCK_SetMux(kCLOCK_LpspiMux, LPSPI_CLOCK_SOURCE_SELECT);
    	CLOCK_SetDiv(kCLOCK_LpspiDiv, LPSPI_CLOCK_SOURCE_DIVIDER);

        LPSPI_MasterGetDefaultConfig(&sLpspiConfig);
        sLpspiConfig.baudRate = TRANSFER_BAUDRATE;
        sLpspiConfig.bitsPerFrame = 8;
    	sLpspiConfig.whichPcs = LPSPI_MASTER_PCS_FOR_INIT;
    	sLpspiConfig.pcsToSckDelayInNanoSec        = 0;
    	sLpspiConfig.lastSckToPcsDelayInNanoSec    = 0;
    	sLpspiConfig.betweenTransferDelayInNanoSec = 0;

        LPSPI_MasterInit(BOARD_LED_LPSPI1_PERIPHERAL, &sLpspiConfig, BOARD_LED_LPSPI1_CLOCK_FREQ);

        /*Set up lpspi master transfer handle*/
        // This function sets up the internal EDMA callbacks, preventing the hang.
        LPSPI_MasterTransferCreateHandleEDMA(LPSPI_MASTER_BASEADDR, &sEdmaHandle, LPSPIMasterUserCallback,
                 	 	 	 	 	 	 	  NULL, &sLpspiEdmaMasterRxRegToRxDataHandle,
    										  &sLpspiEdmaMasterTxRegToTxDataHandle);
     	LPSPI_MasterTransferPrepareEDMALite(BOARD_LED_LPSPI1_PERIPHERAL, &sEdmaHandle, kLPSPI_MasterPcs0 | kLPSPI_MasterPcsContinuous);
}


//TODO: Needs to be called by display controller
void LEDDriver_ConfigurePanel(uint16_t usDisplayRows,
							  uint16_t usDisplayColumns,
							  uint8_t  ubDoubleSidedDisplay,
							  uint8_t  ubLedType,
							  uint8_t  ubNumPanels,
							  uint8_t  ubNumRowSelection)
{
	//-------------------------------------------------//
	//Extract all LED configuration parameters
	usRowsPerPanel = usDisplayRows;
	usColumnsPerPanel = usDisplayColumns;
	ubIsDoubleSidedDisplay = ubDoubleSidedDisplay;
	ubIsRGB = ubLedType;
	ubNumberofPanels = ubNumPanels;
	ubNumberofRowAddressBits = ubNumRowSelection;

	//-------------------------------------------------//
	//Initialising derived parameters

	//Number of unique scan addresses
	ubScanRate = (1 << ubNumberofRowAddressBits);

	// The number of physical rows selected simultaneously by one address
	ubRowsPerScanAddress = (usRowsPerPanel/ubScanRate);

	// The size of one physical row's data across all panels, in bytes.
	// Eg : (128 columns / 8 bits/byte = 16 bytes)
	ubTotalColumnsPerRowBytes = ((ubNumberofPanels * usColumnsPerPanel)/8);

	//Total number of data bits per scan cycle - Across all columns and panels for number of rows that can be selected at once
	ulDataBitsPerScanCycle = (ubNumberofPanels * usColumnsPerPanel * ubRowsPerScanAddress);

	// Size of the SPI payload buffer in bytes (e.g., 256 bits / 8 = 32 bytes)
	ulSpiPayloadSizeBytes = (ulDataBitsPerScanCycle / 8);


	//Allocating memory for ubCombinedData
	size_t TotalDataBytes = (size_t)ubScanRate*ulSpiPayloadSizeBytes;
	if(ubCombinedData != NULL && ubCombinedData[0] != NULL)
	{
		free(ubCombinedData[0]);
		free(ubCombinedData);
	}

	// Allocate the array of row pointers (The "rows" of the 2D array)
	ubCombinedData = (uint8_t **)malloc(ubScanRate * sizeof(uint8_t *));
	if (ubCombinedData == NULL)
	{ /* Handle error */
		return;
	}

	// Allocate the single, contiguous block for all the data (The memory for the SPI transfer)
	uint8_t *pubDataBlock = (uint8_t *)malloc(TotalDataBytes);
	if (pubDataBlock == NULL)
	{
		free(ubCombinedData);
		ubCombinedData = NULL; /* Handle error */
		return;
	}

	// Point each row pointer into the contiguous data block
	for (int n = 0; n < ubScanRate; n++)
	{
		ubCombinedData[n] = pubDataBlock + (n * ulSpiPayloadSizeBytes);
	}

	// Initialize the new buffer to zero for safety
	memset(pubDataBlock, 0, TotalDataBytes);

	//-------------------------------------------------//
	//Allocating memory for psRowAddress

	// Check if memory is already allocated (for re-configuration) and free it
	if (psRowAddressMap != NULL)
	{
		free(psRowAddressMap);
	}

	// Allocate the exact amount of memory needed
	psRowAddressMap = (sRowAddress_t *)malloc(usRowsPerPanel * sizeof(sRowAddress_t));

	if (psRowAddressMap == NULL)
	{
		// Handle allocation failure
		usRowsPerPanel = 0;
		return;
	}
	//Build Row address map according to the configuration parameters
	InitializeRowAddressMap();

}
/**
 * @brief Prepares the `ubCombinedData` buffer for all scan addresses.
 *
 * Reads data from the active frame buffer (`ptubActiveBufferNow`), applies the
 * row mapping (including rotation), and concatenates the rows required
 * for each physical scan address into a single contiguous block for SPI transfer.
 *
 * Note : Needs to be called every time the data in Active buffer changes
 */
void LEDDriver_PrepareDisplayBuffer(uint8_t **ptubActiveBufferNow)
{
    for (int n = 0; n < ubScanRate; n++)
    {
        uint8_t ubFound = 0;
        for (int i = 0; i < usRowsPerPanel; i++)
        {
            if (psRowAddressMap[i].dec == n)
            {
                memcpy(ubCombinedData[n] + ubFound * ubTotalColumnsPerRowBytes, ptubActiveBufferNow[psRowAddressMap[i].row], ubTotalColumnsPerRowBytes);
                ubFound++;
                if (ubFound == ubRowsPerScanAddress) break;
            }
        }
    }
}

void LEDDriver_DisplayOnLED()
{
	if (bIsTransferCompleted == 1)
	{
		LED_LE_ENABLE;
		SDK_DelayAtLeastUs(10, CLOCK_GetCoreSysClkFreq());// TODO :
		LED_LE_DISABLE;

		LED_OE_ENABLE;
		SDK_DelayAtLeastUs(100, CLOCK_GetCoreSysClkFreq());// TODO :
		LED_OE_DISABLE;

		SDK_DelayAtLeastUs(100, CLOCK_GetCoreSysClkFreq());// TODO :
		SPITransfer();
	}
}

//-------------------------------------[ LOCAL FUNCTIONS ] -------------------------//
//
/**
 * @brief Initializes the row address map for display rotation.
 *
 * Calculates the source row index (`row`) in the frame buffer that corresponds to a
 * physical scan address (`dec`) for a 180-degree display rotation.
 * This is called once during initialization or before building data.
 */
static void InitializeRowAddressMap(void)
{
    // This function is updated to map data for a 180-degree rotation.
    for (int i = 0; i < usRowsPerPanel; i++)
    {
        // 1. Determine the source row index in the frame buffer to flip the content (15 -> 0, 0 -> 15)
        uint8_t ubSourceRowIndex = usRowsPerPanel - 1 - i;

        // 2. Apply the original scan address logic to the *source row index* (0 to 15)
        uint8_t ubScanAddress;

        if (ubSourceRowIndex < ubScanRate)
        {
            // First half of source data (rows 0-7) map to scan addresses 7 down to 0
            ubScanAddress = ubScanRate - 1 - ubSourceRowIndex; // 7 - ubSourceRowIndex
        }
        else
        {
            // Second half of source data (rows 8-15) map to scan addresses 0 up to 7
            ubScanAddress = ubSourceRowIndex - ubScanRate; // ubSourceRowIndex - 8
        }

        // The current physical display row (i) is driven by 'ubScanAddress'
        // and should pull its data from 'ubSourceRowIndex'.
        psRowAddressMap[i].dec = ubScanAddress;
        psRowAddressMap[i].row = ubSourceRowIndex; // Set data source row to the flipped index
    }
}


/**
 * @brief Converts a standard binary number to its corresponding Gray code.
 *
 * The Gray code is used for the row select addresses to prevent transient states.
 *
 * @param ubBin The binary value to convert (e.g., the row index).
 * @return The 8-bit Gray code equivalent.
 */
static inline uint8_t BinaryToGray(uint8_t ubBin) {
    // Standard binary to Gray conversion: G = B ^ (B >> 1)
    return ubBin ^ (ubBin >> 1);
}

/**
 * @brief Selects the physical row to be displayed by driving the address lines (A, B, C, etc.).
 *
 * The row index is first converted to Gray code before being output to the LED address pins.
 *
 * @param ubRow The 0-indexed row (0 to ubScanRate - 1) to select.
 */
static void LEDRowSelect(uint8_t ubRow)
{
    // Ensure input is within bounds
    if (ubRow >= ubScanRate) return;

    // 1. Calculate the Gray Code for the binary scan address (0-7)
    // This removes the hardcoded lookup table for address bits.
    uint8_t ubGrayCode = BinaryToGray(ubRow);

    // 2. Output the calculated Gray code bits to the address pins.
    LED_A0((ubGrayCode >> 0) & 0x01);
    LED_A1((ubGrayCode >> 1) & 0x01);
    LED_A2((ubGrayCode >> 2) & 0x01);
}

/**
 * @brief SPI handler for display refresh.
 *
 * Manages one step of the display scan cycle: setting the row address, initiating
 * the LPSPI DMA transfer, and advancing the row counter.
 *
 * @param void No parameters.
 * @return void No return value.
 */
static void SPITransfer(void)
{
    bIsTransferCompleted = false;
    LEDRowSelect(ubRowSize);
	/*Start master transfer*/
	sMasterXfer.txData   = ubCombinedData[ubRowSize];
	sMasterXfer.rxData   = NULL;
	sMasterXfer.dataSize = ulSpiPayloadSizeBytes;
	LPSPI_MasterTransferEDMALite(BOARD_LED_LPSPI1_PERIPHERAL, &sEdmaHandle, &sMasterXfer);

	ubRowSize++;
	if(ubRowSize  >= 8 )
	{
		ubRowSize = 0;
	}
}

/**
 * @brief Callback function executed upon completion of an LPSPI Master EDMA transfer.
 *
 * This function is registered with the EDMA handle and is called by the EDMA interrupt
 * service routine when the transfer is finished.
 *
 * @param base LPSPI peripheral base address.
 * @param handle Pointer to the LPSPI master EDMA transfer handle.
 * @param status Status of the transfer (kStatus_Success or an error code).
 * @param userData Custom data pointer (unused in this implementation).
 */
static void LPSPIMasterUserCallback(LPSPI_Type *base, lpspi_master_edma_handle_t *handle, status_t status, void *userData)
{

    if (status == kStatus_Success)
    {
        // The transfer finished. We set a flag to release the CPU from its waiting loop.
        bIsTransferCompleted = true;
    }
}


