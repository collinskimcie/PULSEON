/**
 * @file HomeAnalog_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "HomeAnalog_gen.h"
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

lv_obj_t * HomeAnalog_create(void)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if PULSEON_WATCH_UI_CHECK_COMPILE_TARGET(PULSEON_WATCH_UI_TARGET_ALL)
    if (PULSEON_WATCH_UI_check_target(PULSEON_WATCH_UI_TARGET_ALL)) {
        lv_obj_t * lv_obj_0 = lv_obj_create(NULL);
        lv_obj_set_name_static(lv_obj_0, "HomeAnalog_#");
        lv_obj_set_width(lv_obj_0, 240);
        lv_obj_set_height(lv_obj_0, 320);
        lv_obj_set_style_bg_color(lv_obj_0, lv_color_hex(0x12151C), 0);
        lv_obj_set_style_pad_all(lv_obj_0, 0, 0);
        lv_obj_set_style_border_width(lv_obj_0, 0, 0);

        lv_obj_t * tick0 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tick0, "tick0");
        lv_obj_set_x(tick0, 118);
        lv_obj_set_y(tick0, 20);
        lv_obj_set_width(tick0, 4);
        lv_obj_set_height(tick0, 14);
        lv_obj_set_style_bg_color(tick0, lv_color_hex(0xE6E9F0), 0);
        lv_obj_set_style_radius(tick0, 0, 0);
        lv_obj_set_style_border_width(tick0, 0, 0);
        lv_obj_set_style_pad_all(tick0, 0, 0);
        lv_obj_set_style_transform_rotation(tick0, 0, 0);
        lv_obj_set_style_transform_pivot_x(tick0, 2, 0);
        lv_obj_set_style_transform_pivot_y(tick0, 108, 0);

        lv_obj_t * tick1 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tick1, "tick1");
        lv_obj_set_x(tick1, 119);
        lv_obj_set_y(tick1, 20);
        lv_obj_set_width(tick1, 2);
        lv_obj_set_height(tick1, 6);
        lv_obj_set_style_bg_color(tick1, lv_color_hex(0x9AA3B2), 0);
        lv_obj_set_style_radius(tick1, 0, 0);
        lv_obj_set_style_border_width(tick1, 0, 0);
        lv_obj_set_style_pad_all(tick1, 0, 0);
        lv_obj_set_style_transform_rotation(tick1, 60, 0);
        lv_obj_set_style_transform_pivot_x(tick1, 1, 0);
        lv_obj_set_style_transform_pivot_y(tick1, 108, 0);

        lv_obj_t * tick2 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tick2, "tick2");
        lv_obj_set_x(tick2, 119);
        lv_obj_set_y(tick2, 20);
        lv_obj_set_width(tick2, 2);
        lv_obj_set_height(tick2, 6);
        lv_obj_set_style_bg_color(tick2, lv_color_hex(0x9AA3B2), 0);
        lv_obj_set_style_radius(tick2, 0, 0);
        lv_obj_set_style_border_width(tick2, 0, 0);
        lv_obj_set_style_pad_all(tick2, 0, 0);
        lv_obj_set_style_transform_rotation(tick2, 120, 0);
        lv_obj_set_style_transform_pivot_x(tick2, 1, 0);
        lv_obj_set_style_transform_pivot_y(tick2, 108, 0);

        lv_obj_t * tick3 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tick3, "tick3");
        lv_obj_set_x(tick3, 119);
        lv_obj_set_y(tick3, 20);
        lv_obj_set_width(tick3, 2);
        lv_obj_set_height(tick3, 6);
        lv_obj_set_style_bg_color(tick3, lv_color_hex(0x9AA3B2), 0);
        lv_obj_set_style_radius(tick3, 0, 0);
        lv_obj_set_style_border_width(tick3, 0, 0);
        lv_obj_set_style_pad_all(tick3, 0, 0);
        lv_obj_set_style_transform_rotation(tick3, 180, 0);
        lv_obj_set_style_transform_pivot_x(tick3, 1, 0);
        lv_obj_set_style_transform_pivot_y(tick3, 108, 0);

        lv_obj_t * tick4 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tick4, "tick4");
        lv_obj_set_x(tick4, 119);
        lv_obj_set_y(tick4, 20);
        lv_obj_set_width(tick4, 2);
        lv_obj_set_height(tick4, 6);
        lv_obj_set_style_bg_color(tick4, lv_color_hex(0x9AA3B2), 0);
        lv_obj_set_style_radius(tick4, 0, 0);
        lv_obj_set_style_border_width(tick4, 0, 0);
        lv_obj_set_style_pad_all(tick4, 0, 0);
        lv_obj_set_style_transform_rotation(tick4, 240, 0);
        lv_obj_set_style_transform_pivot_x(tick4, 1, 0);
        lv_obj_set_style_transform_pivot_y(tick4, 108, 0);

        lv_obj_t * tick5 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tick5, "tick5");
        lv_obj_set_x(tick5, 118);
        lv_obj_set_y(tick5, 20);
        lv_obj_set_width(tick5, 4);
        lv_obj_set_height(tick5, 14);
        lv_obj_set_style_bg_color(tick5, lv_color_hex(0xE6E9F0), 0);
        lv_obj_set_style_radius(tick5, 0, 0);
        lv_obj_set_style_border_width(tick5, 0, 0);
        lv_obj_set_style_pad_all(tick5, 0, 0);
        lv_obj_set_style_transform_rotation(tick5, 300, 0);
        lv_obj_set_style_transform_pivot_x(tick5, 2, 0);
        lv_obj_set_style_transform_pivot_y(tick5, 108, 0);

        lv_obj_t * tick6 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tick6, "tick6");
        lv_obj_set_x(tick6, 119);
        lv_obj_set_y(tick6, 20);
        lv_obj_set_width(tick6, 2);
        lv_obj_set_height(tick6, 6);
        lv_obj_set_style_bg_color(tick6, lv_color_hex(0x9AA3B2), 0);
        lv_obj_set_style_radius(tick6, 0, 0);
        lv_obj_set_style_border_width(tick6, 0, 0);
        lv_obj_set_style_pad_all(tick6, 0, 0);
        lv_obj_set_style_transform_rotation(tick6, 360, 0);
        lv_obj_set_style_transform_pivot_x(tick6, 1, 0);
        lv_obj_set_style_transform_pivot_y(tick6, 108, 0);

        lv_obj_t * tick7 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tick7, "tick7");
        lv_obj_set_x(tick7, 119);
        lv_obj_set_y(tick7, 20);
        lv_obj_set_width(tick7, 2);
        lv_obj_set_height(tick7, 6);
        lv_obj_set_style_bg_color(tick7, lv_color_hex(0x9AA3B2), 0);
        lv_obj_set_style_radius(tick7, 0, 0);
        lv_obj_set_style_border_width(tick7, 0, 0);
        lv_obj_set_style_pad_all(tick7, 0, 0);
        lv_obj_set_style_transform_rotation(tick7, 420, 0);
        lv_obj_set_style_transform_pivot_x(tick7, 1, 0);
        lv_obj_set_style_transform_pivot_y(tick7, 108, 0);

        lv_obj_t * tick8 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tick8, "tick8");
        lv_obj_set_x(tick8, 119);
        lv_obj_set_y(tick8, 20);
        lv_obj_set_width(tick8, 2);
        lv_obj_set_height(tick8, 6);
        lv_obj_set_style_bg_color(tick8, lv_color_hex(0x9AA3B2), 0);
        lv_obj_set_style_radius(tick8, 0, 0);
        lv_obj_set_style_border_width(tick8, 0, 0);
        lv_obj_set_style_pad_all(tick8, 0, 0);
        lv_obj_set_style_transform_rotation(tick8, 480, 0);
        lv_obj_set_style_transform_pivot_x(tick8, 1, 0);
        lv_obj_set_style_transform_pivot_y(tick8, 108, 0);

        lv_obj_t * tick9 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tick9, "tick9");
        lv_obj_set_x(tick9, 119);
        lv_obj_set_y(tick9, 20);
        lv_obj_set_width(tick9, 2);
        lv_obj_set_height(tick9, 6);
        lv_obj_set_style_bg_color(tick9, lv_color_hex(0x9AA3B2), 0);
        lv_obj_set_style_radius(tick9, 0, 0);
        lv_obj_set_style_border_width(tick9, 0, 0);
        lv_obj_set_style_pad_all(tick9, 0, 0);
        lv_obj_set_style_transform_rotation(tick9, 540, 0);
        lv_obj_set_style_transform_pivot_x(tick9, 1, 0);
        lv_obj_set_style_transform_pivot_y(tick9, 108, 0);

        lv_obj_t * tick10 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tick10, "tick10");
        lv_obj_set_x(tick10, 118);
        lv_obj_set_y(tick10, 20);
        lv_obj_set_width(tick10, 4);
        lv_obj_set_height(tick10, 14);
        lv_obj_set_style_bg_color(tick10, lv_color_hex(0xE6E9F0), 0);
        lv_obj_set_style_radius(tick10, 0, 0);
        lv_obj_set_style_border_width(tick10, 0, 0);
        lv_obj_set_style_pad_all(tick10, 0, 0);
        lv_obj_set_style_transform_rotation(tick10, 600, 0);
        lv_obj_set_style_transform_pivot_x(tick10, 2, 0);
        lv_obj_set_style_transform_pivot_y(tick10, 108, 0);

        lv_obj_t * tick11 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tick11, "tick11");
        lv_obj_set_x(tick11, 119);
        lv_obj_set_y(tick11, 20);
        lv_obj_set_width(tick11, 2);
        lv_obj_set_height(tick11, 6);
        lv_obj_set_style_bg_color(tick11, lv_color_hex(0x9AA3B2), 0);
        lv_obj_set_style_radius(tick11, 0, 0);
        lv_obj_set_style_border_width(tick11, 0, 0);
        lv_obj_set_style_pad_all(tick11, 0, 0);
        lv_obj_set_style_transform_rotation(tick11, 660, 0);
        lv_obj_set_style_transform_pivot_x(tick11, 1, 0);
        lv_obj_set_style_transform_pivot_y(tick11, 108, 0);

        lv_obj_t * tick12 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tick12, "tick12");
        lv_obj_set_x(tick12, 119);
        lv_obj_set_y(tick12, 20);
        lv_obj_set_width(tick12, 2);
        lv_obj_set_height(tick12, 6);
        lv_obj_set_style_bg_color(tick12, lv_color_hex(0x9AA3B2), 0);
        lv_obj_set_style_radius(tick12, 0, 0);
        lv_obj_set_style_border_width(tick12, 0, 0);
        lv_obj_set_style_pad_all(tick12, 0, 0);
        lv_obj_set_style_transform_rotation(tick12, 720, 0);
        lv_obj_set_style_transform_pivot_x(tick12, 1, 0);
        lv_obj_set_style_transform_pivot_y(tick12, 108, 0);

        lv_obj_t * tick13 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tick13, "tick13");
        lv_obj_set_x(tick13, 119);
        lv_obj_set_y(tick13, 20);
        lv_obj_set_width(tick13, 2);
        lv_obj_set_height(tick13, 6);
        lv_obj_set_style_bg_color(tick13, lv_color_hex(0x9AA3B2), 0);
        lv_obj_set_style_radius(tick13, 0, 0);
        lv_obj_set_style_border_width(tick13, 0, 0);
        lv_obj_set_style_pad_all(tick13, 0, 0);
        lv_obj_set_style_transform_rotation(tick13, 780, 0);
        lv_obj_set_style_transform_pivot_x(tick13, 1, 0);
        lv_obj_set_style_transform_pivot_y(tick13, 108, 0);

        lv_obj_t * tick14 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tick14, "tick14");
        lv_obj_set_x(tick14, 119);
        lv_obj_set_y(tick14, 20);
        lv_obj_set_width(tick14, 2);
        lv_obj_set_height(tick14, 6);
        lv_obj_set_style_bg_color(tick14, lv_color_hex(0x9AA3B2), 0);
        lv_obj_set_style_radius(tick14, 0, 0);
        lv_obj_set_style_border_width(tick14, 0, 0);
        lv_obj_set_style_pad_all(tick14, 0, 0);
        lv_obj_set_style_transform_rotation(tick14, 840, 0);
        lv_obj_set_style_transform_pivot_x(tick14, 1, 0);
        lv_obj_set_style_transform_pivot_y(tick14, 108, 0);

        lv_obj_t * tick15 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tick15, "tick15");
        lv_obj_set_x(tick15, 118);
        lv_obj_set_y(tick15, 20);
        lv_obj_set_width(tick15, 4);
        lv_obj_set_height(tick15, 14);
        lv_obj_set_style_bg_color(tick15, lv_color_hex(0xE6E9F0), 0);
        lv_obj_set_style_radius(tick15, 0, 0);
        lv_obj_set_style_border_width(tick15, 0, 0);
        lv_obj_set_style_pad_all(tick15, 0, 0);
        lv_obj_set_style_transform_rotation(tick15, 900, 0);
        lv_obj_set_style_transform_pivot_x(tick15, 2, 0);
        lv_obj_set_style_transform_pivot_y(tick15, 108, 0);

        lv_obj_t * tick16 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tick16, "tick16");
        lv_obj_set_x(tick16, 119);
        lv_obj_set_y(tick16, 20);
        lv_obj_set_width(tick16, 2);
        lv_obj_set_height(tick16, 6);
        lv_obj_set_style_bg_color(tick16, lv_color_hex(0x9AA3B2), 0);
        lv_obj_set_style_radius(tick16, 0, 0);
        lv_obj_set_style_border_width(tick16, 0, 0);
        lv_obj_set_style_pad_all(tick16, 0, 0);
        lv_obj_set_style_transform_rotation(tick16, 960, 0);
        lv_obj_set_style_transform_pivot_x(tick16, 1, 0);
        lv_obj_set_style_transform_pivot_y(tick16, 108, 0);

        lv_obj_t * tick17 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tick17, "tick17");
        lv_obj_set_x(tick17, 119);
        lv_obj_set_y(tick17, 20);
        lv_obj_set_width(tick17, 2);
        lv_obj_set_height(tick17, 6);
        lv_obj_set_style_bg_color(tick17, lv_color_hex(0x9AA3B2), 0);
        lv_obj_set_style_radius(tick17, 0, 0);
        lv_obj_set_style_border_width(tick17, 0, 0);
        lv_obj_set_style_pad_all(tick17, 0, 0);
        lv_obj_set_style_transform_rotation(tick17, 1020, 0);
        lv_obj_set_style_transform_pivot_x(tick17, 1, 0);
        lv_obj_set_style_transform_pivot_y(tick17, 108, 0);

        lv_obj_t * tick18 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tick18, "tick18");
        lv_obj_set_x(tick18, 119);
        lv_obj_set_y(tick18, 20);
        lv_obj_set_width(tick18, 2);
        lv_obj_set_height(tick18, 6);
        lv_obj_set_style_bg_color(tick18, lv_color_hex(0x9AA3B2), 0);
        lv_obj_set_style_radius(tick18, 0, 0);
        lv_obj_set_style_border_width(tick18, 0, 0);
        lv_obj_set_style_pad_all(tick18, 0, 0);
        lv_obj_set_style_transform_rotation(tick18, 1080, 0);
        lv_obj_set_style_transform_pivot_x(tick18, 1, 0);
        lv_obj_set_style_transform_pivot_y(tick18, 108, 0);

        lv_obj_t * tick19 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tick19, "tick19");
        lv_obj_set_x(tick19, 119);
        lv_obj_set_y(tick19, 20);
        lv_obj_set_width(tick19, 2);
        lv_obj_set_height(tick19, 6);
        lv_obj_set_style_bg_color(tick19, lv_color_hex(0x9AA3B2), 0);
        lv_obj_set_style_radius(tick19, 0, 0);
        lv_obj_set_style_border_width(tick19, 0, 0);
        lv_obj_set_style_pad_all(tick19, 0, 0);
        lv_obj_set_style_transform_rotation(tick19, 1140, 0);
        lv_obj_set_style_transform_pivot_x(tick19, 1, 0);
        lv_obj_set_style_transform_pivot_y(tick19, 108, 0);

        lv_obj_t * tick20 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tick20, "tick20");
        lv_obj_set_x(tick20, 118);
        lv_obj_set_y(tick20, 20);
        lv_obj_set_width(tick20, 4);
        lv_obj_set_height(tick20, 14);
        lv_obj_set_style_bg_color(tick20, lv_color_hex(0xE6E9F0), 0);
        lv_obj_set_style_radius(tick20, 0, 0);
        lv_obj_set_style_border_width(tick20, 0, 0);
        lv_obj_set_style_pad_all(tick20, 0, 0);
        lv_obj_set_style_transform_rotation(tick20, 1200, 0);
        lv_obj_set_style_transform_pivot_x(tick20, 2, 0);
        lv_obj_set_style_transform_pivot_y(tick20, 108, 0);

        lv_obj_t * tick21 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tick21, "tick21");
        lv_obj_set_x(tick21, 119);
        lv_obj_set_y(tick21, 20);
        lv_obj_set_width(tick21, 2);
        lv_obj_set_height(tick21, 6);
        lv_obj_set_style_bg_color(tick21, lv_color_hex(0x9AA3B2), 0);
        lv_obj_set_style_radius(tick21, 0, 0);
        lv_obj_set_style_border_width(tick21, 0, 0);
        lv_obj_set_style_pad_all(tick21, 0, 0);
        lv_obj_set_style_transform_rotation(tick21, 1260, 0);
        lv_obj_set_style_transform_pivot_x(tick21, 1, 0);
        lv_obj_set_style_transform_pivot_y(tick21, 108, 0);

        lv_obj_t * tick22 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tick22, "tick22");
        lv_obj_set_x(tick22, 119);
        lv_obj_set_y(tick22, 20);
        lv_obj_set_width(tick22, 2);
        lv_obj_set_height(tick22, 6);
        lv_obj_set_style_bg_color(tick22, lv_color_hex(0x9AA3B2), 0);
        lv_obj_set_style_radius(tick22, 0, 0);
        lv_obj_set_style_border_width(tick22, 0, 0);
        lv_obj_set_style_pad_all(tick22, 0, 0);
        lv_obj_set_style_transform_rotation(tick22, 1320, 0);
        lv_obj_set_style_transform_pivot_x(tick22, 1, 0);
        lv_obj_set_style_transform_pivot_y(tick22, 108, 0);

        lv_obj_t * tick23 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tick23, "tick23");
        lv_obj_set_x(tick23, 119);
        lv_obj_set_y(tick23, 20);
        lv_obj_set_width(tick23, 2);
        lv_obj_set_height(tick23, 6);
        lv_obj_set_style_bg_color(tick23, lv_color_hex(0x9AA3B2), 0);
        lv_obj_set_style_radius(tick23, 0, 0);
        lv_obj_set_style_border_width(tick23, 0, 0);
        lv_obj_set_style_pad_all(tick23, 0, 0);
        lv_obj_set_style_transform_rotation(tick23, 1380, 0);
        lv_obj_set_style_transform_pivot_x(tick23, 1, 0);
        lv_obj_set_style_transform_pivot_y(tick23, 108, 0);

        lv_obj_t * tick24 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tick24, "tick24");
        lv_obj_set_x(tick24, 119);
        lv_obj_set_y(tick24, 20);
        lv_obj_set_width(tick24, 2);
        lv_obj_set_height(tick24, 6);
        lv_obj_set_style_bg_color(tick24, lv_color_hex(0x9AA3B2), 0);
        lv_obj_set_style_radius(tick24, 0, 0);
        lv_obj_set_style_border_width(tick24, 0, 0);
        lv_obj_set_style_pad_all(tick24, 0, 0);
        lv_obj_set_style_transform_rotation(tick24, 1440, 0);
        lv_obj_set_style_transform_pivot_x(tick24, 1, 0);
        lv_obj_set_style_transform_pivot_y(tick24, 108, 0);

        lv_obj_t * tick25 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tick25, "tick25");
        lv_obj_set_x(tick25, 118);
        lv_obj_set_y(tick25, 20);
        lv_obj_set_width(tick25, 4);
        lv_obj_set_height(tick25, 14);
        lv_obj_set_style_bg_color(tick25, lv_color_hex(0xE6E9F0), 0);
        lv_obj_set_style_radius(tick25, 0, 0);
        lv_obj_set_style_border_width(tick25, 0, 0);
        lv_obj_set_style_pad_all(tick25, 0, 0);
        lv_obj_set_style_transform_rotation(tick25, 1500, 0);
        lv_obj_set_style_transform_pivot_x(tick25, 2, 0);
        lv_obj_set_style_transform_pivot_y(tick25, 108, 0);

        lv_obj_t * tick26 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tick26, "tick26");
        lv_obj_set_x(tick26, 119);
        lv_obj_set_y(tick26, 20);
        lv_obj_set_width(tick26, 2);
        lv_obj_set_height(tick26, 6);
        lv_obj_set_style_bg_color(tick26, lv_color_hex(0x9AA3B2), 0);
        lv_obj_set_style_radius(tick26, 0, 0);
        lv_obj_set_style_border_width(tick26, 0, 0);
        lv_obj_set_style_pad_all(tick26, 0, 0);
        lv_obj_set_style_transform_rotation(tick26, 1560, 0);
        lv_obj_set_style_transform_pivot_x(tick26, 1, 0);
        lv_obj_set_style_transform_pivot_y(tick26, 108, 0);

        lv_obj_t * tick27 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tick27, "tick27");
        lv_obj_set_x(tick27, 119);
        lv_obj_set_y(tick27, 20);
        lv_obj_set_width(tick27, 2);
        lv_obj_set_height(tick27, 6);
        lv_obj_set_style_bg_color(tick27, lv_color_hex(0x9AA3B2), 0);
        lv_obj_set_style_radius(tick27, 0, 0);
        lv_obj_set_style_border_width(tick27, 0, 0);
        lv_obj_set_style_pad_all(tick27, 0, 0);
        lv_obj_set_style_transform_rotation(tick27, 1620, 0);
        lv_obj_set_style_transform_pivot_x(tick27, 1, 0);
        lv_obj_set_style_transform_pivot_y(tick27, 108, 0);

        lv_obj_t * tick28 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tick28, "tick28");
        lv_obj_set_x(tick28, 119);
        lv_obj_set_y(tick28, 20);
        lv_obj_set_width(tick28, 2);
        lv_obj_set_height(tick28, 6);
        lv_obj_set_style_bg_color(tick28, lv_color_hex(0x9AA3B2), 0);
        lv_obj_set_style_radius(tick28, 0, 0);
        lv_obj_set_style_border_width(tick28, 0, 0);
        lv_obj_set_style_pad_all(tick28, 0, 0);
        lv_obj_set_style_transform_rotation(tick28, 1680, 0);
        lv_obj_set_style_transform_pivot_x(tick28, 1, 0);
        lv_obj_set_style_transform_pivot_y(tick28, 108, 0);

        lv_obj_t * tick29 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tick29, "tick29");
        lv_obj_set_x(tick29, 119);
        lv_obj_set_y(tick29, 20);
        lv_obj_set_width(tick29, 2);
        lv_obj_set_height(tick29, 6);
        lv_obj_set_style_bg_color(tick29, lv_color_hex(0x9AA3B2), 0);
        lv_obj_set_style_radius(tick29, 0, 0);
        lv_obj_set_style_border_width(tick29, 0, 0);
        lv_obj_set_style_pad_all(tick29, 0, 0);
        lv_obj_set_style_transform_rotation(tick29, 1740, 0);
        lv_obj_set_style_transform_pivot_x(tick29, 1, 0);
        lv_obj_set_style_transform_pivot_y(tick29, 108, 0);

        lv_obj_t * tick30 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tick30, "tick30");
        lv_obj_set_x(tick30, 118);
        lv_obj_set_y(tick30, 20);
        lv_obj_set_width(tick30, 4);
        lv_obj_set_height(tick30, 14);
        lv_obj_set_style_bg_color(tick30, lv_color_hex(0xE6E9F0), 0);
        lv_obj_set_style_radius(tick30, 0, 0);
        lv_obj_set_style_border_width(tick30, 0, 0);
        lv_obj_set_style_pad_all(tick30, 0, 0);
        lv_obj_set_style_transform_rotation(tick30, 1800, 0);
        lv_obj_set_style_transform_pivot_x(tick30, 2, 0);
        lv_obj_set_style_transform_pivot_y(tick30, 108, 0);

        lv_obj_t * tick31 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tick31, "tick31");
        lv_obj_set_x(tick31, 119);
        lv_obj_set_y(tick31, 20);
        lv_obj_set_width(tick31, 2);
        lv_obj_set_height(tick31, 6);
        lv_obj_set_style_bg_color(tick31, lv_color_hex(0x9AA3B2), 0);
        lv_obj_set_style_radius(tick31, 0, 0);
        lv_obj_set_style_border_width(tick31, 0, 0);
        lv_obj_set_style_pad_all(tick31, 0, 0);
        lv_obj_set_style_transform_rotation(tick31, 1860, 0);
        lv_obj_set_style_transform_pivot_x(tick31, 1, 0);
        lv_obj_set_style_transform_pivot_y(tick31, 108, 0);

        lv_obj_t * tick32 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tick32, "tick32");
        lv_obj_set_x(tick32, 119);
        lv_obj_set_y(tick32, 20);
        lv_obj_set_width(tick32, 2);
        lv_obj_set_height(tick32, 6);
        lv_obj_set_style_bg_color(tick32, lv_color_hex(0x9AA3B2), 0);
        lv_obj_set_style_radius(tick32, 0, 0);
        lv_obj_set_style_border_width(tick32, 0, 0);
        lv_obj_set_style_pad_all(tick32, 0, 0);
        lv_obj_set_style_transform_rotation(tick32, 1920, 0);
        lv_obj_set_style_transform_pivot_x(tick32, 1, 0);
        lv_obj_set_style_transform_pivot_y(tick32, 108, 0);

        lv_obj_t * tick33 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tick33, "tick33");
        lv_obj_set_x(tick33, 119);
        lv_obj_set_y(tick33, 20);
        lv_obj_set_width(tick33, 2);
        lv_obj_set_height(tick33, 6);
        lv_obj_set_style_bg_color(tick33, lv_color_hex(0x9AA3B2), 0);
        lv_obj_set_style_radius(tick33, 0, 0);
        lv_obj_set_style_border_width(tick33, 0, 0);
        lv_obj_set_style_pad_all(tick33, 0, 0);
        lv_obj_set_style_transform_rotation(tick33, 1980, 0);
        lv_obj_set_style_transform_pivot_x(tick33, 1, 0);
        lv_obj_set_style_transform_pivot_y(tick33, 108, 0);

        lv_obj_t * tick34 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tick34, "tick34");
        lv_obj_set_x(tick34, 119);
        lv_obj_set_y(tick34, 20);
        lv_obj_set_width(tick34, 2);
        lv_obj_set_height(tick34, 6);
        lv_obj_set_style_bg_color(tick34, lv_color_hex(0x9AA3B2), 0);
        lv_obj_set_style_radius(tick34, 0, 0);
        lv_obj_set_style_border_width(tick34, 0, 0);
        lv_obj_set_style_pad_all(tick34, 0, 0);
        lv_obj_set_style_transform_rotation(tick34, 2040, 0);
        lv_obj_set_style_transform_pivot_x(tick34, 1, 0);
        lv_obj_set_style_transform_pivot_y(tick34, 108, 0);

        lv_obj_t * tick35 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tick35, "tick35");
        lv_obj_set_x(tick35, 118);
        lv_obj_set_y(tick35, 20);
        lv_obj_set_width(tick35, 4);
        lv_obj_set_height(tick35, 14);
        lv_obj_set_style_bg_color(tick35, lv_color_hex(0xE6E9F0), 0);
        lv_obj_set_style_radius(tick35, 0, 0);
        lv_obj_set_style_border_width(tick35, 0, 0);
        lv_obj_set_style_pad_all(tick35, 0, 0);
        lv_obj_set_style_transform_rotation(tick35, 2100, 0);
        lv_obj_set_style_transform_pivot_x(tick35, 2, 0);
        lv_obj_set_style_transform_pivot_y(tick35, 108, 0);

        lv_obj_t * tick36 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tick36, "tick36");
        lv_obj_set_x(tick36, 119);
        lv_obj_set_y(tick36, 20);
        lv_obj_set_width(tick36, 2);
        lv_obj_set_height(tick36, 6);
        lv_obj_set_style_bg_color(tick36, lv_color_hex(0x9AA3B2), 0);
        lv_obj_set_style_radius(tick36, 0, 0);
        lv_obj_set_style_border_width(tick36, 0, 0);
        lv_obj_set_style_pad_all(tick36, 0, 0);
        lv_obj_set_style_transform_rotation(tick36, 2160, 0);
        lv_obj_set_style_transform_pivot_x(tick36, 1, 0);
        lv_obj_set_style_transform_pivot_y(tick36, 108, 0);

        lv_obj_t * tick37 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tick37, "tick37");
        lv_obj_set_x(tick37, 119);
        lv_obj_set_y(tick37, 20);
        lv_obj_set_width(tick37, 2);
        lv_obj_set_height(tick37, 6);
        lv_obj_set_style_bg_color(tick37, lv_color_hex(0x9AA3B2), 0);
        lv_obj_set_style_radius(tick37, 0, 0);
        lv_obj_set_style_border_width(tick37, 0, 0);
        lv_obj_set_style_pad_all(tick37, 0, 0);
        lv_obj_set_style_transform_rotation(tick37, 2220, 0);
        lv_obj_set_style_transform_pivot_x(tick37, 1, 0);
        lv_obj_set_style_transform_pivot_y(tick37, 108, 0);

        lv_obj_t * tick38 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tick38, "tick38");
        lv_obj_set_x(tick38, 119);
        lv_obj_set_y(tick38, 20);
        lv_obj_set_width(tick38, 2);
        lv_obj_set_height(tick38, 6);
        lv_obj_set_style_bg_color(tick38, lv_color_hex(0x9AA3B2), 0);
        lv_obj_set_style_radius(tick38, 0, 0);
        lv_obj_set_style_border_width(tick38, 0, 0);
        lv_obj_set_style_pad_all(tick38, 0, 0);
        lv_obj_set_style_transform_rotation(tick38, 2280, 0);
        lv_obj_set_style_transform_pivot_x(tick38, 1, 0);
        lv_obj_set_style_transform_pivot_y(tick38, 108, 0);

        lv_obj_t * tick39 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tick39, "tick39");
        lv_obj_set_x(tick39, 119);
        lv_obj_set_y(tick39, 20);
        lv_obj_set_width(tick39, 2);
        lv_obj_set_height(tick39, 6);
        lv_obj_set_style_bg_color(tick39, lv_color_hex(0x9AA3B2), 0);
        lv_obj_set_style_radius(tick39, 0, 0);
        lv_obj_set_style_border_width(tick39, 0, 0);
        lv_obj_set_style_pad_all(tick39, 0, 0);
        lv_obj_set_style_transform_rotation(tick39, 2340, 0);
        lv_obj_set_style_transform_pivot_x(tick39, 1, 0);
        lv_obj_set_style_transform_pivot_y(tick39, 108, 0);

        lv_obj_t * tick40 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tick40, "tick40");
        lv_obj_set_x(tick40, 118);
        lv_obj_set_y(tick40, 20);
        lv_obj_set_width(tick40, 4);
        lv_obj_set_height(tick40, 14);
        lv_obj_set_style_bg_color(tick40, lv_color_hex(0xE6E9F0), 0);
        lv_obj_set_style_radius(tick40, 0, 0);
        lv_obj_set_style_border_width(tick40, 0, 0);
        lv_obj_set_style_pad_all(tick40, 0, 0);
        lv_obj_set_style_transform_rotation(tick40, 2400, 0);
        lv_obj_set_style_transform_pivot_x(tick40, 2, 0);
        lv_obj_set_style_transform_pivot_y(tick40, 108, 0);

        lv_obj_t * tick41 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tick41, "tick41");
        lv_obj_set_x(tick41, 119);
        lv_obj_set_y(tick41, 20);
        lv_obj_set_width(tick41, 2);
        lv_obj_set_height(tick41, 6);
        lv_obj_set_style_bg_color(tick41, lv_color_hex(0x9AA3B2), 0);
        lv_obj_set_style_radius(tick41, 0, 0);
        lv_obj_set_style_border_width(tick41, 0, 0);
        lv_obj_set_style_pad_all(tick41, 0, 0);
        lv_obj_set_style_transform_rotation(tick41, 2460, 0);
        lv_obj_set_style_transform_pivot_x(tick41, 1, 0);
        lv_obj_set_style_transform_pivot_y(tick41, 108, 0);

        lv_obj_t * tick42 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tick42, "tick42");
        lv_obj_set_x(tick42, 119);
        lv_obj_set_y(tick42, 20);
        lv_obj_set_width(tick42, 2);
        lv_obj_set_height(tick42, 6);
        lv_obj_set_style_bg_color(tick42, lv_color_hex(0x9AA3B2), 0);
        lv_obj_set_style_radius(tick42, 0, 0);
        lv_obj_set_style_border_width(tick42, 0, 0);
        lv_obj_set_style_pad_all(tick42, 0, 0);
        lv_obj_set_style_transform_rotation(tick42, 2520, 0);
        lv_obj_set_style_transform_pivot_x(tick42, 1, 0);
        lv_obj_set_style_transform_pivot_y(tick42, 108, 0);

        lv_obj_t * tick43 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tick43, "tick43");
        lv_obj_set_x(tick43, 119);
        lv_obj_set_y(tick43, 20);
        lv_obj_set_width(tick43, 2);
        lv_obj_set_height(tick43, 6);
        lv_obj_set_style_bg_color(tick43, lv_color_hex(0x9AA3B2), 0);
        lv_obj_set_style_radius(tick43, 0, 0);
        lv_obj_set_style_border_width(tick43, 0, 0);
        lv_obj_set_style_pad_all(tick43, 0, 0);
        lv_obj_set_style_transform_rotation(tick43, 2580, 0);
        lv_obj_set_style_transform_pivot_x(tick43, 1, 0);
        lv_obj_set_style_transform_pivot_y(tick43, 108, 0);

        lv_obj_t * tick44 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tick44, "tick44");
        lv_obj_set_x(tick44, 119);
        lv_obj_set_y(tick44, 20);
        lv_obj_set_width(tick44, 2);
        lv_obj_set_height(tick44, 6);
        lv_obj_set_style_bg_color(tick44, lv_color_hex(0x9AA3B2), 0);
        lv_obj_set_style_radius(tick44, 0, 0);
        lv_obj_set_style_border_width(tick44, 0, 0);
        lv_obj_set_style_pad_all(tick44, 0, 0);
        lv_obj_set_style_transform_rotation(tick44, 2640, 0);
        lv_obj_set_style_transform_pivot_x(tick44, 1, 0);
        lv_obj_set_style_transform_pivot_y(tick44, 108, 0);

        lv_obj_t * tick45 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tick45, "tick45");
        lv_obj_set_x(tick45, 118);
        lv_obj_set_y(tick45, 20);
        lv_obj_set_width(tick45, 4);
        lv_obj_set_height(tick45, 14);
        lv_obj_set_style_bg_color(tick45, lv_color_hex(0xE6E9F0), 0);
        lv_obj_set_style_radius(tick45, 0, 0);
        lv_obj_set_style_border_width(tick45, 0, 0);
        lv_obj_set_style_pad_all(tick45, 0, 0);
        lv_obj_set_style_transform_rotation(tick45, 2700, 0);
        lv_obj_set_style_transform_pivot_x(tick45, 2, 0);
        lv_obj_set_style_transform_pivot_y(tick45, 108, 0);

        lv_obj_t * tick46 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tick46, "tick46");
        lv_obj_set_x(tick46, 119);
        lv_obj_set_y(tick46, 20);
        lv_obj_set_width(tick46, 2);
        lv_obj_set_height(tick46, 6);
        lv_obj_set_style_bg_color(tick46, lv_color_hex(0x9AA3B2), 0);
        lv_obj_set_style_radius(tick46, 0, 0);
        lv_obj_set_style_border_width(tick46, 0, 0);
        lv_obj_set_style_pad_all(tick46, 0, 0);
        lv_obj_set_style_transform_rotation(tick46, 2760, 0);
        lv_obj_set_style_transform_pivot_x(tick46, 1, 0);
        lv_obj_set_style_transform_pivot_y(tick46, 108, 0);

        lv_obj_t * tick47 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tick47, "tick47");
        lv_obj_set_x(tick47, 119);
        lv_obj_set_y(tick47, 20);
        lv_obj_set_width(tick47, 2);
        lv_obj_set_height(tick47, 6);
        lv_obj_set_style_bg_color(tick47, lv_color_hex(0x9AA3B2), 0);
        lv_obj_set_style_radius(tick47, 0, 0);
        lv_obj_set_style_border_width(tick47, 0, 0);
        lv_obj_set_style_pad_all(tick47, 0, 0);
        lv_obj_set_style_transform_rotation(tick47, 2820, 0);
        lv_obj_set_style_transform_pivot_x(tick47, 1, 0);
        lv_obj_set_style_transform_pivot_y(tick47, 108, 0);

        lv_obj_t * tick48 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tick48, "tick48");
        lv_obj_set_x(tick48, 119);
        lv_obj_set_y(tick48, 20);
        lv_obj_set_width(tick48, 2);
        lv_obj_set_height(tick48, 6);
        lv_obj_set_style_bg_color(tick48, lv_color_hex(0x9AA3B2), 0);
        lv_obj_set_style_radius(tick48, 0, 0);
        lv_obj_set_style_border_width(tick48, 0, 0);
        lv_obj_set_style_pad_all(tick48, 0, 0);
        lv_obj_set_style_transform_rotation(tick48, 2880, 0);
        lv_obj_set_style_transform_pivot_x(tick48, 1, 0);
        lv_obj_set_style_transform_pivot_y(tick48, 108, 0);

        lv_obj_t * tick49 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tick49, "tick49");
        lv_obj_set_x(tick49, 119);
        lv_obj_set_y(tick49, 20);
        lv_obj_set_width(tick49, 2);
        lv_obj_set_height(tick49, 6);
        lv_obj_set_style_bg_color(tick49, lv_color_hex(0x9AA3B2), 0);
        lv_obj_set_style_radius(tick49, 0, 0);
        lv_obj_set_style_border_width(tick49, 0, 0);
        lv_obj_set_style_pad_all(tick49, 0, 0);
        lv_obj_set_style_transform_rotation(tick49, 2940, 0);
        lv_obj_set_style_transform_pivot_x(tick49, 1, 0);
        lv_obj_set_style_transform_pivot_y(tick49, 108, 0);

        lv_obj_t * tick50 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tick50, "tick50");
        lv_obj_set_x(tick50, 118);
        lv_obj_set_y(tick50, 20);
        lv_obj_set_width(tick50, 4);
        lv_obj_set_height(tick50, 14);
        lv_obj_set_style_bg_color(tick50, lv_color_hex(0xE6E9F0), 0);
        lv_obj_set_style_radius(tick50, 0, 0);
        lv_obj_set_style_border_width(tick50, 0, 0);
        lv_obj_set_style_pad_all(tick50, 0, 0);
        lv_obj_set_style_transform_rotation(tick50, 3000, 0);
        lv_obj_set_style_transform_pivot_x(tick50, 2, 0);
        lv_obj_set_style_transform_pivot_y(tick50, 108, 0);

        lv_obj_t * tick51 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tick51, "tick51");
        lv_obj_set_x(tick51, 119);
        lv_obj_set_y(tick51, 20);
        lv_obj_set_width(tick51, 2);
        lv_obj_set_height(tick51, 6);
        lv_obj_set_style_bg_color(tick51, lv_color_hex(0x9AA3B2), 0);
        lv_obj_set_style_radius(tick51, 0, 0);
        lv_obj_set_style_border_width(tick51, 0, 0);
        lv_obj_set_style_pad_all(tick51, 0, 0);
        lv_obj_set_style_transform_rotation(tick51, 3060, 0);
        lv_obj_set_style_transform_pivot_x(tick51, 1, 0);
        lv_obj_set_style_transform_pivot_y(tick51, 108, 0);

        lv_obj_t * tick52 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tick52, "tick52");
        lv_obj_set_x(tick52, 119);
        lv_obj_set_y(tick52, 20);
        lv_obj_set_width(tick52, 2);
        lv_obj_set_height(tick52, 6);
        lv_obj_set_style_bg_color(tick52, lv_color_hex(0x9AA3B2), 0);
        lv_obj_set_style_radius(tick52, 0, 0);
        lv_obj_set_style_border_width(tick52, 0, 0);
        lv_obj_set_style_pad_all(tick52, 0, 0);
        lv_obj_set_style_transform_rotation(tick52, 3120, 0);
        lv_obj_set_style_transform_pivot_x(tick52, 1, 0);
        lv_obj_set_style_transform_pivot_y(tick52, 108, 0);

        lv_obj_t * tick53 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tick53, "tick53");
        lv_obj_set_x(tick53, 119);
        lv_obj_set_y(tick53, 20);
        lv_obj_set_width(tick53, 2);
        lv_obj_set_height(tick53, 6);
        lv_obj_set_style_bg_color(tick53, lv_color_hex(0x9AA3B2), 0);
        lv_obj_set_style_radius(tick53, 0, 0);
        lv_obj_set_style_border_width(tick53, 0, 0);
        lv_obj_set_style_pad_all(tick53, 0, 0);
        lv_obj_set_style_transform_rotation(tick53, 3180, 0);
        lv_obj_set_style_transform_pivot_x(tick53, 1, 0);
        lv_obj_set_style_transform_pivot_y(tick53, 108, 0);

        lv_obj_t * tick54 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tick54, "tick54");
        lv_obj_set_x(tick54, 119);
        lv_obj_set_y(tick54, 20);
        lv_obj_set_width(tick54, 2);
        lv_obj_set_height(tick54, 6);
        lv_obj_set_style_bg_color(tick54, lv_color_hex(0x9AA3B2), 0);
        lv_obj_set_style_radius(tick54, 0, 0);
        lv_obj_set_style_border_width(tick54, 0, 0);
        lv_obj_set_style_pad_all(tick54, 0, 0);
        lv_obj_set_style_transform_rotation(tick54, 3240, 0);
        lv_obj_set_style_transform_pivot_x(tick54, 1, 0);
        lv_obj_set_style_transform_pivot_y(tick54, 108, 0);

        lv_obj_t * tick55 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tick55, "tick55");
        lv_obj_set_x(tick55, 118);
        lv_obj_set_y(tick55, 20);
        lv_obj_set_width(tick55, 4);
        lv_obj_set_height(tick55, 14);
        lv_obj_set_style_bg_color(tick55, lv_color_hex(0xE6E9F0), 0);
        lv_obj_set_style_radius(tick55, 0, 0);
        lv_obj_set_style_border_width(tick55, 0, 0);
        lv_obj_set_style_pad_all(tick55, 0, 0);
        lv_obj_set_style_transform_rotation(tick55, 3300, 0);
        lv_obj_set_style_transform_pivot_x(tick55, 2, 0);
        lv_obj_set_style_transform_pivot_y(tick55, 108, 0);

        lv_obj_t * tick56 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tick56, "tick56");
        lv_obj_set_x(tick56, 119);
        lv_obj_set_y(tick56, 20);
        lv_obj_set_width(tick56, 2);
        lv_obj_set_height(tick56, 6);
        lv_obj_set_style_bg_color(tick56, lv_color_hex(0x9AA3B2), 0);
        lv_obj_set_style_radius(tick56, 0, 0);
        lv_obj_set_style_border_width(tick56, 0, 0);
        lv_obj_set_style_pad_all(tick56, 0, 0);
        lv_obj_set_style_transform_rotation(tick56, 3360, 0);
        lv_obj_set_style_transform_pivot_x(tick56, 1, 0);
        lv_obj_set_style_transform_pivot_y(tick56, 108, 0);

        lv_obj_t * tick57 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tick57, "tick57");
        lv_obj_set_x(tick57, 119);
        lv_obj_set_y(tick57, 20);
        lv_obj_set_width(tick57, 2);
        lv_obj_set_height(tick57, 6);
        lv_obj_set_style_bg_color(tick57, lv_color_hex(0x9AA3B2), 0);
        lv_obj_set_style_radius(tick57, 0, 0);
        lv_obj_set_style_border_width(tick57, 0, 0);
        lv_obj_set_style_pad_all(tick57, 0, 0);
        lv_obj_set_style_transform_rotation(tick57, 3420, 0);
        lv_obj_set_style_transform_pivot_x(tick57, 1, 0);
        lv_obj_set_style_transform_pivot_y(tick57, 108, 0);

        lv_obj_t * tick58 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tick58, "tick58");
        lv_obj_set_x(tick58, 119);
        lv_obj_set_y(tick58, 20);
        lv_obj_set_width(tick58, 2);
        lv_obj_set_height(tick58, 6);
        lv_obj_set_style_bg_color(tick58, lv_color_hex(0x9AA3B2), 0);
        lv_obj_set_style_radius(tick58, 0, 0);
        lv_obj_set_style_border_width(tick58, 0, 0);
        lv_obj_set_style_pad_all(tick58, 0, 0);
        lv_obj_set_style_transform_rotation(tick58, 3480, 0);
        lv_obj_set_style_transform_pivot_x(tick58, 1, 0);
        lv_obj_set_style_transform_pivot_y(tick58, 108, 0);

        lv_obj_t * tick59 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tick59, "tick59");
        lv_obj_set_x(tick59, 119);
        lv_obj_set_y(tick59, 20);
        lv_obj_set_width(tick59, 2);
        lv_obj_set_height(tick59, 6);
        lv_obj_set_style_bg_color(tick59, lv_color_hex(0x9AA3B2), 0);
        lv_obj_set_style_radius(tick59, 0, 0);
        lv_obj_set_style_border_width(tick59, 0, 0);
        lv_obj_set_style_pad_all(tick59, 0, 0);
        lv_obj_set_style_transform_rotation(tick59, 3540, 0);
        lv_obj_set_style_transform_pivot_x(tick59, 1, 0);
        lv_obj_set_style_transform_pivot_y(tick59, 108, 0);

        lv_obj_t * n12 = lv_label_create(lv_obj_0);
        lv_obj_set_name(n12, "n12");
        lv_obj_set_x(n12, 105);
        lv_obj_set_y(n12, 46);
        lv_obj_set_width(n12, 30);
        lv_label_set_text(n12, "12");
        lv_obj_set_style_text_color(n12, lv_color_hex(0xE6E9F0), 0);
        lv_obj_set_style_text_font(n12, font_h5, 0);
        lv_obj_set_style_text_align(n12, LV_TEXT_ALIGN_CENTER, 0);

        lv_obj_t * n3 = lv_label_create(lv_obj_0);
        lv_obj_set_name(n3, "n3");
        lv_obj_set_x(n3, 177);
        lv_obj_set_y(n3, 116);
        lv_obj_set_width(n3, 30);
        lv_label_set_text(n3, "3");
        lv_obj_set_style_text_color(n3, lv_color_hex(0xE6E9F0), 0);
        lv_obj_set_style_text_font(n3, font_h5, 0);
        lv_obj_set_style_text_align(n3, LV_TEXT_ALIGN_CENTER, 0);

        lv_obj_t * n6 = lv_label_create(lv_obj_0);
        lv_obj_set_name(n6, "n6");
        lv_obj_set_x(n6, 105);
        lv_obj_set_y(n6, 186);
        lv_obj_set_width(n6, 30);
        lv_label_set_text(n6, "6");
        lv_obj_set_style_text_color(n6, lv_color_hex(0xE6E9F0), 0);
        lv_obj_set_style_text_font(n6, font_h5, 0);
        lv_obj_set_style_text_align(n6, LV_TEXT_ALIGN_CENTER, 0);

        lv_obj_t * n9 = lv_label_create(lv_obj_0);
        lv_obj_set_name(n9, "n9");
        lv_obj_set_x(n9, 33);
        lv_obj_set_y(n9, 116);
        lv_obj_set_width(n9, 30);
        lv_label_set_text(n9, "9");
        lv_obj_set_style_text_color(n9, lv_color_hex(0xE6E9F0), 0);
        lv_obj_set_style_text_font(n9, font_h5, 0);
        lv_obj_set_style_text_align(n9, LV_TEXT_ALIGN_CENTER, 0);

        lv_obj_t * center_dot = lv_obj_create(lv_obj_0);
        lv_obj_set_name(center_dot, "center_dot");
        lv_obj_set_x(center_dot, 114);
        lv_obj_set_y(center_dot, 122);
        lv_obj_set_width(center_dot, 12);
        lv_obj_set_height(center_dot, 12);
        lv_obj_set_style_bg_color(center_dot, lv_color_hex(0x9429FF), 0);
        lv_obj_set_style_radius(center_dot, 6, 0);
        lv_obj_set_style_border_width(center_dot, 0, 0);
        lv_obj_set_style_pad_all(center_dot, 0, 0);

        lv_obj_t * card_date = lv_obj_create(lv_obj_0);
        lv_obj_set_name(card_date, "card_date");
        lv_obj_set_x(card_date, 14);
        lv_obj_set_y(card_date, 252);
        lv_obj_set_width(card_date, 102);
        lv_obj_set_height(card_date, 52);
        lv_obj_set_style_bg_color(card_date, lv_color_hex(0x1E232E), 0);
        lv_obj_set_style_radius(card_date, 16, 0);
        lv_obj_set_style_border_width(card_date, 0, 0);
        lv_obj_set_style_pad_all(card_date, 0, 0);

        lv_obj_t * card_steps = lv_obj_create(lv_obj_0);
        lv_obj_set_name(card_steps, "card_steps");
        lv_obj_set_x(card_steps, 124);
        lv_obj_set_y(card_steps, 252);
        lv_obj_set_width(card_steps, 102);
        lv_obj_set_height(card_steps, 52);
        lv_obj_set_style_bg_color(card_steps, lv_color_hex(0x1E232E), 0);
        lv_obj_set_style_radius(card_steps, 16, 0);
        lv_obj_set_style_border_width(card_steps, 0, 0);
        lv_obj_set_style_pad_all(card_steps, 0, 0);

        lv_obj_t * wd = lv_label_create(lv_obj_0);
        lv_obj_set_name(wd, "wd");
        lv_obj_set_x(wd, 15);
        lv_obj_set_y(wd, 258);
        lv_obj_set_width(wd, 100);
        lv_label_set_text(wd, "FRI");
        lv_obj_set_style_text_color(wd, lv_color_hex(0x9AA3B2), 0);
        lv_obj_set_style_text_font(wd, font_body, 0);
        lv_obj_set_style_text_align(wd, LV_TEXT_ALIGN_CENTER, 0);

        lv_obj_t * dm = lv_label_create(lv_obj_0);
        lv_obj_set_name(dm, "dm");
        lv_obj_set_x(dm, 15);
        lv_obj_set_y(dm, 276);
        lv_obj_set_width(dm, 100);
        lv_label_set_text(dm, "5 Nov");
        lv_obj_set_style_text_color(dm, lv_color_hex(0xE6E9F0), 0);
        lv_obj_set_style_text_font(dm, font_h5, 0);
        lv_obj_set_style_text_align(dm, LV_TEXT_ALIGN_CENTER, 0);

        lv_obj_t * steps_cap = lv_label_create(lv_obj_0);
        lv_obj_set_name(steps_cap, "steps_cap");
        lv_obj_set_x(steps_cap, 125);
        lv_obj_set_y(steps_cap, 258);
        lv_obj_set_width(steps_cap, 100);
        lv_label_set_text(steps_cap, "STEPS");
        lv_obj_set_style_text_color(steps_cap, lv_color_hex(0x9AA3B2), 0);
        lv_obj_set_style_text_font(steps_cap, font_body, 0);
        lv_obj_set_style_text_align(steps_cap, LV_TEXT_ALIGN_CENTER, 0);

        lv_obj_t * steps = lv_label_create(lv_obj_0);
        lv_obj_set_name(steps, "steps");
        lv_obj_set_x(steps, 125);
        lv_obj_set_y(steps, 276);
        lv_obj_set_width(steps, 100);
        lv_label_set_text(steps, "6842");
        lv_obj_set_style_text_color(steps, lv_color_hex(0x9429FF), 0);
        lv_obj_set_style_text_font(steps, font_h5, 0);
        lv_obj_set_style_text_align(steps, LV_TEXT_ALIGN_CENTER, 0);

        the_root = lv_obj_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

