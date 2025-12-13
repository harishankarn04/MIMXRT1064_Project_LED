#include "lv_hb_canvas_label.h"
#include "hb_shaper.h"
#include <stdlib.h>
#include <string.h>

lv_obj_t * lv_hb_label_create(lv_obj_t * parent,
                              const char * text,
                              const char * font_path,
                              int font_px,
                              int x,
                              int y)
{
    (void)font_path;
    hb_shape_result_t shaped = hb_shape_text(text);

//    if(shaped.count == 0) {
//        printf("HB ERROR: No glyphs shaped!\n");
//        return NULL;
//    }
//
//    int pen_x = 0;
//    int pen_y = font_px;
//
//    int width = 0;
//    for(int i = 0; i < shaped.count; i++) {
//        width += shaped.glyphs[i].x_advance;
//    }
//
//    int height = font_px + 10;
//
//    printf("Canvas size: %d x %d\n", width, height);
//
//    lv_obj_t * canvas = lv_canvas_create(parent);
//    lv_obj_set_pos(canvas, x, y);
//    lv_obj_set_size(canvas, width, height);
//
//    lv_color_t * buf = malloc(width * height * 4);
//    memset(buf, 0, width * height * sizeof(lv_color_t));
//
//    lv_canvas_set_buffer(canvas, buf, width, height, LV_COLOR_FORMAT_ARGB8888);
////    lv_canvas_set_buffer(canvas, buf, width, height, LV_COLOR_FORMAT_I1);
//
//    FT_Face face = shaped.face;
//    FT_GlyphSlot g;
//    int px=0;
//    int py=0;
//
//    for(int i = 0; i < shaped.count; i++) {
//
//        FT_Load_Glyph(face, shaped.glyphs[i].glyph_id, FT_LOAD_RENDER);
//         g= face->glyph;
//
//        for(int row = 0; row < g->bitmap.rows; row++) {
//            for(int col = 0; col < g->bitmap.width; col++) {
//
//                  px = pen_x + g->bitmap_left + col;
//                  py = pen_y - g->bitmap_top + row;
//
//                if(px < 0 || py < 0 || px >= width || py >= height)
//                    continue;
//
//                uint8_t a = g->bitmap.buffer[row * g->bitmap.pitch + col];
//                if(a > 0) {
//                    lv_canvas_set_px(canvas, px, py, lv_color_black(), LV_OPA_COVER);
//                }
//            }
//        }
//
//        pen_x += shaped.glyphs[i].x_advance;
//    }
//
//    hb_shape_free(&shaped);
//    return canvas;
}

//lv_obj_t * lv_hb_label_create_marquee(lv_obj_t * parent,
//                              const char * text,
//                              const char * font_path,
//                              int font_px,
//                              int x,
//                              int y)
//{
//    (void)font_path;
//    hb_shape_result_t shaped = hb_shape_text(text);
//
//    if(shaped.count == 0) {
//        printf("HB ERROR: No glyphs shaped!\n");
//        return NULL;
//    }
//
//    int pen_x = 0;
//    int pen_y = font_px;
//
//    int width = 0;
//    for(int i = 0; i < shaped.count; i++) {
//        width += shaped.glyphs[i].x_advance;
//    }
//
//    int height = font_px + 10;
//
//    printf("Canvas size: %d x %d\n", width, height);
//
//    lv_obj_t * canvas = lv_canvas_create(parent);
//    lv_obj_set_pos(canvas, x, y);
//    lv_obj_set_size(canvas, width, height);
//
//    lv_color_t * buf = malloc(width * height * 4);
//    memset(buf, 0, width * height * sizeof(lv_color_t));
//
//    lv_canvas_set_buffer(canvas, buf, width, height, LV_COLOR_FORMAT_ARGB8888);
////    lv_canvas_set_buffer(canvas, buf, width, height, LV_COLOR_FORMAT_I1);
//
//    FT_Face face = shaped.face;
//
//    for(int i = 0; i < shaped.count; i++) {
//
//        FT_Load_Glyph(face, shaped.glyphs[i].glyph_id, FT_LOAD_RENDER);
//        FT_GlyphSlot g = face->glyph;
//
//        for(int row = 0; row < g->bitmap.rows; row++) {
//            for(int col = 0; col < g->bitmap.width; col++) {
//
//                int px = pen_x + g->bitmap_left + col;
//                int py = pen_y - g->bitmap_top + row;
//
//                if(px < 0 || py < 0 || px >= width || py >= height)
//                    continue;
//
//                uint8_t a = g->bitmap.buffer[row * g->bitmap.pitch + col];
//                if(a > 0) {
//                    lv_canvas_set_px(canvas, px, py, lv_color_black(), LV_OPA_COVER);
//                }
//            }
//        }
//
//        pen_x += shaped.glyphs[i].x_advance;
//    }
//
//    hb_shape_free(&shaped);
//    return canvas;
//}
