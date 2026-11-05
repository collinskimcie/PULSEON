/**
 * @file HomeEmber_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "HomeEmber_gen.h"
#include "../../PULSEON_WATCH_UI.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/***********************
 *  STATIC VARIABLES
 **********************/

/***********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

lv_obj_t * HomeEmber_create(void)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if PULSEON_WATCH_UI_CHECK_COMPILE_TARGET(PULSEON_WATCH_UI_TARGET_ALL)
    if (PULSEON_WATCH_UI_check_target(PULSEON_WATCH_UI_TARGET_ALL)) {
        lv_obj_t * lv_obj_0 = lv_obj_create(NULL);
        lv_obj_set_name_static(lv_obj_0, "HomeEmber_#");
        lv_obj_set_width(lv_obj_0, 240);
        lv_obj_set_height(lv_obj_0, 320);
        lv_obj_set_style_bg_color(lv_obj_0, lv_color_hex(0x000000), 0);
        lv_obj_set_style_pad_all(lv_obj_0, 0, 0);
        lv_obj_set_style_border_width(lv_obj_0, 0, 0);

        lv_obj_t * eye_l = lv_obj_create(lv_obj_0);
        lv_obj_set_name(eye_l, "eye_l");
        lv_obj_set_x(eye_l, 50);
        lv_obj_set_y(eye_l, 114);
        lv_obj_set_width(eye_l, 56);
        lv_obj_set_height(eye_l, 56);
        lv_obj_set_style_bg_color(eye_l, lv_color_hex(0xE01616), 0);
        lv_obj_set_style_radius(eye_l, 28, 0);
        lv_obj_set_style_border_width(eye_l, 0, 0);
        lv_obj_set_style_pad_all(eye_l, 0, 0);

        lv_obj_t * white_l = lv_obj_create(lv_obj_0);
        lv_obj_set_name(white_l, "white_l");
        lv_obj_set_x(white_l, 59);
        lv_obj_set_y(white_l, 123);
        lv_obj_set_width(white_l, 38);
        lv_obj_set_height(white_l, 38);
        lv_obj_set_style_bg_color(white_l, lv_color_hex(0xF2F2F2), 0);
        lv_obj_set_style_radius(white_l, 19, 0);
        lv_obj_set_style_border_width(white_l, 0, 0);
        lv_obj_set_style_pad_all(white_l, 0, 0);

        lv_obj_t * pupil_l = lv_obj_create(lv_obj_0);
        lv_obj_set_name(pupil_l, "pupil_l");
        lv_obj_set_x(pupil_l, 73);
        lv_obj_set_y(pupil_l, 138);
        lv_obj_set_width(pupil_l, 14);
        lv_obj_set_height(pupil_l, 14);
        lv_obj_set_style_bg_color(pupil_l, lv_color_hex(0x111111), 0);
        lv_obj_set_style_radius(pupil_l, 7, 0);
        lv_obj_set_style_border_width(pupil_l, 0, 0);
        lv_obj_set_style_pad_all(pupil_l, 0, 0);

        lv_obj_t * cover_l = lv_obj_create(lv_obj_0);
        lv_obj_set_name(cover_l, "cover_l");
        lv_obj_set_x(cover_l, 50);
        lv_obj_set_y(cover_l, 114);
        lv_obj_set_width(cover_l, 56);
        lv_obj_set_height(cover_l, 0);
        lv_obj_set_style_bg_color(cover_l, lv_color_hex(0x000000), 0);
        lv_obj_set_style_radius(cover_l, 0, 0);
        lv_obj_set_style_border_width(cover_l, 0, 0);
        lv_obj_set_style_pad_all(cover_l, 0, 0);

        lv_obj_t * lid_l = lv_obj_create(lv_obj_0);
        lv_obj_set_name(lid_l, "lid_l");
        lv_obj_set_x(lid_l, 36);
        lv_obj_set_y(lid_l, 90);
        lv_obj_set_width(lid_l, 84);
        lv_obj_set_height(lid_l, 44);
        lv_obj_set_style_bg_color(lid_l, lv_color_hex(0x000000), 0);
        lv_obj_set_style_radius(lid_l, 0, 0);
        lv_obj_set_style_border_width(lid_l, 0, 0);
        lv_obj_set_style_pad_all(lid_l, 0, 0);
        lv_obj_set_style_transform_rotation(lid_l, 180, 0);
        lv_obj_set_style_transform_pivot_x(lid_l, 42, 0);
        lv_obj_set_style_transform_pivot_y(lid_l, 22, 0);

        lv_obj_t * eye_r = lv_obj_create(lv_obj_0);
        lv_obj_set_name(eye_r, "eye_r");
        lv_obj_set_x(eye_r, 134);
        lv_obj_set_y(eye_r, 114);
        lv_obj_set_width(eye_r, 56);
        lv_obj_set_height(eye_r, 56);
        lv_obj_set_style_bg_color(eye_r, lv_color_hex(0xE01616), 0);
        lv_obj_set_style_radius(eye_r, 28, 0);
        lv_obj_set_style_border_width(eye_r, 0, 0);
        lv_obj_set_style_pad_all(eye_r, 0, 0);

        lv_obj_t * white_r = lv_obj_create(lv_obj_0);
        lv_obj_set_name(white_r, "white_r");
        lv_obj_set_x(white_r, 143);
        lv_obj_set_y(white_r, 123);
        lv_obj_set_width(white_r, 38);
        lv_obj_set_height(white_r, 38);
        lv_obj_set_style_bg_color(white_r, lv_color_hex(0xF2F2F2), 0);
        lv_obj_set_style_radius(white_r, 19, 0);
        lv_obj_set_style_border_width(white_r, 0, 0);
        lv_obj_set_style_pad_all(white_r, 0, 0);

        lv_obj_t * pupil_r = lv_obj_create(lv_obj_0);
        lv_obj_set_name(pupil_r, "pupil_r");
        lv_obj_set_x(pupil_r, 153);
        lv_obj_set_y(pupil_r, 138);
        lv_obj_set_width(pupil_r, 14);
        lv_obj_set_height(pupil_r, 14);
        lv_obj_set_style_bg_color(pupil_r, lv_color_hex(0x111111), 0);
        lv_obj_set_style_radius(pupil_r, 7, 0);
        lv_obj_set_style_border_width(pupil_r, 0, 0);
        lv_obj_set_style_pad_all(pupil_r, 0, 0);

        lv_obj_t * cover_r = lv_obj_create(lv_obj_0);
        lv_obj_set_name(cover_r, "cover_r");
        lv_obj_set_x(cover_r, 134);
        lv_obj_set_y(cover_r, 114);
        lv_obj_set_width(cover_r, 56);
        lv_obj_set_height(cover_r, 0);
        lv_obj_set_style_bg_color(cover_r, lv_color_hex(0x000000), 0);
        lv_obj_set_style_radius(cover_r, 0, 0);
        lv_obj_set_style_border_width(cover_r, 0, 0);
        lv_obj_set_style_pad_all(cover_r, 0, 0);

        lv_obj_t * lid_r = lv_obj_create(lv_obj_0);
        lv_obj_set_name(lid_r, "lid_r");
        lv_obj_set_x(lid_r, 120);
        lv_obj_set_y(lid_r, 90);
        lv_obj_set_width(lid_r, 84);
        lv_obj_set_height(lid_r, 44);
        lv_obj_set_style_bg_color(lid_r, lv_color_hex(0x000000), 0);
        lv_obj_set_style_radius(lid_r, 0, 0);
        lv_obj_set_style_border_width(lid_r, 0, 0);
        lv_obj_set_style_pad_all(lid_r, 0, 0);
        lv_obj_set_style_transform_rotation(lid_r, -180, 0);
        lv_obj_set_style_transform_pivot_x(lid_r, 42, 0);
        lv_obj_set_style_transform_pivot_y(lid_r, 22, 0);

        lv_obj_t * mouth = lv_obj_create(lv_obj_0);
        lv_obj_set_name(mouth, "mouth");
        lv_obj_set_x(mouth, 106);
        lv_obj_set_y(mouth, 198);
        lv_obj_set_width(mouth, 29);
        lv_obj_set_height(mouth, 2);
        lv_obj_set_style_bg_color(mouth, lv_color_hex(0xD8D8D8), 0);
        lv_obj_set_style_radius(mouth, 1, 0);
        lv_obj_set_style_border_width(mouth, 0, 0);
        lv_obj_set_style_pad_all(mouth, 0, 0);
        lv_obj_set_style_transform_rotation(mouth, -121, 0);
        lv_obj_set_style_transform_pivot_x(mouth, 14, 0);
        lv_obj_set_style_transform_pivot_y(mouth, 1, 0);

        lv_obj_t * time = lv_label_create(lv_obj_0);
        lv_obj_set_name(time, "time");
        lv_obj_set_x(time, 0);
        lv_obj_set_y(time, 236);
        lv_obj_set_width(time, 240);
        lv_label_set_text(time, "09:41");
        lv_obj_set_style_text_color(time, lv_color_hex(0xE01616), 0);
        lv_obj_set_style_text_font(time, font_h1, 0);
        lv_obj_set_style_text_align(time, LV_TEXT_ALIGN_CENTER, 0);

        the_root = lv_obj_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

