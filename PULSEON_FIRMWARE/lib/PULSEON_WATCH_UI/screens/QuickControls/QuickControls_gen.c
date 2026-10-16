/**
 * @file QuickControls_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "QuickControls_gen.h"
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

lv_obj_t * QuickControls_create(void)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if PULSEON_WATCH_UI_CHECK_COMPILE_TARGET(PULSEON_WATCH_UI_TARGET_ALL)
    if (PULSEON_WATCH_UI_check_target(PULSEON_WATCH_UI_TARGET_ALL)) {
        lv_obj_t * lv_obj_0 = lv_obj_create(NULL);
        lv_obj_set_name_static(lv_obj_0, "QuickControls_#");
        lv_obj_set_width(lv_obj_0, 240);
        lv_obj_set_height(lv_obj_0, 320);
        lv_obj_set_style_bg_color(lv_obj_0, COLOR_DARK_BG, 0);

        lv_obj_t * lv_label_0 = lv_label_create(lv_obj_0);
        lv_obj_set_x(lv_label_0, 9);
        lv_obj_set_y(lv_label_0, 13);
        lv_label_set_text(lv_label_0, "QUICK CONTROLS");
        lv_obj_set_style_text_color(lv_label_0, COLOR_DARK_TEXT, 0);
        lv_obj_set_style_text_font(lv_label_0, font_h4, 0);

        lv_obj_t * lv_obj_1 = lv_obj_create(lv_obj_0);
        lv_obj_set_x(lv_obj_1, 9);
        lv_obj_set_y(lv_obj_1, 69);
        lv_obj_set_width(lv_obj_1, 69);
        lv_obj_set_height(lv_obj_1, 83);
        lv_obj_set_style_bg_color(lv_obj_1, COLOR_DARK_PANEL, 0);
        lv_obj_set_style_radius(lv_obj_1, RADIUS_DEFAULT, 0);
        lv_obj_t * lv_label_1 = lv_label_create(lv_obj_1);
        lv_obj_set_x(lv_label_1, 0);
        lv_obj_set_y(lv_label_1, 16);
        lv_obj_set_width(lv_label_1, 69);
        lv_label_set_text(lv_label_1, "BT");
        lv_obj_set_style_text_color(lv_label_1, COLOR_ACCENT, 0);
        lv_obj_set_style_text_font(lv_label_1, font_h4, 0);
        lv_obj_set_style_text_align(lv_label_1, LV_TEXT_ALIGN_CENTER, 0);

        lv_obj_t * lv_label_2 = lv_label_create(lv_obj_1);
        lv_obj_set_x(lv_label_2, 0);
        lv_obj_set_y(lv_label_2, 51);
        lv_obj_set_width(lv_label_2, 69);
        lv_label_set_text(lv_label_2, "ON");
        lv_obj_set_style_text_color(lv_label_2, COLOR_DARK_TEXT, 0);
        lv_obj_set_style_text_font(lv_label_2, font_body, 0);
        lv_obj_set_style_text_align(lv_label_2, LV_TEXT_ALIGN_CENTER, 0);

        lv_obj_t * lv_obj_2 = lv_obj_create(lv_obj_0);
        lv_obj_set_x(lv_obj_2, 86);
        lv_obj_set_y(lv_obj_2, 69);
        lv_obj_set_width(lv_obj_2, 69);
        lv_obj_set_height(lv_obj_2, 83);
        lv_obj_set_style_bg_color(lv_obj_2, COLOR_DARK_PANEL, 0);
        lv_obj_set_style_radius(lv_obj_2, RADIUS_DEFAULT, 0);
        lv_obj_t * lv_label_3 = lv_label_create(lv_obj_2);
        lv_obj_set_x(lv_label_3, 0);
        lv_obj_set_y(lv_label_3, 16);
        lv_obj_set_width(lv_label_3, 69);
        lv_label_set_text(lv_label_3, "WIFI");
        lv_obj_set_style_text_color(lv_label_3, COLOR_ACCENT, 0);
        lv_obj_set_style_text_font(lv_label_3, font_h4, 0);
        lv_obj_set_style_text_align(lv_label_3, LV_TEXT_ALIGN_CENTER, 0);

        lv_obj_t * lv_label_4 = lv_label_create(lv_obj_2);
        lv_obj_set_x(lv_label_4, 0);
        lv_obj_set_y(lv_label_4, 51);
        lv_obj_set_width(lv_label_4, 69);
        lv_label_set_text(lv_label_4, "ON");
        lv_obj_set_style_text_color(lv_label_4, COLOR_DARK_TEXT, 0);
        lv_obj_set_style_text_font(lv_label_4, font_body, 0);
        lv_obj_set_style_text_align(lv_label_4, LV_TEXT_ALIGN_CENTER, 0);

        lv_obj_t * lv_obj_3 = lv_obj_create(lv_obj_0);
        lv_obj_set_x(lv_obj_3, 162);
        lv_obj_set_y(lv_obj_3, 69);
        lv_obj_set_width(lv_obj_3, 69);
        lv_obj_set_height(lv_obj_3, 83);
        lv_obj_set_style_bg_color(lv_obj_3, COLOR_DARK_PANEL, 0);
        lv_obj_set_style_radius(lv_obj_3, RADIUS_DEFAULT, 0);
        lv_obj_t * lv_label_5 = lv_label_create(lv_obj_3);
        lv_obj_set_x(lv_label_5, 0);
        lv_obj_set_y(lv_label_5, 16);
        lv_obj_set_width(lv_label_5, 69);
        lv_label_set_text(lv_label_5, "SOUND");
        lv_obj_set_style_text_color(lv_label_5, COLOR_ACCENT, 0);
        lv_obj_set_style_text_font(lv_label_5, font_h4, 0);
        lv_obj_set_style_text_align(lv_label_5, LV_TEXT_ALIGN_CENTER, 0);

        lv_obj_t * lv_label_6 = lv_label_create(lv_obj_3);
        lv_obj_set_x(lv_label_6, 0);
        lv_obj_set_y(lv_label_6, 51);
        lv_obj_set_width(lv_label_6, 69);
        lv_label_set_text(lv_label_6, "ON");
        lv_obj_set_style_text_color(lv_label_6, COLOR_DARK_TEXT, 0);
        lv_obj_set_style_text_font(lv_label_6, font_body, 0);
        lv_obj_set_style_text_align(lv_label_6, LV_TEXT_ALIGN_CENTER, 0);

        lv_obj_t * lv_label_7 = lv_label_create(lv_obj_0);
        lv_obj_set_x(lv_label_7, 9);
        lv_obj_set_y(lv_label_7, 197);
        lv_label_set_text(lv_label_7, "BRIGHTNESS");
        lv_obj_set_style_text_color(lv_label_7, COLOR_DARK_TEXT, 0);
        lv_obj_set_style_text_font(lv_label_7, font_body, 0);

        lv_obj_t * lv_label_8 = lv_label_create(lv_obj_0);
        lv_obj_set_x(lv_label_8, 184);
        lv_obj_set_y(lv_label_8, 195);
        lv_label_set_text(lv_label_8, "80%");
        lv_obj_set_style_text_color(lv_label_8, COLOR_ACCENT, 0);
        lv_obj_set_style_text_font(lv_label_8, font_h5, 0);

        lv_obj_t * lv_label_9 = lv_label_create(lv_obj_0);
        lv_obj_set_x(lv_label_9, 9);
        lv_obj_set_y(lv_label_9, 256);
        lv_label_set_text(lv_label_9, "BATTERY");
        lv_obj_set_style_text_color(lv_label_9, COLOR_DARK_TEXT, 0);
        lv_obj_set_style_text_font(lv_label_9, font_body, 0);

        lv_obj_t * lv_label_10 = lv_label_create(lv_obj_0);
        lv_obj_set_x(lv_label_10, 184);
        lv_obj_set_y(lv_label_10, 253);
        lv_label_set_text(lv_label_10, "86%");
        lv_obj_set_style_text_color(lv_label_10, COLOR_ACCENT, 0);
        lv_obj_set_style_text_font(lv_label_10, font_h5, 0);

        the_root = lv_obj_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/
