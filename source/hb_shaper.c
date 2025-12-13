#include "hb_shaper.h"
#include <stdlib.h>
#include <string.h>
#include "Font_ttf.h"

hb_shape_result_t hb_shape_text(const char *text)
{
    hb_shape_result_t result = {0};

    FT_Library ft;
    if (FT_Init_FreeType(&ft)) {
        printf("FreeType init failed\n");
        return result;
    }

    FT_Face face = NULL;

    /* ✅ VERY IMPORTANT: TTC files often need index 0,1,2
       We try all until one works */
    if (FT_New_Memory_Face(ft, AnjaliOldLipi_Regular_ttf, AnjaliOldLipi_Regular_ttf_len, 0, &face)) {

        printf("FreeType ERROR: Could not load Nirmala.ttc with any face index!\n");
        FT_Done_FreeType(ft);
        return result;
    }

    FT_Set_Pixel_Sizes(face, 0, 16); // 32 (*changed)

    hb_font_t *hb_font = hb_ft_font_create(face, NULL);
    if (!hb_font) {
        printf("HB ERROR: hb_ft_font_create failed\n");
        FT_Done_Face(face);
        FT_Done_FreeType(ft);
        return result;
    }

    hb_buffer_t *buf = hb_buffer_create();
    hb_buffer_add_utf8(buf, text, -1, 0, -1);
    hb_buffer_guess_segment_properties(buf);

    hb_shape(hb_font, buf, NULL, 0);

    unsigned int count;
    hb_glyph_info_t *info = hb_buffer_get_glyph_infos(buf, &count);
    hb_glyph_position_t *pos = hb_buffer_get_glyph_positions(buf, &count);

    if (count == 0) {
        printf("HB ERROR: No glyphs shaped!\n");
        hb_buffer_destroy(buf);
        hb_font_destroy(hb_font);
        FT_Done_Face(face);
        FT_Done_FreeType(ft);
        return result;
    }

    result.count = count;
    result.face = face;
    result.glyphs = malloc(sizeof(hb_glyph_t) * count);

    for (unsigned int i = 0; i < count; i++) {
        result.glyphs[i].glyph_id = info[i].codepoint;
        result.glyphs[i].x_advance = pos[i].x_advance >> 6;
        // result.glyphs[i].y_advance = pos[i].y_advance >> 6;
        result.glyphs[i].x_offset  = pos[i].x_offset >> 6;
        result.glyphs[i].y_offset  = pos[i].y_offset >> 6;
    }

    hb_buffer_destroy(buf);
    hb_font_destroy(hb_font);

    return result;
}

void hb_shape_free(hb_shape_result_t *res)
{
    if (!res || !res->face) return;

    free(res->glyphs);
    FT_Done_Face(res->face);
}

