#ifndef HB_SHAPER_H
#define HB_SHAPER_H

#include <stdint.h>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "harfbuzz/include/hb.h"
#include "harfbuzz/include/hb-ft.h"

typedef struct {
    uint32_t glyph_id;
    int32_t x_offset;
    int32_t y_offset;
    int32_t x_advance;
} hb_glyph_t;

typedef struct {
    hb_glyph_t *glyphs;
    int count;
    FT_Face face;
} hb_shape_result_t;


// Use to adjust text position on display

//typedef struct {
//    hb_glyph_t *glyphs;
//    int count;
//    FT_Face face;
//
//    int ascender;
//    int descender;
//    int line_height;
//} hb_shape_result_t;

hb_shape_result_t hb_shape_text(const char *text);
void hb_shape_free(hb_shape_result_t *res);

#endif
