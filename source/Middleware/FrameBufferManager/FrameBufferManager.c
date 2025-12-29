/**
 * @file FrameBufferManager.c
 * @brief Manages dynamic 2D frame buffers (Active and Reserve) for flicker-free display updates.
 *
 * Implements double-buffering, memory allocation/deallocation, and atomic swapping
 * of buffer pointers to synchronize LED display routines.
 *
 * (C) Copyright Centum T&S Group 2025. All rights reserved.
 * This computer program may not be used, copied, distributed, translated,
 * transmitted or assigned without the prior written authorization of
 * Centum T&S Group.
 */

//------------------------------------ [ INCLUDE FILES ] ----------------------------//
//

#include "fsl_debug_console.h"
#include "Middleware/FrameBufferManager/FrameBufferManager.h"
#include "Middleware/LogManager/LogManager.h"
//-------------------------------------[ STATIC VARIABLE ] --------------------------//
//
static uint8_t **ptubActiveFrontBuffer = NULL;
static uint8_t **ptubReserveFrontBuffer = NULL;
static uint8_t **ptubActiveRearBuffer = NULL;
static uint8_t **ptubReserveRearBuffer = NULL;
static bool     bIsInitialised = false;

static int isDoubleSidedDisplay = 0;

//-------------------------------------[ LOCAL PROTOTYPES ] -------------------------//
//
static uint8_t **AllocateBuffer(uint8_t ubHeight, uint16_t usWidth);

//-------------------------------------[ GLOBAL FUNCTIONS ] -------------------------//
//

/**
 * @brief Initializes the frame buffer system by allocating Active and Reserve buffers.
 *
 * This function must be called once before any other FBM function.
 *
 * @param usDisplayRows 		Number of rows in one LED panel.
 * @param usDisplayColumns 		Number of columns in one LED panel.
 * @param ubDoubleSidedDisplay  0 - Single sided display, 1 - Double sided display
 * @param ubLedType				0 - Monochrome LED, 1 - RGB LED
 * @param ubNumPanels           Number of LED panels connected serially
 * @return 1 on successful allocation and initialization, 0 on failure or if already initialized.
 */
uint8_t FBM_Init(uint16_t usDisplayRows, uint16_t usDisplayColumns, uint8_t  ubDoubleSidedDisplay, uint8_t  ubLedType, uint8_t ubNumPanels)
{
    if (bIsInitialised)
    {
        COSLOG_INFO("FBM_InitManager: Manager already initialized. Call FBM_DeinitializeSystem first.\n");
        return 0;
    }

    if (usDisplayRows == 0 || usDisplayColumns == 0)
    {
    	return 0;
    }

    if (ubLedType)
    {
    	//TODO: Allocate Buffer of appropriate size for color LED
    	return 1;
    }

    //Buffer allocation for monochrome Buffer
    // Allocate Active Buffer using AllocateBuffer
    ptubActiveFrontBuffer = AllocateBuffer(usDisplayRows, usDisplayColumns*ubNumPanels);
    if (NULL == ptubActiveFrontBuffer)
    {
        COSLOG_ERROR("FBM_InitManager: Failed to allocate Active Buffer.\n");
        return 0;
    }
    // Allocate Reserve Buffer using AllocateBuffer
    ptubReserveFrontBuffer = AllocateBuffer(usDisplayRows, usDisplayColumns*ubNumPanels);
    if (NULL == ptubReserveFrontBuffer)
    {
        COSLOG_ERROR("FBM_InitManager: Failed to allocate Reserve Buffer. Cleaning up Active Buffer.\n");
        // Use the unmodified FBM_FreeBuffer for cleanup
        FBM_FreeBuffer(ptubActiveFrontBuffer, usDisplayRows);
        ptubActiveFrontBuffer = NULL;
        return 0;
    }

    //Allocation of Active and reserve buffers if Double sided display
    if (ubDoubleSidedDisplay)
    {
    	isDoubleSidedDisplay = 1;
    	// Allocate Active Buffer using AllocateBuffer
		ptubActiveRearBuffer = AllocateBuffer(usDisplayRows, usDisplayColumns*ubNumPanels);
		if (NULL == ptubActiveRearBuffer)
		{
			COSLOG_ERROR("FBM_InitManager: Failed to allocate Active Buffer for back panel.\n");
			return 0;
		}
		// Allocate Reserve Buffer using AllocateBuffer
		ptubReserveRearBuffer = AllocateBuffer(usDisplayRows, usDisplayColumns*ubNumPanels);
		if (NULL == ptubReserveRearBuffer)
		{
			COSLOG_ERROR("FBM_InitManager: Failed to allocate Reserve Buffer. Cleaning up Active Buffer for back panel.\n");
			// Use the unmodified FBM_FreeBuffer for cleanup
			FBM_FreeBuffer(ptubActiveRearBuffer, usDisplayRows);
			ptubActiveFrontBuffer = NULL;
			return 0;
		}
    }

    bIsInitialised = true;
    return 1;
}


/**
 * @brief Frees all memory allocated for the Active and Reserve buffers and resets state.
 *
 * @param usDisplayRows 		Number of rows in one LED panel.
 */
void FBM_DeinitializeSystem(uint16_t usDisplayRows)
{
    if (!bIsInitialised)
    {
        return;
    }
    // Free Active Buffer using the unmodified FBM_FreeBuffer
    FBM_FreeBuffer(ptubActiveFrontBuffer, usDisplayRows);
    // Free Reserve Buffer using the unmodified FBM_FreeBuffer
    FBM_FreeBuffer(ptubReserveFrontBuffer, usDisplayRows);

    if (isDoubleSidedDisplay)
    {
        // Free Active Buffer using the unmodified FBM_FreeBuffer
        FBM_FreeBuffer(ptubActiveRearBuffer, usDisplayRows);
        // Free Reserve Buffer using the unmodified FBM_FreeBuffer
        FBM_FreeBuffer(ptubReserveRearBuffer, usDisplayRows);

        // Reset static state
        ptubActiveRearBuffer = NULL;
        ptubReserveRearBuffer = NULL;
    }
    // Reset static state
    ptubActiveFrontBuffer = NULL;
    ptubReserveFrontBuffer = NULL;
    bIsInitialised = false;
}


/**
 * @brief Gets the pointer to the currently active buffer.
 * @return Pointer to the Active Buffer (uint8_t **), or NULL if not initialized.
 */
uint8_t **FBM_GetActiveFrontBuffer(void)
{
    if (!bIsInitialised)
    {
        COSLOG_INFO("FBM_GetActiveBuffer: Manager not initialized.\n");
        return NULL;
    }
    return ptubActiveFrontBuffer;
}

/**
 * @brief Gets the pointer to the currently active buffer for rear LED panel.
 * @return Pointer to the Active Buffer (uint8_t **) for rear LED panel, or NULL if not initialized.
 */
uint8_t **FBM_GetActiveRearBuffer(void)
{
    if (!bIsInitialised)
    {
        COSLOG_INFO("FBM_GetActiveBuffer: Manager not initialized.\n");
        return NULL;
    }

    //If not a double sided display, ptubActiveRearBuffer is NULL
    return ptubActiveRearBuffer;
}


/**
 * @brief Gets the pointer to the currently reserve buffer.
 * @return Pointer to the Reserve Buffer (uint8_t **), or NULL if not initialized.
 */
uint8_t **FBM_GetReserveFrontBuffer(void)
{
    if (!bIsInitialised) {
        COSLOG_INFO("FBM_GetReserveBuffer: Manager not initialized.\n");
        return NULL;
    }
    return ptubReserveFrontBuffer;
}

/**
 * @brief Gets the pointer to the current reserve buffer for rear LED panel.
 * @return Pointer to the Reserve Buffer (uint8_t **), or NULL if not initialized.
 */
uint8_t **FBM_GetReserveRearBuffer(void)
{
    if (!bIsInitialised) {
        COSLOG_INFO("FBM_GetReserveBuffer: Manager not initialized.\n");
        return NULL;
    }

    //If not a double sided display, ptubReserveRearBuffer is NULL
    return ptubReserveRearBuffer;
}

/**
 * @brief Atomically swaps the Active and Reserve buffer pointers.
 *
 * This action makes the newly drawn Reserve buffer visible to the LED driver.
 */
void FBM_SwapBuffers(void)
{
    if (!bIsInitialised) {
        COSLOG_INFO("FBM_SwapBuffers: Manager not initialized. Cannot swap.\n");
        return;
    }
    // Use a temporary pointer to swap the two static pointers
    //Swap Front Buffers
    uint8_t **ptubTemp = ptubActiveFrontBuffer;
    ptubActiveFrontBuffer = ptubReserveFrontBuffer;
    ptubReserveFrontBuffer = ptubTemp;

    if (isDoubleSidedDisplay)
    {
    //Swap rear buffers
    ptubActiveRearBuffer = ptubReserveRearBuffer;
    ptubReserveRearBuffer = ptubTemp;
    }
}

/**
 * @brief Frees the memory allocated for a 2D buffer.
 *
 * Cleans up both the individual row memory and the array of row pointers.
 *
 * @param ptubBuffer Pointer to the 2D buffer structure to free.
 * @param usHeight The height of the buffer (number of rows) used for iteration.
 */
void FBM_FreeBuffer(uint8_t **ptubBuffer, uint8_t ubHeight)
{
    // Now takes the double pointer directly.
    if (NULL != ptubBuffer)
    {
        for (uint8_t ubRow = 0; ubRow < ubHeight; ubRow++)
        {
            // Note: We check if the row pointer is NULL before freeing.
            if (NULL != ptubBuffer[ubRow])
            {
                free(ptubBuffer[ubRow]);
            }
        }
        free(ptubBuffer);

        // **The calling code must now set its own pointer to NULL.**

    }
}


/**
 * @brief Clears a 2D buffer by setting all its data bytes to zero.
 *
 * @param ptubBuffer Pointer to the 2D buffer structure to clear.
 * @param usHeight The height of the buffer.
 * @param usWidth The width of the buffer in columns.
 */
void FBM_ClearBuffer(uint8_t **ptubBuffer, uint8_t ubHeight, uint16_t usWidth)
{
    if (NULL != ptubBuffer)
    {
        uint16_t usBytesPerRow = (usWidth + 7U) / 8U;
        for (uint8_t ubRow = 0; ubRow < ubHeight; ubRow++)
        {
            if (NULL != ptubBuffer[ubRow])
            {
                (void)memset(ptubBuffer[ubRow], 0, usBytesPerRow);
            }
        }
    }
}

//-------------------------------------[ LOCAL FUNCTIONS ] -------------------------//
//
/**
 * @brief Allocates memory for a 2D buffer structure (array of row pointers).
 *
 * This function performs a two-level memory allocation: first for the row pointers,
 * then for each row's data.
 *
 * @param usHeight The height of the buffer (number of rows).
 * @param usWidth The width of the buffer in columns (used to calculate bytes per row).
 * @return A pointer to the newly allocated 2D buffer (uint8_t **), or NULL on failure.
 */
static uint8_t **AllocateBuffer(uint8_t ubHeight, uint16_t usWidth)
{

    uint8_t **ptubBuffer = NULL;

    uint16_t usBytesPerRow = (usWidth + 7U) / 8U;

    // 1. Allocate memory for the array of row pointers (Level 2).
    ptubBuffer = (uint8_t **)malloc(ubHeight * sizeof(uint8_t *));

    if (NULL != ptubBuffer)
    {
        uint8_t ubRow = 0;
        // The success check is implied by returning NULL or the valid pointer.
        // We initialize the entire array to NULL to simplify cleanup on failure.
        (void)memset(ptubBuffer, 0, ubHeight * sizeof(uint8_t *));

        while (ubRow < ubHeight)
        {
            // 2. Allocate memory for the current row's data (Level 1).
            ptubBuffer[ubRow] = (uint8_t *)calloc(usBytesPerRow, sizeof(uint8_t));

            if (NULL == ptubBuffer[ubRow])
            {
                // Allocation for a row failed. Call Free to clean up the partially allocated structure.
                FBM_FreeBuffer(ptubBuffer, ubRow); // We pass ubRow as height to clean up only allocated rows.

                // Set our local pointer to NULL before returning failure.
                ptubBuffer = NULL;
                break;
            }
            ubRow++;
        }
    }

    // Return the allocated buffer pointer (or NULL on failure).
    return ptubBuffer;
}


