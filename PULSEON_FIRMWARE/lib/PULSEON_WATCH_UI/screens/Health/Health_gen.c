/**
 * @file Health_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "Health_gen.h"
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

lv_obj_t * Health_create(void)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if PULSEON_WATCH_UI_CHECK_COMPILE_TARGET(PULSEON_WATCH_UI_TARGET_ALL)
    if (PULSEON_WATCH_UI_check_target(PULSEON_WATCH_UI_TARGET_ALL)) {
        lv_obj_t * lv_obj_0 = lv_obj_create(NULL);
        lv_obj_set_name_static(lv_obj_0, "Health_#");
        lv_obj_set_width(lv_obj_0, 240);
        lv_obj_set_height(lv_obj_0, 320);
        lv_obj_set_style_bg_color(lv_obj_0, COLOR_DARK_BG, 0);

        lv_obj_t * lv_label_0 = lv_label_create(lv_obj_0);
        lv_obj_set_x(lv_label_0, 9);
        lv_obj_set_y(lv_label_0, 13);
        lv_label_set_text(lv_label_0, "HEALTH");
        lv_obj_set_style_text_color(lv_label_0, COLOR_DARK_TEXT, 0);
        lv_obj_set_style_text_font(lv_label_0, font_h4, 0);

        lv_obj_t * lv_obj_1 = lv_obj_create(lv_obj_0);
        lv_obj_set_x(lv_obj_1, 9);
        lv_obj_set_y(lv_obj_1, 69);
        lv_obj_set_width(lv_obj_1, 108);
        lv_obj_set_height(lv_obj_1, 91);
        lv_obj_set_style_bg_color(lv_obj_1, COLOR_DARK_PANEL, 0);
        lv_obj_set_style_radius(lv_obj_1, RADIUS_DEFAULT, 0);
        lv_obj_t * lv_label_1 = lv_label_create(lv_obj_1);
        lv_obj_set_x(lv_label_1, 8);
        lv_obj_set_y(lv_label_1, 11);
        lv_label_set_text(lv_label_1, "HEART RATE");
        lv_obj_set_style_text_color(lv_label_1, COLOR_DARK_TEXT, 0);
        lv_obj_set_style_text_font(lv_label_1, font_body, 0);

        lv_obj_t * lv_label_2 = lv_label_create(lv_obj_1);
        lv_obj_set_x(lv_label_2, 8);
        lv_obj_set_y(lv_label_2, 43);
        lv_label_set_text(lv_label_2, "78 BPM");
        lv_obj_set_style_text_color(lv_label_2, COLOR_DANGER, 0);
        lv_obj_set_style_text_font(lv_label_2, font_h4, 0);

        lv_obj_t * lv_obj_2 = lv_obj_create(lv_obj_0);
        lv_obj_set_x(lv_obj_2, 123);
        lv_obj_set_y(lv_obj_2, 69);
        lv_obj_set_width(lv_obj_2, 108);
        lv_obj_set_height(lv_obj_2, 91);
        lv_obj_set_style_bg_color(lv_obj_2, COLOR_DARK_PANEL, 0);
        lv_obj_set_style_radius(lv_obj_2, RADIUS_DEFAULT, 0);
        lv_obj_t * lv_label_3 = lv_label_create(lv_obj_2);
        lv_obj_set_x(lv_label_3, 8);
        lv_obj_set_y(lv_label_3, 11);
        lv_label_set_text(lv_label_3, "STEPS");
        lv_obj_set_style_text_color(lv_label_3, COLOR_DARK_TEXT, 0);
        lv_obj_set_style_text_font(lv_label_3, font_body, 0);

        lv_obj_t * lv_label_4 = lv_label_create(lv_obj_2);
        lv_obj_set_x(lv_label_4, 8);
        lv_obj_set_y(lv_label_4, 43);
        lv_label_set_text(lv_label_4, "6,842");
        lv_obj_set_style_text_color(lv_label_4, COLOR_ACCENT, 0);
        lv_obj_set_style_text_font(lv_label_4, font_h4, 0);

        lv_obj_t * lv_label_5 = lv_label_create(lv_obj_0);
        lv_obj_set_x(lv_label_5, 9);
        lv_obj_set_y(lv_label_5, 193);
        lv_label_set_text(lv_label_5, "ACTIVITY");
        lv_obj_set_style_text_color(lv_label_5, COLOR_DARK_TEXT, 0);
        lv_obj_set_style_text_font(lv_label_5, font_body, 0);

        lv_obj_t * lv_label_6 = lv_label_create(lv_obj_0);
        lv_obj_set_x(lv_label_6, 184);
        lv_obj_set_y(lv_label_6, 189);
        lv_label_set_text(lv_label_6, "72%");
        lv_obj_set_style_text_color(lv_label_6, COLOR_ACCENT, 0);
        lv_obj_set_style_text_font(lv_label_6, font_h4, 0);

        lv_obj_t * lv_label_7 = lv_label_create(lv_obj_0);
        lv_obj_set_x(lv_label_7, 9);
        lv_obj_set_y(lv_label_7, 253);
        lv_label_set_text(lv_label_7, "CALORIES");
        lv_obj_set_style_text_color(lv_label_7, COLOR_DARK_TEXT, 0);
        lv_obj_set_style_text_font(lv_label_7, font_body, 0);

        lv_obj_t * lv_label_8 = lv_label_create(lv_obj_0);
        lv_obj_set_x(lv_label_8, 184);
        lv_obj_set_y(lv_label_8, 249);
        lv_label_set_text(lv_label_8, "486 kcal");
        lv_obj_set_style_text_color(lv_label_8, COLOR_ACCENT, 0);
        lv_obj_set_style_text_font(lv_label_8, font_h5, 0);

        the_root = lv_obj_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/
