/**
 * @file HomeEditorial_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "HomeEditorial_gen.h"
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

lv_obj_t * HomeEditorial_create(void)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if PULSEON_WATCH_UI_CHECK_COMPILE_TARGET(PULSEON_WATCH_UI_TARGET_ALL)
    if (PULSEON_WATCH_UI_check_target(PULSEON_WATCH_UI_TARGET_ALL)) {
        lv_obj_t * lv_obj_0 = lv_obj_create(NULL);
        lv_obj_set_name_static(lv_obj_0, "HomeEditorial_#");
        lv_obj_set_width(lv_obj_0, 240);
        lv_obj_set_height(lv_obj_0, 320);
        lv_obj_set_style_bg_color(lv_obj_0, lv_color_hex(0xECE6DA), 0);
        lv_obj_set_style_pad_all(lv_obj_0, 0, 0);
        lv_obj_set_style_border_width(lv_obj_0, 0, 0);

        lv_obj_t * date = lv_label_create(lv_obj_0);
        lv_obj_set_name(date, "date");
        lv_obj_set_x(date, 20);
        lv_obj_set_y(date, 14);
        lv_label_set_text(date, "FRI 5 NOV");
        lv_obj_set_style_text_color(date, lv_color_hex(0x15130F), 0);
        lv_obj_set_style_text_font(date, font_body, 0);

        lv_obj_t * link = lv_label_create(lv_obj_0);
        lv_obj_set_name(link, "link");
        lv_obj_set_x(link, -20);
        lv_obj_set_y(link, 14);
        lv_obj_set_align(link, LV_ALIGN_TOP_RIGHT);
        lv_label_set_text(link, "LINK");
        lv_obj_set_style_text_color(link, lv_color_hex(0x15130F), 0);
        lv_obj_set_style_text_font(link, font_body, 0);

        lv_obj_t * rule_top = lv_obj_create(lv_obj_0);
        lv_obj_set_name(rule_top, "rule_top");
        lv_obj_set_x(rule_top, 20);
        lv_obj_set_y(rule_top, 36);
        lv_obj_set_width(rule_top, 200);
        lv_obj_set_height(rule_top, 1);
        lv_obj_set_style_bg_color(rule_top, lv_color_hex(0x15130F), 0);
        lv_obj_set_style_radius(rule_top, 0, 0);
        lv_obj_set_style_border_width(rule_top, 0, 0);
        lv_obj_set_style_pad_all(rule_top, 0, 0);

        lv_obj_t * h0_seg0 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(h0_seg0, "h0_seg0");
        lv_obj_set_x(h0_seg0, 32);
        lv_obj_set_y(h0_seg0, 50);
        lv_obj_set_width(h0_seg0, 32);
        lv_obj_set_height(h0_seg0, 12);
        lv_obj_set_style_bg_color(h0_seg0, lv_color_hex(0x15130F), 0);
        lv_obj_set_style_radius(h0_seg0, 6, 0);
        lv_obj_set_style_border_width(h0_seg0, 0, 0);
        lv_obj_set_style_pad_all(h0_seg0, 0, 0);

        lv_obj_t * h0_seg1 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(h0_seg1, "h0_seg1");
        lv_obj_set_x(h0_seg1, 64);
        lv_obj_set_y(h0_seg1, 56);
        lv_obj_set_width(h0_seg1, 12);
        lv_obj_set_height(h0_seg1, 42);
        lv_obj_set_style_bg_color(h0_seg1, lv_color_hex(0x15130F), 0);
        lv_obj_set_style_radius(h0_seg1, 6, 0);
        lv_obj_set_style_border_width(h0_seg1, 0, 0);
        lv_obj_set_style_pad_all(h0_seg1, 0, 0);

        lv_obj_t * h0_seg2 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(h0_seg2, "h0_seg2");
        lv_obj_set_x(h0_seg2, 64);
        lv_obj_set_y(h0_seg2, 98);
        lv_obj_set_width(h0_seg2, 12);
        lv_obj_set_height(h0_seg2, 42);
        lv_obj_set_style_bg_color(h0_seg2, lv_color_hex(0x15130F), 0);
        lv_obj_set_style_radius(h0_seg2, 6, 0);
        lv_obj_set_style_border_width(h0_seg2, 0, 0);
        lv_obj_set_style_pad_all(h0_seg2, 0, 0);

        lv_obj_t * h0_seg3 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(h0_seg3, "h0_seg3");
        lv_obj_set_x(h0_seg3, 32);
        lv_obj_set_y(h0_seg3, 134);
        lv_obj_set_width(h0_seg3, 32);
        lv_obj_set_height(h0_seg3, 12);
        lv_obj_set_style_bg_color(h0_seg3, lv_color_hex(0x15130F), 0);
        lv_obj_set_style_radius(h0_seg3, 6, 0);
        lv_obj_set_style_border_width(h0_seg3, 0, 0);
        lv_obj_set_style_pad_all(h0_seg3, 0, 0);

        lv_obj_t * h0_seg4 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(h0_seg4, "h0_seg4");
        lv_obj_set_x(h0_seg4, 20);
        lv_obj_set_y(h0_seg4, 98);
        lv_obj_set_width(h0_seg4, 12);
        lv_obj_set_height(h0_seg4, 42);
        lv_obj_set_style_bg_color(h0_seg4, lv_color_hex(0x15130F), 0);
        lv_obj_set_style_radius(h0_seg4, 6, 0);
        lv_obj_set_style_border_width(h0_seg4, 0, 0);
        lv_obj_set_style_pad_all(h0_seg4, 0, 0);

        lv_obj_t * h0_seg5 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(h0_seg5, "h0_seg5");
        lv_obj_set_x(h0_seg5, 20);
        lv_obj_set_y(h0_seg5, 56);
        lv_obj_set_width(h0_seg5, 12);
        lv_obj_set_height(h0_seg5, 42);
        lv_obj_set_style_bg_color(h0_seg5, lv_color_hex(0x15130F), 0);
        lv_obj_set_style_radius(h0_seg5, 6, 0);
        lv_obj_set_style_border_width(h0_seg5, 0, 0);
        lv_obj_set_style_pad_all(h0_seg5, 0, 0);

        lv_obj_t * h0_seg6 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(h0_seg6, "h0_seg6");
        lv_obj_set_x(h0_seg6, 32);
        lv_obj_set_y(h0_seg6, 92);
        lv_obj_set_width(h0_seg6, 32);
        lv_obj_set_height(h0_seg6, 12);
        lv_obj_set_style_bg_color(h0_seg6, lv_color_hex(0x15130F), 0);
        lv_obj_set_style_radius(h0_seg6, 6, 0);
        lv_obj_set_style_border_width(h0_seg6, 0, 0);
        lv_obj_set_style_pad_all(h0_seg6, 0, 0);
        lv_obj_set_style_bg_opa(h0_seg6, (255 * 0 / 100), 0);

        lv_obj_t * h1_seg0 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(h1_seg0, "h1_seg0");
        lv_obj_set_x(h1_seg0, 100);
        lv_obj_set_y(h1_seg0, 50);
        lv_obj_set_width(h1_seg0, 32);
        lv_obj_set_height(h1_seg0, 12);
        lv_obj_set_style_bg_color(h1_seg0, lv_color_hex(0x15130F), 0);
        lv_obj_set_style_radius(h1_seg0, 6, 0);
        lv_obj_set_style_border_width(h1_seg0, 0, 0);
        lv_obj_set_style_pad_all(h1_seg0, 0, 0);

        lv_obj_t * h1_seg1 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(h1_seg1, "h1_seg1");
        lv_obj_set_x(h1_seg1, 132);
        lv_obj_set_y(h1_seg1, 56);
        lv_obj_set_width(h1_seg1, 12);
        lv_obj_set_height(h1_seg1, 42);
        lv_obj_set_style_bg_color(h1_seg1, lv_color_hex(0x15130F), 0);
        lv_obj_set_style_radius(h1_seg1, 6, 0);
        lv_obj_set_style_border_width(h1_seg1, 0, 0);
        lv_obj_set_style_pad_all(h1_seg1, 0, 0);

        lv_obj_t * h1_seg2 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(h1_seg2, "h1_seg2");
        lv_obj_set_x(h1_seg2, 132);
        lv_obj_set_y(h1_seg2, 98);
        lv_obj_set_width(h1_seg2, 12);
        lv_obj_set_height(h1_seg2, 42);
        lv_obj_set_style_bg_color(h1_seg2, lv_color_hex(0x15130F), 0);
        lv_obj_set_style_radius(h1_seg2, 6, 0);
        lv_obj_set_style_border_width(h1_seg2, 0, 0);
        lv_obj_set_style_pad_all(h1_seg2, 0, 0);

        lv_obj_t * h1_seg3 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(h1_seg3, "h1_seg3");
        lv_obj_set_x(h1_seg3, 100);
        lv_obj_set_y(h1_seg3, 134);
        lv_obj_set_width(h1_seg3, 32);
        lv_obj_set_height(h1_seg3, 12);
        lv_obj_set_style_bg_color(h1_seg3, lv_color_hex(0x15130F), 0);
        lv_obj_set_style_radius(h1_seg3, 6, 0);
        lv_obj_set_style_border_width(h1_seg3, 0, 0);
        lv_obj_set_style_pad_all(h1_seg3, 0, 0);

        lv_obj_t * h1_seg4 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(h1_seg4, "h1_seg4");
        lv_obj_set_x(h1_seg4, 88);
        lv_obj_set_y(h1_seg4, 98);
        lv_obj_set_width(h1_seg4, 12);
        lv_obj_set_height(h1_seg4, 42);
        lv_obj_set_style_bg_color(h1_seg4, lv_color_hex(0x15130F), 0);
        lv_obj_set_style_radius(h1_seg4, 6, 0);
        lv_obj_set_style_border_width(h1_seg4, 0, 0);
        lv_obj_set_style_pad_all(h1_seg4, 0, 0);
        lv_obj_set_style_bg_opa(h1_seg4, (255 * 0 / 100), 0);

        lv_obj_t * h1_seg5 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(h1_seg5, "h1_seg5");
        lv_obj_set_x(h1_seg5, 88);
        lv_obj_set_y(h1_seg5, 56);
        lv_obj_set_width(h1_seg5, 12);
        lv_obj_set_height(h1_seg5, 42);
        lv_obj_set_style_bg_color(h1_seg5, lv_color_hex(0x15130F), 0);
        lv_obj_set_style_radius(h1_seg5, 6, 0);
        lv_obj_set_style_border_width(h1_seg5, 0, 0);
        lv_obj_set_style_pad_all(h1_seg5, 0, 0);

        lv_obj_t * h1_seg6 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(h1_seg6, "h1_seg6");
        lv_obj_set_x(h1_seg6, 100);
        lv_obj_set_y(h1_seg6, 92);
        lv_obj_set_width(h1_seg6, 32);
        lv_obj_set_height(h1_seg6, 12);
        lv_obj_set_style_bg_color(h1_seg6, lv_color_hex(0x15130F), 0);
        lv_obj_set_style_radius(h1_seg6, 6, 0);
        lv_obj_set_style_border_width(h1_seg6, 0, 0);
        lv_obj_set_style_pad_all(h1_seg6, 0, 0);

        lv_obj_t * m0_seg0 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(m0_seg0, "m0_seg0");
        lv_obj_set_x(m0_seg0, 32);
        lv_obj_set_y(m0_seg0, 156);
        lv_obj_set_width(m0_seg0, 32);
        lv_obj_set_height(m0_seg0, 12);
        lv_obj_set_style_bg_color(m0_seg0, lv_color_hex(0xE5484D), 0);
        lv_obj_set_style_radius(m0_seg0, 6, 0);
        lv_obj_set_style_border_width(m0_seg0, 0, 0);
        lv_obj_set_style_pad_all(m0_seg0, 0, 0);
        lv_obj_set_style_bg_opa(m0_seg0, (255 * 0 / 100), 0);

        lv_obj_t * m0_seg1 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(m0_seg1, "m0_seg1");
        lv_obj_set_x(m0_seg1, 64);
        lv_obj_set_y(m0_seg1, 162);
        lv_obj_set_width(m0_seg1, 12);
        lv_obj_set_height(m0_seg1, 42);
        lv_obj_set_style_bg_color(m0_seg1, lv_color_hex(0xE5484D), 0);
        lv_obj_set_style_radius(m0_seg1, 6, 0);
        lv_obj_set_style_border_width(m0_seg1, 0, 0);
        lv_obj_set_style_pad_all(m0_seg1, 0, 0);

        lv_obj_t * m0_seg2 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(m0_seg2, "m0_seg2");
        lv_obj_set_x(m0_seg2, 64);
        lv_obj_set_y(m0_seg2, 204);
        lv_obj_set_width(m0_seg2, 12);
        lv_obj_set_height(m0_seg2, 42);
        lv_obj_set_style_bg_color(m0_seg2, lv_color_hex(0xE5484D), 0);
        lv_obj_set_style_radius(m0_seg2, 6, 0);
        lv_obj_set_style_border_width(m0_seg2, 0, 0);
        lv_obj_set_style_pad_all(m0_seg2, 0, 0);

        lv_obj_t * m0_seg3 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(m0_seg3, "m0_seg3");
        lv_obj_set_x(m0_seg3, 32);
        lv_obj_set_y(m0_seg3, 240);
        lv_obj_set_width(m0_seg3, 32);
        lv_obj_set_height(m0_seg3, 12);
        lv_obj_set_style_bg_color(m0_seg3, lv_color_hex(0xE5484D), 0);
        lv_obj_set_style_radius(m0_seg3, 6, 0);
        lv_obj_set_style_border_width(m0_seg3, 0, 0);
        lv_obj_set_style_pad_all(m0_seg3, 0, 0);
        lv_obj_set_style_bg_opa(m0_seg3, (255 * 0 / 100), 0);

        lv_obj_t * m0_seg4 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(m0_seg4, "m0_seg4");
        lv_obj_set_x(m0_seg4, 20);
        lv_obj_set_y(m0_seg4, 204);
        lv_obj_set_width(m0_seg4, 12);
        lv_obj_set_height(m0_seg4, 42);
        lv_obj_set_style_bg_color(m0_seg4, lv_color_hex(0xE5484D), 0);
        lv_obj_set_style_radius(m0_seg4, 6, 0);
        lv_obj_set_style_border_width(m0_seg4, 0, 0);
        lv_obj_set_style_pad_all(m0_seg4, 0, 0);
        lv_obj_set_style_bg_opa(m0_seg4, (255 * 0 / 100), 0);

        lv_obj_t * m0_seg5 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(m0_seg5, "m0_seg5");
        lv_obj_set_x(m0_seg5, 20);
        lv_obj_set_y(m0_seg5, 162);
        lv_obj_set_width(m0_seg5, 12);
        lv_obj_set_height(m0_seg5, 42);
        lv_obj_set_style_bg_color(m0_seg5, lv_color_hex(0xE5484D), 0);
        lv_obj_set_style_radius(m0_seg5, 6, 0);
        lv_obj_set_style_border_width(m0_seg5, 0, 0);
        lv_obj_set_style_pad_all(m0_seg5, 0, 0);

        lv_obj_t * m0_seg6 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(m0_seg6, "m0_seg6");
        lv_obj_set_x(m0_seg6, 32);
        lv_obj_set_y(m0_seg6, 198);
        lv_obj_set_width(m0_seg6, 32);
        lv_obj_set_height(m0_seg6, 12);
        lv_obj_set_style_bg_color(m0_seg6, lv_color_hex(0xE5484D), 0);
        lv_obj_set_style_radius(m0_seg6, 6, 0);
        lv_obj_set_style_border_width(m0_seg6, 0, 0);
        lv_obj_set_style_pad_all(m0_seg6, 0, 0);

        lv_obj_t * m1_seg0 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(m1_seg0, "m1_seg0");
        lv_obj_set_x(m1_seg0, 100);
        lv_obj_set_y(m1_seg0, 156);
        lv_obj_set_width(m1_seg0, 32);
        lv_obj_set_height(m1_seg0, 12);
        lv_obj_set_style_bg_color(m1_seg0, lv_color_hex(0xE5484D), 0);
        lv_obj_set_style_radius(m1_seg0, 6, 0);
        lv_obj_set_style_border_width(m1_seg0, 0, 0);
        lv_obj_set_style_pad_all(m1_seg0, 0, 0);
        lv_obj_set_style_bg_opa(m1_seg0, (255 * 0 / 100), 0);

        lv_obj_t * m1_seg1 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(m1_seg1, "m1_seg1");
        lv_obj_set_x(m1_seg1, 132);
        lv_obj_set_y(m1_seg1, 162);
        lv_obj_set_width(m1_seg1, 12);
        lv_obj_set_height(m1_seg1, 42);
        lv_obj_set_style_bg_color(m1_seg1, lv_color_hex(0xE5484D), 0);
        lv_obj_set_style_radius(m1_seg1, 6, 0);
        lv_obj_set_style_border_width(m1_seg1, 0, 0);
        lv_obj_set_style_pad_all(m1_seg1, 0, 0);

        lv_obj_t * m1_seg2 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(m1_seg2, "m1_seg2");
        lv_obj_set_x(m1_seg2, 132);
        lv_obj_set_y(m1_seg2, 204);
        lv_obj_set_width(m1_seg2, 12);
        lv_obj_set_height(m1_seg2, 42);
        lv_obj_set_style_bg_color(m1_seg2, lv_color_hex(0xE5484D), 0);
        lv_obj_set_style_radius(m1_seg2, 6, 0);
        lv_obj_set_style_border_width(m1_seg2, 0, 0);
        lv_obj_set_style_pad_all(m1_seg2, 0, 0);

        lv_obj_t * m1_seg3 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(m1_seg3, "m1_seg3");
        lv_obj_set_x(m1_seg3, 100);
        lv_obj_set_y(m1_seg3, 240);
        lv_obj_set_width(m1_seg3, 32);
        lv_obj_set_height(m1_seg3, 12);
        lv_obj_set_style_bg_color(m1_seg3, lv_color_hex(0xE5484D), 0);
        lv_obj_set_style_radius(m1_seg3, 6, 0);
        lv_obj_set_style_border_width(m1_seg3, 0, 0);
        lv_obj_set_style_pad_all(m1_seg3, 0, 0);
        lv_obj_set_style_bg_opa(m1_seg3, (255 * 0 / 100), 0);

        lv_obj_t * m1_seg4 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(m1_seg4, "m1_seg4");
        lv_obj_set_x(m1_seg4, 88);
        lv_obj_set_y(m1_seg4, 204);
        lv_obj_set_width(m1_seg4, 12);
        lv_obj_set_height(m1_seg4, 42);
        lv_obj_set_style_bg_color(m1_seg4, lv_color_hex(0xE5484D), 0);
        lv_obj_set_style_radius(m1_seg4, 6, 0);
        lv_obj_set_style_border_width(m1_seg4, 0, 0);
        lv_obj_set_style_pad_all(m1_seg4, 0, 0);
        lv_obj_set_style_bg_opa(m1_seg4, (255 * 0 / 100), 0);

        lv_obj_t * m1_seg5 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(m1_seg5, "m1_seg5");
        lv_obj_set_x(m1_seg5, 88);
        lv_obj_set_y(m1_seg5, 162);
        lv_obj_set_width(m1_seg5, 12);
        lv_obj_set_height(m1_seg5, 42);
        lv_obj_set_style_bg_color(m1_seg5, lv_color_hex(0xE5484D), 0);
        lv_obj_set_style_radius(m1_seg5, 6, 0);
        lv_obj_set_style_border_width(m1_seg5, 0, 0);
        lv_obj_set_style_pad_all(m1_seg5, 0, 0);
        lv_obj_set_style_bg_opa(m1_seg5, (255 * 0 / 100), 0);

        lv_obj_t * m1_seg6 = lv_obj_create(lv_obj_0);
        lv_obj_set_name(m1_seg6, "m1_seg6");
        lv_obj_set_x(m1_seg6, 100);
        lv_obj_set_y(m1_seg6, 198);
        lv_obj_set_width(m1_seg6, 32);
        lv_obj_set_height(m1_seg6, 12);
        lv_obj_set_style_bg_color(m1_seg6, lv_color_hex(0xE5484D), 0);
        lv_obj_set_style_radius(m1_seg6, 6, 0);
        lv_obj_set_style_border_width(m1_seg6, 0, 0);
        lv_obj_set_style_pad_all(m1_seg6, 0, 0);
        lv_obj_set_style_bg_opa(m1_seg6, (255 * 0 / 100), 0);

        lv_obj_t * wd = lv_label_create(lv_obj_0);
        lv_obj_set_name(wd, "wd");
        lv_obj_set_x(wd, 164);
        lv_obj_set_y(wd, 56);
        lv_label_set_text(wd, "FRI");
        lv_obj_set_style_text_color(wd, lv_color_hex(0x15130F), 0);
        lv_obj_set_style_text_font(wd, font_h5, 0);

        lv_obj_t * dd = lv_label_create(lv_obj_0);
        lv_obj_set_name(dd, "dd");
        lv_obj_set_x(dd, 164);
        lv_obj_set_y(dd, 80);
        lv_label_set_text(dd, "5");
        lv_obj_set_style_text_color(dd, lv_color_hex(0x15130F), 0);
        lv_obj_set_style_text_font(dd, font_h1, 0);

        lv_obj_t * mon = lv_label_create(lv_obj_0);
        lv_obj_set_name(mon, "mon");
        lv_obj_set_x(mon, 164);
        lv_obj_set_y(mon, 140);
        lv_label_set_text(mon, "NOV");
        lv_obj_set_style_text_color(mon, lv_color_hex(0xE5484D), 0);
        lv_obj_set_style_text_font(mon, font_h5, 0);

        lv_obj_t * rule_bottom = lv_obj_create(lv_obj_0);
        lv_obj_set_name(rule_bottom, "rule_bottom");
        lv_obj_set_x(rule_bottom, 20);
        lv_obj_set_y(rule_bottom, 262);
        lv_obj_set_width(rule_bottom, 200);
        lv_obj_set_height(rule_bottom, 1);
        lv_obj_set_style_bg_color(rule_bottom, lv_color_hex(0x15130F), 0);
        lv_obj_set_style_radius(rule_bottom, 0, 0);
        lv_obj_set_style_border_width(rule_bottom, 0, 0);
        lv_obj_set_style_pad_all(rule_bottom, 0, 0);

        lv_obj_t * hr_cap = lv_label_create(lv_obj_0);
        lv_obj_set_name(hr_cap, "hr_cap");
        lv_obj_set_x(hr_cap, 20);
        lv_obj_set_y(hr_cap, 268);
        lv_label_set_text(hr_cap, "HEART");
        lv_obj_set_style_text_color(hr_cap, lv_color_hex(0x15130F), 0);
        lv_obj_set_style_text_font(hr_cap, font_body, 0);

        lv_obj_t * hr = lv_label_create(lv_obj_0);
        lv_obj_set_name(hr, "hr");
        lv_obj_set_x(hr, 20);
        lv_obj_set_y(hr, 286);
        lv_label_set_text(hr, "78");
        lv_obj_set_style_text_color(hr, lv_color_hex(0x15130F), 0);
        lv_obj_set_style_text_font(hr, font_h5, 0);

        lv_obj_t * steps_cap = lv_label_create(lv_obj_0);
        lv_obj_set_name(steps_cap, "steps_cap");
        lv_obj_set_x(steps_cap, 90);
        lv_obj_set_y(steps_cap, 268);
        lv_label_set_text(steps_cap, "STEPS");
        lv_obj_set_style_text_color(steps_cap, lv_color_hex(0x15130F), 0);
        lv_obj_set_style_text_font(steps_cap, font_body, 0);

        lv_obj_t * steps = lv_label_create(lv_obj_0);
        lv_obj_set_name(steps, "steps");
        lv_obj_set_x(steps, 90);
        lv_obj_set_y(steps, 286);
        lv_label_set_text(steps, "6842");
        lv_obj_set_style_text_color(steps, lv_color_hex(0x15130F), 0);
        lv_obj_set_style_text_font(steps, font_h5, 0);

        lv_obj_t * bat_cap = lv_label_create(lv_obj_0);
        lv_obj_set_name(bat_cap, "bat_cap");
        lv_obj_set_x(bat_cap, 160);
        lv_obj_set_y(bat_cap, 268);
        lv_label_set_text(bat_cap, "PHONE");
        lv_obj_set_style_text_color(bat_cap, lv_color_hex(0x15130F), 0);
        lv_obj_set_style_text_font(bat_cap, font_body, 0);

        lv_obj_t * bat = lv_label_create(lv_obj_0);
        lv_obj_set_name(bat, "bat");
        lv_obj_set_x(bat, 160);
        lv_obj_set_y(bat, 286);
        lv_label_set_text(bat, "86%");
        lv_obj_set_style_text_color(bat, lv_color_hex(0x15130F), 0);
        lv_obj_set_style_text_font(bat, font_h5, 0);

        the_root = lv_obj_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

