#ifndef LV_HB_CANVAS_LABEL_H
#define LV_HB_CANVAS_LABEL_H

#include "../lvgl/lvgl.h"

lv_obj_t * lv_hb_label_create(lv_obj_t * parent,
                              const char * text,
                              const char * font_path,
                              int font_px,
                              int x,
                              int y);

lv_obj_t * lv_hb_label_create_marquee(lv_obj_t * parent,
                              const char * text,
                              const char * font_path,
                              int font_px,
                              int x,
                              int y);
#endif
