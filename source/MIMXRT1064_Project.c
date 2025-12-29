/**
 * @file    main.c
 * @brief   Entry point for Ethernet communication stack using LwIP on i.MX RT1064.
 *
 *          Initializes board hardware, network interface, and protocol modules
 *          including TCP, UDP, and ICMP. Handles periodic tasks such as TCP
 *          message sending and input polling.
 *
 *  (C) Copyright Centum T&S Group 2025. All rights reserved.
 *  This computer program may not be used, copied, distributed, translated, transmitted or assigned
 *  without the prior written authorization of Centum T&S Group.
 */

/* ---------------- LWIP Core ---------------- */
#include "lwip/opt.h"
#include "lwip/init.h"
#include "lwip/timeouts.h"
#include "lwip/tcp.h"
#include "lwip/udp.h"
#include "lwip/dhcp.h"
#include "ping.h"

#if LWIP_IPV4 && LWIP_RAW

/* ---------------- Standard C ---------------- */
#include <string.h>
#include <stdio.h>
#include<stdlib.h>

/* ---------------- Board / Hardware ---------------- */
#include "board.h"
#include "app.h"
#include "fsl_phy.h"


/* ---------------- Network Interface ---------------- */
#include "netif/ethernet.h"
#include "ethernetif.h"

/* ---------------- HAL: Ethernet & Protocols ---------------- */
#include "HAL/EthernetInterface/Ethernet.h"
#include "HAL/EthernetInterface/protocols/tcp.h"
#include "HAL/EthernetInterface/protocols/udp.h"
#include "HAL/EthernetInterface/protocols/icmp.h"
#include "HAL/EthernetInterface/protocols/dhcp.h"
#include "HAL/EthernetInterface/protocols/igmp.h"
#include "HAL/EthernetInterface/protocols/TftpServer.h"
#include "HAL/EthernetInterface/protocols/TftpClient.h"

/* ---------------- HAL: Test Modules ---------------- */
#include "HAL/EthernetInterface/Test/tcp_test.h"
#include "HAL/EthernetInterface/Test/udp_test.h"
#include "HAL/EthernetInterface/Test/igmp_test.h"
#include "HAL/EthernetInterface/Test/tftp_test.h"
#include "HAL/LEDDriverInterface/LEDDriverTest.h"

/* ---------------- HAL: Timer ---------------- */
#include "HAL/TimerModule/timer.h"
#include "HAL/RTC/RTC_Driver.h"

/* ---------------- HAL: LEDDriver ---------------- */
#include "HAL/LEDDriverInterface/LEDDriver.h"
#include "peripherals.h"

/* ---------------- Middleware ---------------- */
#include "Middleware/LogManager/LogManager.h"
#include "Middleware/MessageLayerParser/MessageProtocolParser.h"
#include "Middleware/MessageLayerParser/ReceivingMessageQueue.h"
#include "Middleware/MessageLayerParser/MessageData.h"
#include "Middleware/SessionManager/SessionManager.h"
#include "Middleware/FrameBufferManager/FrameBufferManager.h"

/* ---------------- Application ---------------- */
#include "application/MessageHandler/ProcessCommand.h"
#include "application/MessageHandler/InitializationCommand/InitializationRequest.h"
#include "application/MessageHandler/InitializationCommand/InitializationResponce.h"
#include "application/MessageHandler/MutualControlCommand/MutualControlRequest.h"
#include "application/MessageHandler/MutualControlCommand/MutualControlResponse.h"


#ifndef configMAC_ADDR
#include "fsl_silicon_id.h"
#endif

#ifndef EXAMPLE_NETIF_INIT_FN
#define EXAMPLE_NETIF_INIT_FN ethernetif0_init
#endif


/* ---------------- LVGL ---------------- */
#include "../lvgl/lvgl.h"
#include "../source/application/DisplayController/lv_conf.h"
#include "application/DisplayController/lvgl_support.h"
#include "../lvgl/src/Image/Image.h"



/* ---------------- HARFBUZZ & FREETYPE ---------------- */
//#include "lv_font_hb_freetype.h"
#include "lv_hb_canvas_label.h"

/**
 * @brief Initializes all application-level modules and resets EMP state.
 *
 * This function should be called once at device startup (after hardware
 * and network stack initialization) or whenever a full protocol reset
 * is required.
 */

void Application_Init(void)
{
    /* Reset session manager state (session ID, timers, transaction counters) */
    SessionManager_Init();

    /* Reset the UDP receiving message queue */
    ReceivingMessageQueue_Init();

    /* Reset EMP message parser state */
    MessageProtocolParser_Init();

    /* Reset cached message layer data */
    MessageData_Init();

    /* Reset Initialization Request data */
    InitializationRequest_Reset();

    /* Reset Initialization Response data */
    InitializationResponce_Reset();

    /* Reset Initialization Request data */
    MutualControlRequest_Reset();

    /* Reset Initialization Response data */
    MutualControlResponse_Reset();

    COSLOG_INFO("Application_Init: All protocol modules reset.\r\n");
}


void SysTick_Handler(void)
{
    time_isr();
}


int main(void)
{
    BOARD_InitHardware();

    BOARD_InitBootPeripherals();

    Application_Init();

    lv_port_disp_init();

    LEDDriver_Init();

    FBM_Init(ROWS_PER_PANEL, COLS_PER_PANEL, DOUBLE_SIDED_DISPLAY, LED_TYPE, NUM_PANELS);

    LEDDriver_ConfigurePanel(ROWS_PER_PANEL, COLS_PER_PANEL, DOUBLE_SIDED_DISPLAY, LED_TYPE, NUM_PANELS, ROW_ADDR_BITS);

//    font_display_init();
//    lv_obj_t *label = lv_label_create(lv_scr_act());
//    hb_label_set_text_shaped(label, "Vishal");

    lv_obj_t * scr = lv_scr_act();

   /* Debug label so we know LVGL works */
//   lv_obj_t * label = lv_label_create(scr);
//   lv_label_set_text(label, "TEST LABEL"); (*changed)
//   lv_obj_set_style_text_color(label, lv_color_hex(0xFF0000), 0);
//   lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 10);
//   lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 0);

   /* HarfBuzz + FreeType text */
//   lv_hb_label_create(scr, "ശുഭ മധ്യാഹ്നം",      "fonts/Nirmala.ttc", 32, 20,  60);
//   lv_hb_label_create(scr, "नमस्ते दुनिया", "fonts/Nirmala.ttc", 32, 20, 120);
//   lv_hb_label_create(scr, "ಶುಭ ಮಧ್ಯಾನ", "fonts/Nirmala.ttc", 32, 20, 180);
   //lv_hb_label_create(scr, "مرحبا بالعالم", "fonts/Nirmala.ttc", 32, 20, 180);
   lv_hb_label_create(scr, "ഭ",   "fonts/MTCORSVA.ttf", 16, 0, 0); // 32, 20, 240 (*changed)

   lv_obj_invalidate(scr);

    while (1)
    {
        lv_tick_inc(1);
        lv_timer_handler();
        LEDDriver_DisplayOnLED();
    }
}

#endif
