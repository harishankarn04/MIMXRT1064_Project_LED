/**
* @file timer.c
* @brief Lightweight software timer library Using PIT free-running counter on i.MX RT1064.
* All timing is done in microseconds.
*
* (C) Copyright Centum T&S Group 2025. All rights reserved.
* This computer program may not be used, copied, distributed, translated, transmitted or assigned * without the prior written authorization of Centum T&S Group.
*
**/

#include "timer.h"
#include "fsl_pit.h"
#include "common/CommonDefs.h"


#define PIT_CHANNEL kPIT_Chnl_0   /**< Use PIT channel 0 for free-running timer. */


/**
 * @brief Software timer object.
 *
 * This structure tracks the start time, duration, and active state
 * of a software timer instance.
 */
typedef struct {
    uint32_t ulStartTimeUs;
    uint32_t ulDurationUs;
    uint8_t  ubExpired;
} sSoftTimer_t;


/*******************************************************************************
 * Variables
 ******************************************************************************/
static uint32_t gulPitClkHz;     /**< PIT peripheral clock frequency in Hz (set during Timer_Create). */
static uint32_t gulReloadValue;  /**< Reload value for PIT free-running counter. */


/**
 * @brief Get current time in microseconds since Timer_Create().
 *
 * Reads the free-running PIT counter and converts the elapsed ticks into
 * microseconds. Handles the down-counter behavior of PIT.
 *
 * @return Current elapsed time in microseconds.
 */
static uint32_t Timer_GetTimeUs(void) {
    uint32_t ulCurrentCount = PIT_GetCurrentTimerCount(PIT, PIT_CHANNEL);

    // PIT is down-counter -> ulElapsed = (reload - current)
    uint32_t ulElapsedTicks = gulReloadValue - ulCurrentCount;

    // Convert ticks -> microseconds
    uint64_t udUs = ((uint64_t)ulElapsedTicks * 1000000ULL) / gulPitClkHz;

    return (uint32_t)udUs;
}


static void Timer_Init(void)
{
    pit_config_t sPitConfig;

    PIT_GetDefaultConfig(&sPitConfig);
    PIT_Init(PIT, &sPitConfig);   // udUse SDK PIT macro

    /* Initialize static variables */
    gulPitClkHz = 0U;
    gulReloadValue = 0U;

    gulPitClkHz = CLOCK_GetFreq(kCLOCK_PerClk);

    gulReloadValue = 0xFFFFFFFF;//(gulPitClkHz ) - 1U;
    // Free-running counter (max reload value)
    PIT_SetTimerPeriod(PIT, PIT_CHANNEL, gulReloadValue);

    PIT_StartTimer(PIT, PIT_CHANNEL);
}
/**
 * @brief Initialize the PIT module as a free-running timer.
 *
 * Configures the PIT peripheral and starts a single channel as a continuous
 * down counter with the maximum reload value. Used as the time base for
 * software timers.
 */

/**
 * @brief Create and initialize a software timer.
 *
 * Allocates memory for a software timer, sets its duration, and starts it.
 *
 * @param[out] ppT Pointer to timer handle (allocated inside).
 * @param[in] ulDuration Duration value (depends on unit).
 * @param[in] eUnit Time unit (seconds, milliseconds, microseconds).
 *
 * @return uint8_t
 *         - 1 if timer created successfully,
 *         - 0 if allocation failed or invalid input.
 */
uint8_t Timer_Create(void **ppT, uint32_t ulDuration, eTimeUnit eUnit)
{
    static uint8_t ubInitCompleted = 0;
    sSoftTimer_t *pTimer;

    if (ppT == NULL) {
        return 0;   /* invalid pointer */
    }

    if (1 != ubInitCompleted) {
        ubInitCompleted = 1;
        Timer_Init();
    }

    /* Free existing timer if already assigned */
    if (*ppT != NULL) {
        Timer_Delete(*ppT);
    }

    pTimer = (sSoftTimer_t*)malloc(sizeof(sSoftTimer_t));
    *ppT   = pTimer;

    if (pTimer == NULL) {
        PRINTF("ERROR: mem creation\r\n");
        return 0;   /* failure */
    }

    switch (eUnit) {
        case TIMER_SEC:
            pTimer->ulDurationUs = ulDuration * 1000000UL;
            break;
        case TIMER_MILLI_SEC:
            pTimer->ulDurationUs = ulDuration * 1000UL;
            break;
        case TIMER_MICRO_SEC:
            pTimer->ulDurationUs = ulDuration;
            break;
        default:
            free(pTimer);
            *ppT = NULL;
            return 0; /* invalid unit */
    }

    Timer_Start(pTimer);
    return 1;   /* success */
}


void Timer_Delete(void *pT)
{
	if(pT != NULL)
	{
		free(pT);
		pT = NULL;
	}
}

/**
 * @brief Start a software timer.
 *
 * Initializes a software timer instance with the specified duration.
 * Timer is marked as active and starts counting from the current PIT time.
 *
 * @param[in,out] pT Pointer to software timer object.
 * @param[in] ulDurationUs Timer duration in microseconds.
 */
uint8_t Timer_Start(void *pT)
{
    sSoftTimer_t *pTimer = (sSoftTimer_t*)pT;
    if (pTimer == NULL) {
        return 0;
    }

    pTimer->ulStartTimeUs = Timer_GetTimeUs();
    pTimer->ubExpired     = 0;
    return 1;
}


/**
 * @brief Check if a software timer has expired.
 *
 * Compares the current PIT time with the timer’s start time and duration.
 * Automatically deactivates the timer once expired (one-shot).
 *
 * @param[in,out] pT Pointer to software timer object.
 *
 * @return uint8_t
 *         - 1 (expired) if the timer has elapsed,
 *         - 0 (not expired or inactive) otherwise.
 */
uint8_t Timer_IsExpired(void *pT)
{
    sSoftTimer_t *pTimer = (sSoftTimer_t*)pT;

    if (pTimer == NULL) {
        return 0;
    }

    if (pTimer->ubExpired) {
        return 1;
    }

    uint32_t ulNow = Timer_GetTimeUs();
    uint32_t ulElapsed = ulNow - pTimer->ulStartTimeUs;  /* safe with wraparound */

    if (ulElapsed >= pTimer->ulDurationUs) {
        pTimer->ubExpired = 1;
        return 1;
    }

    return 0;
}
