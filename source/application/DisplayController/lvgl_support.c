#include "../../lvgl/lvgl.h"
#include "../../HAL/LEDDriverInterface/LEDDriver.h"
#include "../../Middleware/FrameBufferManager/FrameBufferManager.h"
#include "board.h"
#include <stdio.h>
#include <string.h>

/* ---------------- DISPLAY PARAMETERS ---------------- */
#define NUM_PANELS      2
#define WIDTH           64     /* per panel */
#define HEIGHT          16
#define TOTAL_WIDTH     (WIDTH * NUM_PANELS)

#define LVGL_BUF_SIZE   (TOTAL_WIDTH * 1 * HEIGHT)

/* Allocate LVGL buffers (cached or non-cached is fine) */

static uint8_t buf1[LVGL_BUF_SIZE];
static uint8_t buf2[LVGL_BUF_SIZE];

static const uint8_t row_map[16] =
{
    0,1,2,3,4,5,6,7,
    8,9,10,11,12,13,14,15
};


static void flushDisplay(lv_display_t *disp, const lv_area_t *area, uint8_t *color_p)
{
    uint8_t **fb = FBM_GetReserveFrontBuffer();
    if (!fb)
    {
        lv_display_flush_ready(disp);
        return;
    }

    uint8_t *src = color_p + 8;

    for (int y = area->y1; y <= area->y2; y++)
    {
    	int phy_y = row_map[y];

    	uint8_t *dst_row = fb[phy_y];

        /* Clear entire row (128 pixels / 8 = 16 bytes) */
        memset(dst_row, 0, TOTAL_WIDTH / 8);

        for (int x = area->x1; x <= area->x2; x++)
        {
        	int bit_index_in_src  = x & 7;
			int byte_index_in_src = (x >> 3);
			int src_byte_offset   = (y - area->y1) * (TOTAL_WIDTH / 8) + byte_index_in_src;

			uint8_t src_byte = src[src_byte_offset];

			/* LVGL stores MSB-first: bit7→x0 */
			uint8_t pixel = (src_byte >> (7 - bit_index_in_src)) & 0x01;

			if (pixel)
			{
				int byte_in_dst = x >> 3;
				int bit_in_dst  = 7 - (x & 7);
				dst_row[byte_in_dst] |= (0 << bit_in_dst);
			}
			else
			{
				int byte_in_dst = x >> 3;
				int bit_in_dst  = 7 - (x & 7);
				dst_row[byte_in_dst] |= (1 << bit_in_dst);
			}
        }
    }

    /* LVGL done */
    lv_display_flush_ready(disp);

    /* Swap front/back buffer */
    FBM_SwapBuffers();

    /* Prepare output to driver */
    LEDDriver_PrepareDisplayBuffer(FBM_GetActiveFrontBuffer());
}


/* ----------------------------------------------------
 * DISPLAY INITIALIZATION
 * ----------------------------------------------------*/
void lv_port_disp_init(void)
{
    lv_init();

    lv_display_t *disp = lv_display_create(TOTAL_WIDTH, HEIGHT);

    lv_display_set_color_format(disp, LV_COLOR_FORMAT_I1);

    lv_display_set_buffers(
        disp,
        buf1,
        buf2,
        LVGL_BUF_SIZE,
        LV_DISPLAY_RENDER_MODE_DIRECT
    );

    lv_display_set_flush_cb(disp, flushDisplay);
}
