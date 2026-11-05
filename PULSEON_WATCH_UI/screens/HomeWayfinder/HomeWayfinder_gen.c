/**
 * @file HomeWayfinder_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "HomeWayfinder_gen.h"
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

lv_obj_t * HomeWayfinder_create(void)
{
    LV_TRACE_OBJ_CREATE("begin");

    static lv_style_t wf_ind5;
    static lv_style_t wf_ind7;
    static lv_style_t wf_knob_off;

    static bool style_inited = false;

    if (!style_inited) {
        /*Init all styles*/
        lv_style_init(&wf_ind5);
        lv_style_init(&wf_ind7);
        lv_style_init(&wf_knob_off);

        lv_style_set_arc_width(&wf_ind5, 5);
        lv_style_set_arc_color(&wf_ind5, lv_color_hex(0xFF2A2A));
        lv_style_set_arc_width(&wf_ind7, 7);
        lv_style_set_arc_color(&wf_ind7, lv_color_hex(0xFF2A2A));
        lv_style_set_bg_opa(&wf_knob_off, (255 * 0 / 100));
        lv_style_set_pad_all(&wf_knob_off, 0);

        style_inited = true;
    }


    lv_obj_t * the_root = NULL;

    #if PULSEON_WATCH_UI_CHECK_COMPILE_TARGET(PULSEON_WATCH_UI_TARGET_ALL)
    if (PULSEON_WATCH_UI_check_target(PULSEON_WATCH_UI_TARGET_ALL)) {
        lv_obj_t * lv_obj_0 = lv_obj_create(NULL);
        lv_obj_set_name_static(lv_obj_0, "HomeWayfinder_#");
        lv_obj_set_width(lv_obj_0, 240);
        lv_obj_set_height(lv_obj_0, 320);
        lv_obj_set_style_bg_color(lv_obj_0, lv_color_hex(0x050000), 0);
        lv_obj_set_style_pad_all(lv_obj_0, 0, 0);
        lv_obj_set_style_border_width(lv_obj_0, 0, 0);

        lv_obj_t * tl0 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tl0, "tl0");
        lv_obj_set_x(tl0, 8);
        lv_obj_set_y(tl0, 42);
        lv_obj_set_width(tl0, 14);
        lv_obj_set_height(tl0, 2);
        lv_obj_set_style_bg_color(tl0, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(tl0, 0, 0);
        lv_obj_set_style_border_width(tl0, 0, 0);
        lv_obj_set_style_pad_all(tl0, 0, 0);

        lv_obj_t * tr0 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tr0, "tr0");
        lv_obj_set_x(tr0, 218);
        lv_obj_set_y(tr0, 42);
        lv_obj_set_width(tr0, 14);
        lv_obj_set_height(tr0, 2);
        lv_obj_set_style_bg_color(tr0, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(tr0, 0, 0);
        lv_obj_set_style_border_width(tr0, 0, 0);
        lv_obj_set_style_pad_all(tr0, 0, 0);

        lv_obj_t * tl1 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tl1, "tl1");
        lv_obj_set_x(tl1, 8);
        lv_obj_set_y(tl1, 52);
        lv_obj_set_width(tl1, 7);
        lv_obj_set_height(tl1, 2);
        lv_obj_set_style_bg_color(tl1, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(tl1, 0, 0);
        lv_obj_set_style_border_width(tl1, 0, 0);
        lv_obj_set_style_pad_all(tl1, 0, 0);

        lv_obj_t * tr1 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tr1, "tr1");
        lv_obj_set_x(tr1, 225);
        lv_obj_set_y(tr1, 52);
        lv_obj_set_width(tr1, 7);
        lv_obj_set_height(tr1, 2);
        lv_obj_set_style_bg_color(tr1, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(tr1, 0, 0);
        lv_obj_set_style_border_width(tr1, 0, 0);
        lv_obj_set_style_pad_all(tr1, 0, 0);

        lv_obj_t * tl2 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tl2, "tl2");
        lv_obj_set_x(tl2, 8);
        lv_obj_set_y(tl2, 62);
        lv_obj_set_width(tl2, 7);
        lv_obj_set_height(tl2, 2);
        lv_obj_set_style_bg_color(tl2, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(tl2, 0, 0);
        lv_obj_set_style_border_width(tl2, 0, 0);
        lv_obj_set_style_pad_all(tl2, 0, 0);

        lv_obj_t * tr2 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tr2, "tr2");
        lv_obj_set_x(tr2, 225);
        lv_obj_set_y(tr2, 62);
        lv_obj_set_width(tr2, 7);
        lv_obj_set_height(tr2, 2);
        lv_obj_set_style_bg_color(tr2, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(tr2, 0, 0);
        lv_obj_set_style_border_width(tr2, 0, 0);
        lv_obj_set_style_pad_all(tr2, 0, 0);

        lv_obj_t * tl3 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tl3, "tl3");
        lv_obj_set_x(tl3, 8);
        lv_obj_set_y(tl3, 72);
        lv_obj_set_width(tl3, 7);
        lv_obj_set_height(tl3, 2);
        lv_obj_set_style_bg_color(tl3, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(tl3, 0, 0);
        lv_obj_set_style_border_width(tl3, 0, 0);
        lv_obj_set_style_pad_all(tl3, 0, 0);

        lv_obj_t * tr3 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tr3, "tr3");
        lv_obj_set_x(tr3, 225);
        lv_obj_set_y(tr3, 72);
        lv_obj_set_width(tr3, 7);
        lv_obj_set_height(tr3, 2);
        lv_obj_set_style_bg_color(tr3, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(tr3, 0, 0);
        lv_obj_set_style_border_width(tr3, 0, 0);
        lv_obj_set_style_pad_all(tr3, 0, 0);

        lv_obj_t * tl4 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tl4, "tl4");
        lv_obj_set_x(tl4, 8);
        lv_obj_set_y(tl4, 82);
        lv_obj_set_width(tl4, 7);
        lv_obj_set_height(tl4, 2);
        lv_obj_set_style_bg_color(tl4, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(tl4, 0, 0);
        lv_obj_set_style_border_width(tl4, 0, 0);
        lv_obj_set_style_pad_all(tl4, 0, 0);

        lv_obj_t * tr4 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tr4, "tr4");
        lv_obj_set_x(tr4, 225);
        lv_obj_set_y(tr4, 82);
        lv_obj_set_width(tr4, 7);
        lv_obj_set_height(tr4, 2);
        lv_obj_set_style_bg_color(tr4, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(tr4, 0, 0);
        lv_obj_set_style_border_width(tr4, 0, 0);
        lv_obj_set_style_pad_all(tr4, 0, 0);

        lv_obj_t * tl5 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tl5, "tl5");
        lv_obj_set_x(tl5, 8);
        lv_obj_set_y(tl5, 92);
        lv_obj_set_width(tl5, 7);
        lv_obj_set_height(tl5, 2);
        lv_obj_set_style_bg_color(tl5, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(tl5, 0, 0);
        lv_obj_set_style_border_width(tl5, 0, 0);
        lv_obj_set_style_pad_all(tl5, 0, 0);

        lv_obj_t * tr5 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tr5, "tr5");
        lv_obj_set_x(tr5, 225);
        lv_obj_set_y(tr5, 92);
        lv_obj_set_width(tr5, 7);
        lv_obj_set_height(tr5, 2);
        lv_obj_set_style_bg_color(tr5, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(tr5, 0, 0);
        lv_obj_set_style_border_width(tr5, 0, 0);
        lv_obj_set_style_pad_all(tr5, 0, 0);

        lv_obj_t * tl6 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tl6, "tl6");
        lv_obj_set_x(tl6, 8);
        lv_obj_set_y(tl6, 102);
        lv_obj_set_width(tl6, 14);
        lv_obj_set_height(tl6, 2);
        lv_obj_set_style_bg_color(tl6, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(tl6, 0, 0);
        lv_obj_set_style_border_width(tl6, 0, 0);
        lv_obj_set_style_pad_all(tl6, 0, 0);

        lv_obj_t * tr6 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tr6, "tr6");
        lv_obj_set_x(tr6, 218);
        lv_obj_set_y(tr6, 102);
        lv_obj_set_width(tr6, 14);
        lv_obj_set_height(tr6, 2);
        lv_obj_set_style_bg_color(tr6, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(tr6, 0, 0);
        lv_obj_set_style_border_width(tr6, 0, 0);
        lv_obj_set_style_pad_all(tr6, 0, 0);

        lv_obj_t * tl7 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tl7, "tl7");
        lv_obj_set_x(tl7, 8);
        lv_obj_set_y(tl7, 112);
        lv_obj_set_width(tl7, 7);
        lv_obj_set_height(tl7, 2);
        lv_obj_set_style_bg_color(tl7, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(tl7, 0, 0);
        lv_obj_set_style_border_width(tl7, 0, 0);
        lv_obj_set_style_pad_all(tl7, 0, 0);

        lv_obj_t * tr7 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tr7, "tr7");
        lv_obj_set_x(tr7, 225);
        lv_obj_set_y(tr7, 112);
        lv_obj_set_width(tr7, 7);
        lv_obj_set_height(tr7, 2);
        lv_obj_set_style_bg_color(tr7, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(tr7, 0, 0);
        lv_obj_set_style_border_width(tr7, 0, 0);
        lv_obj_set_style_pad_all(tr7, 0, 0);

        lv_obj_t * tl8 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tl8, "tl8");
        lv_obj_set_x(tl8, 8);
        lv_obj_set_y(tl8, 122);
        lv_obj_set_width(tl8, 7);
        lv_obj_set_height(tl8, 2);
        lv_obj_set_style_bg_color(tl8, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(tl8, 0, 0);
        lv_obj_set_style_border_width(tl8, 0, 0);
        lv_obj_set_style_pad_all(tl8, 0, 0);

        lv_obj_t * tr8 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tr8, "tr8");
        lv_obj_set_x(tr8, 225);
        lv_obj_set_y(tr8, 122);
        lv_obj_set_width(tr8, 7);
        lv_obj_set_height(tr8, 2);
        lv_obj_set_style_bg_color(tr8, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(tr8, 0, 0);
        lv_obj_set_style_border_width(tr8, 0, 0);
        lv_obj_set_style_pad_all(tr8, 0, 0);

        lv_obj_t * tl9 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tl9, "tl9");
        lv_obj_set_x(tl9, 8);
        lv_obj_set_y(tl9, 132);
        lv_obj_set_width(tl9, 7);
        lv_obj_set_height(tl9, 2);
        lv_obj_set_style_bg_color(tl9, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(tl9, 0, 0);
        lv_obj_set_style_border_width(tl9, 0, 0);
        lv_obj_set_style_pad_all(tl9, 0, 0);

        lv_obj_t * tr9 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tr9, "tr9");
        lv_obj_set_x(tr9, 225);
        lv_obj_set_y(tr9, 132);
        lv_obj_set_width(tr9, 7);
        lv_obj_set_height(tr9, 2);
        lv_obj_set_style_bg_color(tr9, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(tr9, 0, 0);
        lv_obj_set_style_border_width(tr9, 0, 0);
        lv_obj_set_style_pad_all(tr9, 0, 0);

        lv_obj_t * tl10 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tl10, "tl10");
        lv_obj_set_x(tl10, 8);
        lv_obj_set_y(tl10, 142);
        lv_obj_set_width(tl10, 7);
        lv_obj_set_height(tl10, 2);
        lv_obj_set_style_bg_color(tl10, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(tl10, 0, 0);
        lv_obj_set_style_border_width(tl10, 0, 0);
        lv_obj_set_style_pad_all(tl10, 0, 0);

        lv_obj_t * tr10 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tr10, "tr10");
        lv_obj_set_x(tr10, 225);
        lv_obj_set_y(tr10, 142);
        lv_obj_set_width(tr10, 7);
        lv_obj_set_height(tr10, 2);
        lv_obj_set_style_bg_color(tr10, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(tr10, 0, 0);
        lv_obj_set_style_border_width(tr10, 0, 0);
        lv_obj_set_style_pad_all(tr10, 0, 0);

        lv_obj_t * tl11 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tl11, "tl11");
        lv_obj_set_x(tl11, 8);
        lv_obj_set_y(tl11, 152);
        lv_obj_set_width(tl11, 7);
        lv_obj_set_height(tl11, 2);
        lv_obj_set_style_bg_color(tl11, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(tl11, 0, 0);
        lv_obj_set_style_border_width(tl11, 0, 0);
        lv_obj_set_style_pad_all(tl11, 0, 0);

        lv_obj_t * tr11 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tr11, "tr11");
        lv_obj_set_x(tr11, 225);
        lv_obj_set_y(tr11, 152);
        lv_obj_set_width(tr11, 7);
        lv_obj_set_height(tr11, 2);
        lv_obj_set_style_bg_color(tr11, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(tr11, 0, 0);
        lv_obj_set_style_border_width(tr11, 0, 0);
        lv_obj_set_style_pad_all(tr11, 0, 0);

        lv_obj_t * tl12 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tl12, "tl12");
        lv_obj_set_x(tl12, 8);
        lv_obj_set_y(tl12, 162);
        lv_obj_set_width(tl12, 14);
        lv_obj_set_height(tl12, 2);
        lv_obj_set_style_bg_color(tl12, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(tl12, 0, 0);
        lv_obj_set_style_border_width(tl12, 0, 0);
        lv_obj_set_style_pad_all(tl12, 0, 0);

        lv_obj_t * tr12 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tr12, "tr12");
        lv_obj_set_x(tr12, 218);
        lv_obj_set_y(tr12, 162);
        lv_obj_set_width(tr12, 14);
        lv_obj_set_height(tr12, 2);
        lv_obj_set_style_bg_color(tr12, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(tr12, 0, 0);
        lv_obj_set_style_border_width(tr12, 0, 0);
        lv_obj_set_style_pad_all(tr12, 0, 0);

        lv_obj_t * tl13 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tl13, "tl13");
        lv_obj_set_x(tl13, 8);
        lv_obj_set_y(tl13, 172);
        lv_obj_set_width(tl13, 7);
        lv_obj_set_height(tl13, 2);
        lv_obj_set_style_bg_color(tl13, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(tl13, 0, 0);
        lv_obj_set_style_border_width(tl13, 0, 0);
        lv_obj_set_style_pad_all(tl13, 0, 0);

        lv_obj_t * tr13 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tr13, "tr13");
        lv_obj_set_x(tr13, 225);
        lv_obj_set_y(tr13, 172);
        lv_obj_set_width(tr13, 7);
        lv_obj_set_height(tr13, 2);
        lv_obj_set_style_bg_color(tr13, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(tr13, 0, 0);
        lv_obj_set_style_border_width(tr13, 0, 0);
        lv_obj_set_style_pad_all(tr13, 0, 0);

        lv_obj_t * tl14 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tl14, "tl14");
        lv_obj_set_x(tl14, 8);
        lv_obj_set_y(tl14, 182);
        lv_obj_set_width(tl14, 7);
        lv_obj_set_height(tl14, 2);
        lv_obj_set_style_bg_color(tl14, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(tl14, 0, 0);
        lv_obj_set_style_border_width(tl14, 0, 0);
        lv_obj_set_style_pad_all(tl14, 0, 0);

        lv_obj_t * tr14 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tr14, "tr14");
        lv_obj_set_x(tr14, 225);
        lv_obj_set_y(tr14, 182);
        lv_obj_set_width(tr14, 7);
        lv_obj_set_height(tr14, 2);
        lv_obj_set_style_bg_color(tr14, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(tr14, 0, 0);
        lv_obj_set_style_border_width(tr14, 0, 0);
        lv_obj_set_style_pad_all(tr14, 0, 0);

        lv_obj_t * tl15 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tl15, "tl15");
        lv_obj_set_x(tl15, 8);
        lv_obj_set_y(tl15, 192);
        lv_obj_set_width(tl15, 7);
        lv_obj_set_height(tl15, 2);
        lv_obj_set_style_bg_color(tl15, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(tl15, 0, 0);
        lv_obj_set_style_border_width(tl15, 0, 0);
        lv_obj_set_style_pad_all(tl15, 0, 0);

        lv_obj_t * tr15 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tr15, "tr15");
        lv_obj_set_x(tr15, 225);
        lv_obj_set_y(tr15, 192);
        lv_obj_set_width(tr15, 7);
        lv_obj_set_height(tr15, 2);
        lv_obj_set_style_bg_color(tr15, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(tr15, 0, 0);
        lv_obj_set_style_border_width(tr15, 0, 0);
        lv_obj_set_style_pad_all(tr15, 0, 0);

        lv_obj_t * tl16 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tl16, "tl16");
        lv_obj_set_x(tl16, 8);
        lv_obj_set_y(tl16, 202);
        lv_obj_set_width(tl16, 7);
        lv_obj_set_height(tl16, 2);
        lv_obj_set_style_bg_color(tl16, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(tl16, 0, 0);
        lv_obj_set_style_border_width(tl16, 0, 0);
        lv_obj_set_style_pad_all(tl16, 0, 0);

        lv_obj_t * tr16 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tr16, "tr16");
        lv_obj_set_x(tr16, 225);
        lv_obj_set_y(tr16, 202);
        lv_obj_set_width(tr16, 7);
        lv_obj_set_height(tr16, 2);
        lv_obj_set_style_bg_color(tr16, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(tr16, 0, 0);
        lv_obj_set_style_border_width(tr16, 0, 0);
        lv_obj_set_style_pad_all(tr16, 0, 0);

        lv_obj_t * tl17 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tl17, "tl17");
        lv_obj_set_x(tl17, 8);
        lv_obj_set_y(tl17, 212);
        lv_obj_set_width(tl17, 7);
        lv_obj_set_height(tl17, 2);
        lv_obj_set_style_bg_color(tl17, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(tl17, 0, 0);
        lv_obj_set_style_border_width(tl17, 0, 0);
        lv_obj_set_style_pad_all(tl17, 0, 0);

        lv_obj_t * tr17 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tr17, "tr17");
        lv_obj_set_x(tr17, 225);
        lv_obj_set_y(tr17, 212);
        lv_obj_set_width(tr17, 7);
        lv_obj_set_height(tr17, 2);
        lv_obj_set_style_bg_color(tr17, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(tr17, 0, 0);
        lv_obj_set_style_border_width(tr17, 0, 0);
        lv_obj_set_style_pad_all(tr17, 0, 0);

        lv_obj_t * tl18 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tl18, "tl18");
        lv_obj_set_x(tl18, 8);
        lv_obj_set_y(tl18, 222);
        lv_obj_set_width(tl18, 14);
        lv_obj_set_height(tl18, 2);
        lv_obj_set_style_bg_color(tl18, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(tl18, 0, 0);
        lv_obj_set_style_border_width(tl18, 0, 0);
        lv_obj_set_style_pad_all(tl18, 0, 0);

        lv_obj_t * tr18 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tr18, "tr18");
        lv_obj_set_x(tr18, 218);
        lv_obj_set_y(tr18, 222);
        lv_obj_set_width(tr18, 14);
        lv_obj_set_height(tr18, 2);
        lv_obj_set_style_bg_color(tr18, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(tr18, 0, 0);
        lv_obj_set_style_border_width(tr18, 0, 0);
        lv_obj_set_style_pad_all(tr18, 0, 0);

        lv_obj_t * tl19 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tl19, "tl19");
        lv_obj_set_x(tl19, 8);
        lv_obj_set_y(tl19, 232);
        lv_obj_set_width(tl19, 7);
        lv_obj_set_height(tl19, 2);
        lv_obj_set_style_bg_color(tl19, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(tl19, 0, 0);
        lv_obj_set_style_border_width(tl19, 0, 0);
        lv_obj_set_style_pad_all(tl19, 0, 0);

        lv_obj_t * tr19 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tr19, "tr19");
        lv_obj_set_x(tr19, 225);
        lv_obj_set_y(tr19, 232);
        lv_obj_set_width(tr19, 7);
        lv_obj_set_height(tr19, 2);
        lv_obj_set_style_bg_color(tr19, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(tr19, 0, 0);
        lv_obj_set_style_border_width(tr19, 0, 0);
        lv_obj_set_style_pad_all(tr19, 0, 0);

        lv_obj_t * tl20 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tl20, "tl20");
        lv_obj_set_x(tl20, 8);
        lv_obj_set_y(tl20, 242);
        lv_obj_set_width(tl20, 7);
        lv_obj_set_height(tl20, 2);
        lv_obj_set_style_bg_color(tl20, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(tl20, 0, 0);
        lv_obj_set_style_border_width(tl20, 0, 0);
        lv_obj_set_style_pad_all(tl20, 0, 0);

        lv_obj_t * tr20 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tr20, "tr20");
        lv_obj_set_x(tr20, 225);
        lv_obj_set_y(tr20, 242);
        lv_obj_set_width(tr20, 7);
        lv_obj_set_height(tr20, 2);
        lv_obj_set_style_bg_color(tr20, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(tr20, 0, 0);
        lv_obj_set_style_border_width(tr20, 0, 0);
        lv_obj_set_style_pad_all(tr20, 0, 0);

        lv_obj_t * tl21 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tl21, "tl21");
        lv_obj_set_x(tl21, 8);
        lv_obj_set_y(tl21, 252);
        lv_obj_set_width(tl21, 7);
        lv_obj_set_height(tl21, 2);
        lv_obj_set_style_bg_color(tl21, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(tl21, 0, 0);
        lv_obj_set_style_border_width(tl21, 0, 0);
        lv_obj_set_style_pad_all(tl21, 0, 0);

        lv_obj_t * tr21 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tr21, "tr21");
        lv_obj_set_x(tr21, 225);
        lv_obj_set_y(tr21, 252);
        lv_obj_set_width(tr21, 7);
        lv_obj_set_height(tr21, 2);
        lv_obj_set_style_bg_color(tr21, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(tr21, 0, 0);
        lv_obj_set_style_border_width(tr21, 0, 0);
        lv_obj_set_style_pad_all(tr21, 0, 0);

        lv_obj_t * tl22 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tl22, "tl22");
        lv_obj_set_x(tl22, 8);
        lv_obj_set_y(tl22, 262);
        lv_obj_set_width(tl22, 7);
        lv_obj_set_height(tl22, 2);
        lv_obj_set_style_bg_color(tl22, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(tl22, 0, 0);
        lv_obj_set_style_border_width(tl22, 0, 0);
        lv_obj_set_style_pad_all(tl22, 0, 0);

        lv_obj_t * tr22 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tr22, "tr22");
        lv_obj_set_x(tr22, 225);
        lv_obj_set_y(tr22, 262);
        lv_obj_set_width(tr22, 7);
        lv_obj_set_height(tr22, 2);
        lv_obj_set_style_bg_color(tr22, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(tr22, 0, 0);
        lv_obj_set_style_border_width(tr22, 0, 0);
        lv_obj_set_style_pad_all(tr22, 0, 0);

        lv_obj_t * tl23 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tl23, "tl23");
        lv_obj_set_x(tl23, 8);
        lv_obj_set_y(tl23, 272);
        lv_obj_set_width(tl23, 7);
        lv_obj_set_height(tl23, 2);
        lv_obj_set_style_bg_color(tl23, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(tl23, 0, 0);
        lv_obj_set_style_border_width(tl23, 0, 0);
        lv_obj_set_style_pad_all(tl23, 0, 0);

        lv_obj_t * tr23 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(tr23, "tr23");
        lv_obj_set_x(tr23, 225);
        lv_obj_set_y(tr23, 272);
        lv_obj_set_width(tr23, 7);
        lv_obj_set_height(tr23, 2);
        lv_obj_set_style_bg_color(tr23, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(tr23, 0, 0);
        lv_obj_set_style_border_width(tr23, 0, 0);
        lv_obj_set_style_pad_all(tr23, 0, 0);

        lv_obj_t * hr_arc = lv_arc_create(lv_obj_0);
        lv_obj_set_name(hr_arc, "hr_arc");
        lv_obj_set_x(hr_arc, 34);
        lv_obj_set_y(hr_arc, 30);
        lv_obj_set_width(hr_arc, 56);
        lv_obj_set_height(hr_arc, 56);
        lv_arc_set_rotation(hr_arc, 0);
        lv_arc_set_bg_start_angle(hr_arc, 135);
        lv_arc_set_bg_end_angle(hr_arc, 45);
        lv_arc_set_value(hr_arc, 40);
        lv_obj_set_style_arc_width(hr_arc, 5, 0);
        lv_obj_set_style_arc_color(hr_arc, lv_color_hex(0x4A0B0B), 0);
        lv_obj_add_style(hr_arc, &wf_ind5, LV_PART_INDICATOR);
        lv_obj_add_style(hr_arc, &wf_knob_off, LV_PART_KNOB);

        lv_obj_t * hr_val = lv_label_create(lv_obj_0);
        lv_obj_set_name(hr_val, "hr_val");
        lv_obj_set_x(hr_val, 34);
        lv_obj_set_y(hr_val, 45);
        lv_obj_set_width(hr_val, 56);
        lv_label_set_text(hr_val, "78");
        lv_obj_set_style_text_color(hr_val, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_text_font(hr_val, font_h5, 0);
        lv_obj_set_style_text_align(hr_val, LV_TEXT_ALIGN_CENTER, 0);

        lv_obj_t * hr_sub = lv_label_create(lv_obj_0);
        lv_obj_set_name(hr_sub, "hr_sub");
        lv_obj_set_x(hr_sub, 34);
        lv_obj_set_y(hr_sub, 65);
        lv_obj_set_width(hr_sub, 56);
        lv_label_set_text(hr_sub, "bpm");
        lv_obj_set_style_text_color(hr_sub, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_text_font(hr_sub, font_body, 0);
        lv_obj_set_style_text_align(hr_sub, LV_TEXT_ALIGN_CENTER, 0);

        lv_obj_t * o2_arc = lv_arc_create(lv_obj_0);
        lv_obj_set_name(o2_arc, "o2_arc");
        lv_obj_set_x(o2_arc, 92);
        lv_obj_set_y(o2_arc, 30);
        lv_obj_set_width(o2_arc, 56);
        lv_obj_set_height(o2_arc, 56);
        lv_arc_set_rotation(o2_arc, 0);
        lv_arc_set_bg_start_angle(o2_arc, 135);
        lv_arc_set_bg_end_angle(o2_arc, 45);
        lv_arc_set_value(o2_arc, 80);
        lv_obj_set_style_arc_width(o2_arc, 5, 0);
        lv_obj_set_style_arc_color(o2_arc, lv_color_hex(0x4A0B0B), 0);
        lv_obj_add_style(o2_arc, &wf_ind5, LV_PART_INDICATOR);
        lv_obj_add_style(o2_arc, &wf_knob_off, LV_PART_KNOB);

        lv_obj_t * o2_val = lv_label_create(lv_obj_0);
        lv_obj_set_name(o2_val, "o2_val");
        lv_obj_set_x(o2_val, 92);
        lv_obj_set_y(o2_val, 45);
        lv_obj_set_width(o2_val, 56);
        lv_label_set_text(o2_val, "98");
        lv_obj_set_style_text_color(o2_val, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_text_font(o2_val, font_h5, 0);
        lv_obj_set_style_text_align(o2_val, LV_TEXT_ALIGN_CENTER, 0);

        lv_obj_t * o2_sub = lv_label_create(lv_obj_0);
        lv_obj_set_name(o2_sub, "o2_sub");
        lv_obj_set_x(o2_sub, 92);
        lv_obj_set_y(o2_sub, 65);
        lv_obj_set_width(o2_sub, 56);
        lv_label_set_text(o2_sub, "SpO2");
        lv_obj_set_style_text_color(o2_sub, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_text_font(o2_sub, font_body, 0);
        lv_obj_set_style_text_align(o2_sub, LV_TEXT_ALIGN_CENTER, 0);

        lv_obj_t * tmp_arc = lv_arc_create(lv_obj_0);
        lv_obj_set_name(tmp_arc, "tmp_arc");
        lv_obj_set_x(tmp_arc, 150);
        lv_obj_set_y(tmp_arc, 30);
        lv_obj_set_width(tmp_arc, 56);
        lv_obj_set_height(tmp_arc, 56);
        lv_arc_set_rotation(tmp_arc, 0);
        lv_arc_set_bg_start_angle(tmp_arc, 135);
        lv_arc_set_bg_end_angle(tmp_arc, 45);
        lv_arc_set_value(tmp_arc, 0);
        lv_obj_set_style_arc_width(tmp_arc, 5, 0);
        lv_obj_set_style_arc_color(tmp_arc, lv_color_hex(0x4A0B0B), 0);
        lv_obj_add_style(tmp_arc, &wf_ind5, LV_PART_INDICATOR);
        lv_obj_add_style(tmp_arc, &wf_knob_off, LV_PART_KNOB);

        lv_obj_t * tmp_val = lv_label_create(lv_obj_0);
        lv_obj_set_name(tmp_val, "tmp_val");
        lv_obj_set_x(tmp_val, 150);
        lv_obj_set_y(tmp_val, 45);
        lv_obj_set_width(tmp_val, 56);
        lv_label_set_text(tmp_val, "24");
        lv_obj_set_style_text_color(tmp_val, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_text_font(tmp_val, font_h5, 0);
        lv_obj_set_style_text_align(tmp_val, LV_TEXT_ALIGN_CENTER, 0);

        lv_obj_t * tmp_sub = lv_label_create(lv_obj_0);
        lv_obj_set_name(tmp_sub, "tmp_sub");
        lv_obj_set_x(tmp_sub, 150);
        lv_obj_set_y(tmp_sub, 65);
        lv_obj_set_width(tmp_sub, 56);
        lv_label_set_text(tmp_sub, "temp C");
        lv_obj_set_style_text_color(tmp_sub, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_text_font(tmp_sub, font_body, 0);
        lv_obj_set_style_text_align(tmp_sub, LV_TEXT_ALIGN_CENTER, 0);

        lv_obj_t * time = lv_label_create(lv_obj_0);
        lv_obj_set_name(time, "time");
        lv_obj_set_x(time, 20);
        lv_obj_set_y(time, 92);
        lv_obj_set_width(time, 200);
        lv_label_set_text(time, "09:41");
        lv_obj_set_style_text_color(time, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_text_font(time, font_h1, 0);
        lv_obj_set_style_text_align(time, LV_TEXT_ALIGN_CENTER, 0);

        lv_obj_t * date = lv_label_create(lv_obj_0);
        lv_obj_set_name(date, "date");
        lv_obj_set_x(date, 20);
        lv_obj_set_y(date, 150);
        lv_obj_set_width(date, 200);
        lv_label_set_text(date, "Fri 5 Nov");
        lv_obj_set_style_text_color(date, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_text_font(date, font_body, 0);
        lv_obj_set_style_text_align(date, LV_TEXT_ALIGN_CENTER, 0);

        lv_obj_t * rule0 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(rule0, "rule0");
        lv_obj_set_x(rule0, 34);
        lv_obj_set_y(rule0, 177);
        lv_obj_set_width(rule0, 2);
        lv_obj_set_height(rule0, 14);
        lv_obj_set_style_bg_color(rule0, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(rule0, 0, 0);
        lv_obj_set_style_border_width(rule0, 0, 0);
        lv_obj_set_style_pad_all(rule0, 0, 0);

        lv_obj_t * rule1 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(rule1, "rule1");
        lv_obj_set_x(rule1, 40);
        lv_obj_set_y(rule1, 180);
        lv_obj_set_width(rule1, 2);
        lv_obj_set_height(rule1, 8);
        lv_obj_set_style_bg_color(rule1, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(rule1, 0, 0);
        lv_obj_set_style_border_width(rule1, 0, 0);
        lv_obj_set_style_pad_all(rule1, 0, 0);

        lv_obj_t * rule2 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(rule2, "rule2");
        lv_obj_set_x(rule2, 46);
        lv_obj_set_y(rule2, 180);
        lv_obj_set_width(rule2, 2);
        lv_obj_set_height(rule2, 8);
        lv_obj_set_style_bg_color(rule2, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(rule2, 0, 0);
        lv_obj_set_style_border_width(rule2, 0, 0);
        lv_obj_set_style_pad_all(rule2, 0, 0);

        lv_obj_t * rule3 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(rule3, "rule3");
        lv_obj_set_x(rule3, 52);
        lv_obj_set_y(rule3, 180);
        lv_obj_set_width(rule3, 2);
        lv_obj_set_height(rule3, 8);
        lv_obj_set_style_bg_color(rule3, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(rule3, 0, 0);
        lv_obj_set_style_border_width(rule3, 0, 0);
        lv_obj_set_style_pad_all(rule3, 0, 0);

        lv_obj_t * rule4 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(rule4, "rule4");
        lv_obj_set_x(rule4, 58);
        lv_obj_set_y(rule4, 180);
        lv_obj_set_width(rule4, 2);
        lv_obj_set_height(rule4, 8);
        lv_obj_set_style_bg_color(rule4, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(rule4, 0, 0);
        lv_obj_set_style_border_width(rule4, 0, 0);
        lv_obj_set_style_pad_all(rule4, 0, 0);

        lv_obj_t * rule5 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(rule5, "rule5");
        lv_obj_set_x(rule5, 64);
        lv_obj_set_y(rule5, 177);
        lv_obj_set_width(rule5, 2);
        lv_obj_set_height(rule5, 14);
        lv_obj_set_style_bg_color(rule5, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(rule5, 0, 0);
        lv_obj_set_style_border_width(rule5, 0, 0);
        lv_obj_set_style_pad_all(rule5, 0, 0);

        lv_obj_t * rule6 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(rule6, "rule6");
        lv_obj_set_x(rule6, 70);
        lv_obj_set_y(rule6, 180);
        lv_obj_set_width(rule6, 2);
        lv_obj_set_height(rule6, 8);
        lv_obj_set_style_bg_color(rule6, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(rule6, 0, 0);
        lv_obj_set_style_border_width(rule6, 0, 0);
        lv_obj_set_style_pad_all(rule6, 0, 0);

        lv_obj_t * rule7 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(rule7, "rule7");
        lv_obj_set_x(rule7, 76);
        lv_obj_set_y(rule7, 180);
        lv_obj_set_width(rule7, 2);
        lv_obj_set_height(rule7, 8);
        lv_obj_set_style_bg_color(rule7, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(rule7, 0, 0);
        lv_obj_set_style_border_width(rule7, 0, 0);
        lv_obj_set_style_pad_all(rule7, 0, 0);

        lv_obj_t * rule8 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(rule8, "rule8");
        lv_obj_set_x(rule8, 82);
        lv_obj_set_y(rule8, 180);
        lv_obj_set_width(rule8, 2);
        lv_obj_set_height(rule8, 8);
        lv_obj_set_style_bg_color(rule8, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(rule8, 0, 0);
        lv_obj_set_style_border_width(rule8, 0, 0);
        lv_obj_set_style_pad_all(rule8, 0, 0);

        lv_obj_t * rule9 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(rule9, "rule9");
        lv_obj_set_x(rule9, 88);
        lv_obj_set_y(rule9, 180);
        lv_obj_set_width(rule9, 2);
        lv_obj_set_height(rule9, 8);
        lv_obj_set_style_bg_color(rule9, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(rule9, 0, 0);
        lv_obj_set_style_border_width(rule9, 0, 0);
        lv_obj_set_style_pad_all(rule9, 0, 0);

        lv_obj_t * rule10 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(rule10, "rule10");
        lv_obj_set_x(rule10, 94);
        lv_obj_set_y(rule10, 177);
        lv_obj_set_width(rule10, 2);
        lv_obj_set_height(rule10, 14);
        lv_obj_set_style_bg_color(rule10, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(rule10, 0, 0);
        lv_obj_set_style_border_width(rule10, 0, 0);
        lv_obj_set_style_pad_all(rule10, 0, 0);

        lv_obj_t * rule11 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(rule11, "rule11");
        lv_obj_set_x(rule11, 100);
        lv_obj_set_y(rule11, 180);
        lv_obj_set_width(rule11, 2);
        lv_obj_set_height(rule11, 8);
        lv_obj_set_style_bg_color(rule11, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(rule11, 0, 0);
        lv_obj_set_style_border_width(rule11, 0, 0);
        lv_obj_set_style_pad_all(rule11, 0, 0);

        lv_obj_t * rule12 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(rule12, "rule12");
        lv_obj_set_x(rule12, 106);
        lv_obj_set_y(rule12, 180);
        lv_obj_set_width(rule12, 2);
        lv_obj_set_height(rule12, 8);
        lv_obj_set_style_bg_color(rule12, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(rule12, 0, 0);
        lv_obj_set_style_border_width(rule12, 0, 0);
        lv_obj_set_style_pad_all(rule12, 0, 0);

        lv_obj_t * rule13 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(rule13, "rule13");
        lv_obj_set_x(rule13, 112);
        lv_obj_set_y(rule13, 180);
        lv_obj_set_width(rule13, 2);
        lv_obj_set_height(rule13, 8);
        lv_obj_set_style_bg_color(rule13, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(rule13, 0, 0);
        lv_obj_set_style_border_width(rule13, 0, 0);
        lv_obj_set_style_pad_all(rule13, 0, 0);

        lv_obj_t * rule14 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(rule14, "rule14");
        lv_obj_set_x(rule14, 118);
        lv_obj_set_y(rule14, 173);
        lv_obj_set_width(rule14, 2);
        lv_obj_set_height(rule14, 22);
        lv_obj_set_style_bg_color(rule14, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(rule14, 0, 0);
        lv_obj_set_style_border_width(rule14, 0, 0);
        lv_obj_set_style_pad_all(rule14, 0, 0);

        lv_obj_t * rule15 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(rule15, "rule15");
        lv_obj_set_x(rule15, 124);
        lv_obj_set_y(rule15, 177);
        lv_obj_set_width(rule15, 2);
        lv_obj_set_height(rule15, 14);
        lv_obj_set_style_bg_color(rule15, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(rule15, 0, 0);
        lv_obj_set_style_border_width(rule15, 0, 0);
        lv_obj_set_style_pad_all(rule15, 0, 0);

        lv_obj_t * rule16 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(rule16, "rule16");
        lv_obj_set_x(rule16, 130);
        lv_obj_set_y(rule16, 180);
        lv_obj_set_width(rule16, 2);
        lv_obj_set_height(rule16, 8);
        lv_obj_set_style_bg_color(rule16, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(rule16, 0, 0);
        lv_obj_set_style_border_width(rule16, 0, 0);
        lv_obj_set_style_pad_all(rule16, 0, 0);

        lv_obj_t * rule17 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(rule17, "rule17");
        lv_obj_set_x(rule17, 136);
        lv_obj_set_y(rule17, 180);
        lv_obj_set_width(rule17, 2);
        lv_obj_set_height(rule17, 8);
        lv_obj_set_style_bg_color(rule17, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(rule17, 0, 0);
        lv_obj_set_style_border_width(rule17, 0, 0);
        lv_obj_set_style_pad_all(rule17, 0, 0);

        lv_obj_t * rule18 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(rule18, "rule18");
        lv_obj_set_x(rule18, 142);
        lv_obj_set_y(rule18, 180);
        lv_obj_set_width(rule18, 2);
        lv_obj_set_height(rule18, 8);
        lv_obj_set_style_bg_color(rule18, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(rule18, 0, 0);
        lv_obj_set_style_border_width(rule18, 0, 0);
        lv_obj_set_style_pad_all(rule18, 0, 0);

        lv_obj_t * rule19 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(rule19, "rule19");
        lv_obj_set_x(rule19, 148);
        lv_obj_set_y(rule19, 180);
        lv_obj_set_width(rule19, 2);
        lv_obj_set_height(rule19, 8);
        lv_obj_set_style_bg_color(rule19, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(rule19, 0, 0);
        lv_obj_set_style_border_width(rule19, 0, 0);
        lv_obj_set_style_pad_all(rule19, 0, 0);

        lv_obj_t * rule20 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(rule20, "rule20");
        lv_obj_set_x(rule20, 154);
        lv_obj_set_y(rule20, 177);
        lv_obj_set_width(rule20, 2);
        lv_obj_set_height(rule20, 14);
        lv_obj_set_style_bg_color(rule20, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(rule20, 0, 0);
        lv_obj_set_style_border_width(rule20, 0, 0);
        lv_obj_set_style_pad_all(rule20, 0, 0);

        lv_obj_t * rule21 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(rule21, "rule21");
        lv_obj_set_x(rule21, 160);
        lv_obj_set_y(rule21, 180);
        lv_obj_set_width(rule21, 2);
        lv_obj_set_height(rule21, 8);
        lv_obj_set_style_bg_color(rule21, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(rule21, 0, 0);
        lv_obj_set_style_border_width(rule21, 0, 0);
        lv_obj_set_style_pad_all(rule21, 0, 0);

        lv_obj_t * rule22 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(rule22, "rule22");
        lv_obj_set_x(rule22, 166);
        lv_obj_set_y(rule22, 180);
        lv_obj_set_width(rule22, 2);
        lv_obj_set_height(rule22, 8);
        lv_obj_set_style_bg_color(rule22, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(rule22, 0, 0);
        lv_obj_set_style_border_width(rule22, 0, 0);
        lv_obj_set_style_pad_all(rule22, 0, 0);

        lv_obj_t * rule23 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(rule23, "rule23");
        lv_obj_set_x(rule23, 172);
        lv_obj_set_y(rule23, 180);
        lv_obj_set_width(rule23, 2);
        lv_obj_set_height(rule23, 8);
        lv_obj_set_style_bg_color(rule23, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(rule23, 0, 0);
        lv_obj_set_style_border_width(rule23, 0, 0);
        lv_obj_set_style_pad_all(rule23, 0, 0);

        lv_obj_t * rule24 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(rule24, "rule24");
        lv_obj_set_x(rule24, 178);
        lv_obj_set_y(rule24, 180);
        lv_obj_set_width(rule24, 2);
        lv_obj_set_height(rule24, 8);
        lv_obj_set_style_bg_color(rule24, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(rule24, 0, 0);
        lv_obj_set_style_border_width(rule24, 0, 0);
        lv_obj_set_style_pad_all(rule24, 0, 0);

        lv_obj_t * rule25 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(rule25, "rule25");
        lv_obj_set_x(rule25, 184);
        lv_obj_set_y(rule25, 177);
        lv_obj_set_width(rule25, 2);
        lv_obj_set_height(rule25, 14);
        lv_obj_set_style_bg_color(rule25, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(rule25, 0, 0);
        lv_obj_set_style_border_width(rule25, 0, 0);
        lv_obj_set_style_pad_all(rule25, 0, 0);

        lv_obj_t * rule26 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(rule26, "rule26");
        lv_obj_set_x(rule26, 190);
        lv_obj_set_y(rule26, 180);
        lv_obj_set_width(rule26, 2);
        lv_obj_set_height(rule26, 8);
        lv_obj_set_style_bg_color(rule26, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(rule26, 0, 0);
        lv_obj_set_style_border_width(rule26, 0, 0);
        lv_obj_set_style_pad_all(rule26, 0, 0);

        lv_obj_t * rule27 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(rule27, "rule27");
        lv_obj_set_x(rule27, 196);
        lv_obj_set_y(rule27, 180);
        lv_obj_set_width(rule27, 2);
        lv_obj_set_height(rule27, 8);
        lv_obj_set_style_bg_color(rule27, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(rule27, 0, 0);
        lv_obj_set_style_border_width(rule27, 0, 0);
        lv_obj_set_style_pad_all(rule27, 0, 0);

        lv_obj_t * rule28 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(rule28, "rule28");
        lv_obj_set_x(rule28, 202);
        lv_obj_set_y(rule28, 180);
        lv_obj_set_width(rule28, 2);
        lv_obj_set_height(rule28, 8);
        lv_obj_set_style_bg_color(rule28, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_radius(rule28, 0, 0);
        lv_obj_set_style_border_width(rule28, 0, 0);
        lv_obj_set_style_pad_all(rule28, 0, 0);

        lv_obj_t * dprev = lv_label_create(lv_obj_0);
        lv_obj_set_name(dprev, "dprev");
        lv_obj_set_x(dprev, 27);
        lv_obj_set_y(dprev, 204);
        lv_obj_set_width(dprev, 50);
        lv_label_set_text(dprev, "Thu");
        lv_obj_set_style_text_color(dprev, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_text_font(dprev, font_body, 0);
        lv_obj_set_style_text_align(dprev, LV_TEXT_ALIGN_CENTER, 0);

        lv_obj_t * dcur = lv_label_create(lv_obj_0);
        lv_obj_set_name(dcur, "dcur");
        lv_obj_set_x(dcur, 90);
        lv_obj_set_y(dcur, 201);
        lv_obj_set_width(dcur, 60);
        lv_label_set_text(dcur, "Fri");
        lv_obj_set_style_text_color(dcur, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_text_font(dcur, font_h5, 0);
        lv_obj_set_style_text_align(dcur, LV_TEXT_ALIGN_CENTER, 0);

        lv_obj_t * dnext = lv_label_create(lv_obj_0);
        lv_obj_set_name(dnext, "dnext");
        lv_obj_set_x(dnext, 163);
        lv_obj_set_y(dnext, 204);
        lv_obj_set_width(dnext, 50);
        lv_label_set_text(dnext, "Sat");
        lv_obj_set_style_text_color(dnext, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_text_font(dnext, font_body, 0);
        lv_obj_set_style_text_align(dnext, LV_TEXT_ALIGN_CENTER, 0);

        lv_obj_t * step_arc = lv_arc_create(lv_obj_0);
        lv_obj_set_name(step_arc, "step_arc");
        lv_obj_set_x(step_arc, 34);
        lv_obj_set_y(step_arc, 234);
        lv_obj_set_width(step_arc, 56);
        lv_obj_set_height(step_arc, 56);
        lv_arc_set_rotation(step_arc, 270);
        lv_arc_set_bg_start_angle(step_arc, 0);
        lv_arc_set_bg_end_angle(step_arc, 360);
        lv_arc_set_value(step_arc, 0);
        lv_obj_set_style_arc_width(step_arc, 7, 0);
        lv_obj_set_style_arc_color(step_arc, lv_color_hex(0x4A0B0B), 0);
        lv_obj_add_style(step_arc, &wf_ind7, LV_PART_INDICATOR);
        lv_obj_add_style(step_arc, &wf_knob_off, LV_PART_KNOB);

        lv_obj_t * step_lbl = lv_label_create(lv_obj_0);
        lv_obj_set_name(step_lbl, "step_lbl");
        lv_obj_set_x(step_lbl, 42);
        lv_obj_set_y(step_lbl, 254);
        lv_obj_set_width(step_lbl, 40);
        lv_label_set_text(step_lbl, "6.8k");
        lv_obj_set_style_text_color(step_lbl, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_text_font(step_lbl, font_body, 0);
        lv_obj_set_style_text_align(step_lbl, LV_TEXT_ALIGN_CENTER, 0);

        lv_obj_t * alarm_disc = lv_obj_create(lv_obj_0);
        lv_obj_set_name(alarm_disc, "alarm_disc");
        lv_obj_set_x(alarm_disc, 92);
        lv_obj_set_y(alarm_disc, 234);
        lv_obj_set_width(alarm_disc, 56);
        lv_obj_set_height(alarm_disc, 56);
        lv_obj_set_style_bg_color(alarm_disc, lv_color_hex(0x2A0606), 0);
        lv_obj_set_style_radius(alarm_disc, 28, 0);
        lv_obj_set_style_border_width(alarm_disc, 0, 0);
        lv_obj_set_style_pad_all(alarm_disc, 0, 0);

        lv_obj_t * alarm_cap = lv_label_create(lv_obj_0);
        lv_obj_set_name(alarm_cap, "alarm_cap");
        lv_obj_set_x(alarm_cap, 92);
        lv_obj_set_y(alarm_cap, 244);
        lv_obj_set_width(alarm_cap, 56);
        lv_label_set_text(alarm_cap, "ALARM");
        lv_obj_set_style_text_color(alarm_cap, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_text_font(alarm_cap, font_body, 0);
        lv_obj_set_style_text_align(alarm_cap, LV_TEXT_ALIGN_CENTER, 0);

        lv_obj_t * alarm = lv_label_create(lv_obj_0);
        lv_obj_set_name(alarm, "alarm");
        lv_obj_set_x(alarm, 92);
        lv_obj_set_y(alarm, 264);
        lv_obj_set_width(alarm, 56);
        lv_label_set_text(alarm, "06:30");
        lv_obj_set_style_text_color(alarm, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_text_font(alarm, font_body, 0);
        lv_obj_set_style_text_align(alarm, LV_TEXT_ALIGN_CENTER, 0);

        lv_obj_t * bat_arc = lv_arc_create(lv_obj_0);
        lv_obj_set_name(bat_arc, "bat_arc");
        lv_obj_set_x(bat_arc, 150);
        lv_obj_set_y(bat_arc, 234);
        lv_obj_set_width(bat_arc, 56);
        lv_obj_set_height(bat_arc, 56);
        lv_arc_set_rotation(bat_arc, 0);
        lv_arc_set_bg_start_angle(bat_arc, 135);
        lv_arc_set_bg_end_angle(bat_arc, 45);
        lv_arc_set_value(bat_arc, 0);
        lv_obj_set_style_arc_width(bat_arc, 5, 0);
        lv_obj_set_style_arc_color(bat_arc, lv_color_hex(0x4A0B0B), 0);
        lv_obj_add_style(bat_arc, &wf_ind5, LV_PART_INDICATOR);
        lv_obj_add_style(bat_arc, &wf_knob_off, LV_PART_KNOB);

        lv_obj_t * bat_val = lv_label_create(lv_obj_0);
        lv_obj_set_name(bat_val, "bat_val");
        lv_obj_set_x(bat_val, 150);
        lv_obj_set_y(bat_val, 249);
        lv_obj_set_width(bat_val, 56);
        lv_label_set_text(bat_val, "86");
        lv_obj_set_style_text_color(bat_val, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_text_font(bat_val, font_h5, 0);
        lv_obj_set_style_text_align(bat_val, LV_TEXT_ALIGN_CENTER, 0);

        lv_obj_t * bat_sub = lv_label_create(lv_obj_0);
        lv_obj_set_name(bat_sub, "bat_sub");
        lv_obj_set_x(bat_sub, 150);
        lv_obj_set_y(bat_sub, 269);
        lv_obj_set_width(bat_sub, 56);
        lv_label_set_text(bat_sub, "bat");
        lv_obj_set_style_text_color(bat_sub, lv_color_hex(0xFF2A2A), 0);
        lv_obj_set_style_text_font(bat_sub, font_body, 0);
        lv_obj_set_style_text_align(bat_sub, LV_TEXT_ALIGN_CENTER, 0);

        the_root = lv_obj_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

