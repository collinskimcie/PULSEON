/**
 * @file WatchHome_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "WatchHome_gen.h"
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

lv_obj_t * WatchHome_create(void)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if PULSEON_WATCH_UI_CHECK_COMPILE_TARGET(PULSEON_WATCH_UI_TARGET_ALL)
    if (PULSEON_WATCH_UI_check_target(PULSEON_WATCH_UI_TARGET_ALL)) {
        lv_obj_t * lv_obj_0 = lv_obj_create(NULL);
        lv_obj_set_name_static(lv_obj_0, "WatchHome_#");
        lv_obj_set_width(lv_obj_0, 240);
        lv_obj_set_height(lv_obj_0, 320);
        lv_obj_set_style_bg_color(lv_obj_0, COLOR_DARK_BG, 0);

        lv_obj_t * lv_label_0 = lv_label_create(lv_obj_0);
        lv_obj_set_x(lv_label_0, 9);
        lv_obj_set_y(lv_label_0, 11);
        lv_label_set_text(lv_label_0, "MON 07 OCT");
        lv_obj_set_style_text_color(lv_label_0, COLOR_DARK_TEXT, 0);
        lv_obj_set_style_text_font(lv_label_0, font_h5, 0);

        lv_obj_t * lv_label_1 = lv_label_create(lv_obj_0);
        lv_obj_set_x(lv_label_1, 173);
        lv_obj_set_y(lv_label_1, 11);
        lv_label_set_text(lv_label_1, "BT");
        lv_obj_set_style_text_color(lv_label_1, COLOR_ACCENT, 0);
        lv_obj_set_style_text_font(lv_label_1, font_h5, 0);

        lv_obj_t * lv_label_2 = lv_label_create(lv_obj_0);
        lv_obj_set_x(lv_label_2, 203);
        lv_obj_set_y(lv_label_2, 11);
        lv_label_set_text(lv_label_2, "86%");
        lv_obj_set_style_text_color(lv_label_2, COLOR_DARK_TEXT, 0);
        lv_obj_set_style_text_font(lv_label_2, font_h5, 0);

        lv_obj_t * lv_label_3 = lv_label_create(lv_obj_0);
        lv_obj_set_x(lv_label_3, 0);
        lv_obj_set_y(lv_label_3, 69);
        lv_obj_set_width(lv_label_3, 240);
        lv_obj_set_height(lv_label_3, 73);
        lv_label_set_text(lv_label_3, "12:48");
        lv_obj_set_style_text_color(lv_label_3, COLOR_DARK_TEXT, 0);
        lv_obj_set_style_text_font(lv_label_3, font_h1, 0);
        lv_obj_set_style_text_align(lv_label_3, LV_TEXT_ALIGN_CENTER, 0);

        lv_obj_t * lv_label_4 = lv_label_create(lv_obj_0);
        lv_obj_set_x(lv_label_4, 0);
        lv_obj_set_y(lv_label_4, 144);
        lv_obj_set_width(lv_label_4, 240);
        lv_obj_set_height(lv_label_4, 37);
        lv_label_set_text(lv_label_4, "PM");
        lv_obj_set_style_text_color(lv_label_4, COLOR_ACCENT, 0);
        lv_obj_set_style_text_font(lv_label_4, font_h5, 0);
        lv_obj_set_style_text_align(lv_label_4, LV_TEXT_ALIGN_CENTER, 0);

        lv_obj_t * lv_obj_1 = lv_obj_create(lv_obj_0);
        lv_obj_set_x(lv_obj_1, 9);
        lv_obj_set_y(lv_obj_1, 193);
        lv_obj_set_width(lv_obj_1, 108);
        lv_obj_set_height(lv_obj_1, 64);
        lv_obj_set_style_bg_color(lv_obj_1, COLOR_DARK_PANEL, 0);
        lv_obj_set_style_radius(lv_obj_1, RADIUS_DEFAULT, 0);
        lv_obj_t * lv_label_5 = lv_label_create(lv_obj_1);
        lv_obj_set_x(lv_label_5, 8);
        lv_obj_set_y(lv_label_5, 7);
        lv_label_set_text(lv_label_5, "HEART RATE");
        lv_obj_set_style_text_color(lv_label_5, COLOR_DARK_TEXT, 0);
        lv_obj_set_style_text_font(lv_label_5, font_body, 0);

        lv_obj_t * lv_label_6 = lv_label_create(lv_obj_1);
        lv_obj_set_x(lv_label_6, 8);
        lv_obj_set_y(lv_label_6, 29);
        lv_label_set_text(lv_label_6, "78 BPM");
        lv_obj_set_style_text_color(lv_label_6, COLOR_DANGER, 0);
        lv_obj_set_style_text_font(lv_label_6, font_h5, 0);

        lv_obj_t * lv_obj_2 = lv_obj_create(lv_obj_0);
        lv_obj_set_x(lv_obj_2, 123);
        lv_obj_set_y(lv_obj_2, 193);
        lv_obj_set_width(lv_obj_2, 108);
        lv_obj_set_height(lv_obj_2, 64);
        lv_obj_set_style_bg_color(lv_obj_2, COLOR_DARK_PANEL, 0);
        lv_obj_set_style_radius(lv_obj_2, RADIUS_DEFAULT, 0);
        lv_obj_t * lv_label_7 = lv_label_create(lv_obj_2);
        lv_obj_set_x(lv_label_7, 8);
        lv_obj_set_y(lv_label_7, 7);
        lv_label_set_text(lv_label_7, "WEATHER");
        lv_obj_set_style_text_color(lv_label_7, COLOR_DARK_TEXT, 0);
        lv_obj_set_style_text_font(lv_label_7, font_body, 0);

        lv_obj_t * lv_label_8 = lv_label_create(lv_obj_2);
        lv_obj_set_x(lv_label_8, 8);
        lv_obj_set_y(lv_label_8, 29);
        lv_label_set_text(lv_label_8, "24 C");
        lv_obj_set_style_text_color(lv_label_8, COLOR_ACCENT, 0);
        lv_obj_set_style_text_font(lv_label_8, font_h5, 0);

        lv_obj_t * lv_label_9 = lv_label_create(lv_obj_0);
        lv_obj_set_x(lv_label_9, 9);
        lv_obj_set_y(lv_label_9, 276);
        lv_label_set_text(lv_label_9, "STEPS");
        lv_obj_set_style_text_color(lv_label_9, COLOR_DARK_TEXT, 0);
        lv_obj_set_style_text_font(lv_label_9, font_body, 0);

        lv_obj_t * lv_label_10 = lv_label_create(lv_obj_0);
        lv_obj_set_x(lv_label_10, 59);
        lv_obj_set_y(lv_label_10, 272);
        lv_label_set_text(lv_label_10, "6,842");
        lv_obj_set_style_text_color(lv_label_10, COLOR_ACCENT, 0);
        lv_obj_set_style_text_font(lv_label_10, font_h5, 0);

        lv_obj_t * lv_label_11 = lv_label_create(lv_obj_0);
        lv_obj_set_x(lv_label_11, 131);
        lv_obj_set_y(lv_label_11, 276);
        lv_label_set_text(lv_label_11, "ACTIVITY");
        lv_obj_set_style_text_color(lv_label_11, COLOR_DARK_TEXT, 0);
        lv_obj_set_style_text_font(lv_label_11, font_body, 0);

        lv_obj_t * lv_label_12 = lv_label_create(lv_obj_0);
        lv_obj_set_x(lv_label_12, 184);
        lv_obj_set_y(lv_label_12, 272);
        lv_label_set_text(lv_label_12, "72%");
        lv_obj_set_style_text_color(lv_label_12, COLOR_ACCENT, 0);
        lv_obj_set_style_text_font(lv_label_12, font_h5, 0);

        the_root = lv_obj_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/
