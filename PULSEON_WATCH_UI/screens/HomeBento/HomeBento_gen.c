/**
 * @file HomeBento_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "HomeBento_gen.h"
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

lv_obj_t * HomeBento_create(void)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if PULSEON_WATCH_UI_CHECK_COMPILE_TARGET(PULSEON_WATCH_UI_TARGET_ALL)
    if (PULSEON_WATCH_UI_check_target(PULSEON_WATCH_UI_TARGET_ALL)) {
        lv_obj_t * lv_obj_0 = lv_obj_create(NULL);
        lv_obj_set_name_static(lv_obj_0, "HomeBento_#");
        lv_obj_set_width(lv_obj_0, 240);
        lv_obj_set_height(lv_obj_0, 320);
        lv_obj_set_style_bg_color(lv_obj_0, lv_color_hex(0x0E0E12), 0);
        lv_obj_set_style_pad_all(lv_obj_0, 0, 0);
        lv_obj_set_style_border_width(lv_obj_0, 0, 0);

        lv_obj_t * time_tile = lv_obj_create(lv_obj_0);
        lv_obj_set_name(time_tile, "time_tile");
        lv_obj_set_x(time_tile, 8);
        lv_obj_set_y(time_tile, 8);
        lv_obj_set_width(time_tile, 224);
        lv_obj_set_height(time_tile, 96);
        lv_obj_set_style_bg_color(time_tile, lv_color_hex(0xFF7A59), 0);
        lv_obj_set_style_radius(time_tile, 20, 0);
        lv_obj_set_style_border_width(time_tile, 0, 0);
        lv_obj_set_style_pad_all(time_tile, 0, 0);

        lv_obj_t * date = lv_label_create(lv_obj_0);
        lv_obj_set_name(date, "date");
        lv_obj_set_x(date, 20);
        lv_obj_set_y(date, 16);
        lv_label_set_text(date, "FRI 5 NOV");
        lv_obj_set_style_text_color(date, lv_color_hex(0x101014), 0);
        lv_obj_set_style_text_font(date, font_body, 0);

        lv_obj_t * time = lv_label_create(lv_obj_0);
        lv_obj_set_name(time, "time");
        lv_obj_set_x(time, 20);
        lv_obj_set_y(time, 38);
        lv_label_set_text(time, "09:41");
        lv_obj_set_style_text_color(time, lv_color_hex(0x101014), 0);
        lv_obj_set_style_text_font(time, font_h1, 0);

        lv_obj_t * hr_tile = lv_obj_create(lv_obj_0);
        lv_obj_set_name(hr_tile, "hr_tile");
        lv_obj_set_x(hr_tile, 8);
        lv_obj_set_y(hr_tile, 112);
        lv_obj_set_width(hr_tile, 108);
        lv_obj_set_height(hr_tile, 70);
        lv_obj_set_style_bg_color(hr_tile, lv_color_hex(0xFFC857), 0);
        lv_obj_set_style_radius(hr_tile, 20, 0);
        lv_obj_set_style_border_width(hr_tile, 0, 0);
        lv_obj_set_style_pad_all(hr_tile, 0, 0);

        lv_obj_t * hr_cap = lv_label_create(lv_obj_0);
        lv_obj_set_name(hr_cap, "hr_cap");
        lv_obj_set_x(hr_cap, 20);
        lv_obj_set_y(hr_cap, 120);
        lv_label_set_text(hr_cap, "HEART");
        lv_obj_set_style_text_color(hr_cap, lv_color_hex(0x101014), 0);
        lv_obj_set_style_text_font(hr_cap, font_body, 0);

        lv_obj_t * hr = lv_label_create(lv_obj_0);
        lv_obj_set_name(hr, "hr");
        lv_obj_set_x(hr, 20);
        lv_obj_set_y(hr, 138);
        lv_label_set_text(hr, "78");
        lv_obj_set_style_text_color(hr, lv_color_hex(0x101014), 0);
        lv_obj_set_style_text_font(hr, font_h4, 0);

        lv_obj_t * steps_tile = lv_obj_create(lv_obj_0);
        lv_obj_set_name(steps_tile, "steps_tile");
        lv_obj_set_x(steps_tile, 124);
        lv_obj_set_y(steps_tile, 112);
        lv_obj_set_width(steps_tile, 108);
        lv_obj_set_height(steps_tile, 70);
        lv_obj_set_style_bg_color(steps_tile, lv_color_hex(0x6FD3A6), 0);
        lv_obj_set_style_radius(steps_tile, 20, 0);
        lv_obj_set_style_border_width(steps_tile, 0, 0);
        lv_obj_set_style_pad_all(steps_tile, 0, 0);

        lv_obj_t * steps_cap = lv_label_create(lv_obj_0);
        lv_obj_set_name(steps_cap, "steps_cap");
        lv_obj_set_x(steps_cap, 136);
        lv_obj_set_y(steps_cap, 120);
        lv_label_set_text(steps_cap, "STEPS");
        lv_obj_set_style_text_color(steps_cap, lv_color_hex(0x101014), 0);
        lv_obj_set_style_text_font(steps_cap, font_body, 0);

        lv_obj_t * steps = lv_label_create(lv_obj_0);
        lv_obj_set_name(steps, "steps");
        lv_obj_set_x(steps, 136);
        lv_obj_set_y(steps, 138);
        lv_label_set_text(steps, "6842");
        lv_obj_set_style_text_color(steps, lv_color_hex(0x101014), 0);
        lv_obj_set_style_text_font(steps, font_h4, 0);

        lv_obj_t * bat_tile = lv_obj_create(lv_obj_0);
        lv_obj_set_name(bat_tile, "bat_tile");
        lv_obj_set_x(bat_tile, 8);
        lv_obj_set_y(bat_tile, 190);
        lv_obj_set_width(bat_tile, 108);
        lv_obj_set_height(bat_tile, 56);
        lv_obj_set_style_bg_color(bat_tile, lv_color_hex(0x7AA2FF), 0);
        lv_obj_set_style_radius(bat_tile, 20, 0);
        lv_obj_set_style_border_width(bat_tile, 0, 0);
        lv_obj_set_style_pad_all(bat_tile, 0, 0);

        lv_obj_t * bat_cap = lv_label_create(lv_obj_0);
        lv_obj_set_name(bat_cap, "bat_cap");
        lv_obj_set_x(bat_cap, 20);
        lv_obj_set_y(bat_cap, 198);
        lv_label_set_text(bat_cap, "PHONE");
        lv_obj_set_style_text_color(bat_cap, lv_color_hex(0x101014), 0);
        lv_obj_set_style_text_font(bat_cap, font_body, 0);

        lv_obj_t * bat = lv_label_create(lv_obj_0);
        lv_obj_set_name(bat, "bat");
        lv_obj_set_x(bat, 20);
        lv_obj_set_y(bat, 216);
        lv_label_set_text(bat, "86%");
        lv_obj_set_style_text_color(bat, lv_color_hex(0x101014), 0);
        lv_obj_set_style_text_font(bat, font_h5, 0);

        lv_obj_t * o2_tile = lv_obj_create(lv_obj_0);
        lv_obj_set_name(o2_tile, "o2_tile");
        lv_obj_set_x(o2_tile, 124);
        lv_obj_set_y(o2_tile, 190);
        lv_obj_set_width(o2_tile, 108);
        lv_obj_set_height(o2_tile, 56);
        lv_obj_set_style_bg_color(o2_tile, lv_color_hex(0xB7A680), 0);
        lv_obj_set_style_radius(o2_tile, 20, 0);
        lv_obj_set_style_border_width(o2_tile, 0, 0);
        lv_obj_set_style_pad_all(o2_tile, 0, 0);

        lv_obj_t * o2_cap = lv_label_create(lv_obj_0);
        lv_obj_set_name(o2_cap, "o2_cap");
        lv_obj_set_x(o2_cap, 136);
        lv_obj_set_y(o2_cap, 198);
        lv_label_set_text(o2_cap, "SPO2");
        lv_obj_set_style_text_color(o2_cap, lv_color_hex(0x101014), 0);
        lv_obj_set_style_text_font(o2_cap, font_body, 0);

        lv_obj_t * o2 = lv_label_create(lv_obj_0);
        lv_obj_set_name(o2, "o2");
        lv_obj_set_x(o2, 136);
        lv_obj_set_y(o2, 216);
        lv_label_set_text(o2, "98%");
        lv_obj_set_style_text_color(o2, lv_color_hex(0x101014), 0);
        lv_obj_set_style_text_font(o2, font_h5, 0);

        lv_obj_t * info_tile = lv_obj_create(lv_obj_0);
        lv_obj_set_name(info_tile, "info_tile");
        lv_obj_set_x(info_tile, 8);
        lv_obj_set_y(info_tile, 254);
        lv_obj_set_width(info_tile, 224);
        lv_obj_set_height(info_tile, 58);
        lv_obj_set_style_bg_color(info_tile, lv_color_hex(0x1E1E26), 0);
        lv_obj_set_style_radius(info_tile, 20, 0);
        lv_obj_set_style_border_width(info_tile, 0, 0);
        lv_obj_set_style_pad_all(info_tile, 0, 0);

        lv_obj_t * wx = lv_label_create(lv_obj_0);
        lv_obj_set_name(wx, "wx");
        lv_obj_set_x(wx, 20);
        lv_obj_set_y(wx, 264);
        lv_label_set_text(wx, "Clear 24 C");
        lv_obj_set_style_text_color(wx, lv_color_hex(0xFFFFFF), 0);
        lv_obj_set_style_text_font(wx, font_body, 0);

        lv_obj_t * alarm = lv_label_create(lv_obj_0);
        lv_obj_set_name(alarm, "alarm");
        lv_obj_set_x(alarm, 20);
        lv_obj_set_y(alarm, 284);
        lv_label_set_text(alarm, "06:30");
        lv_obj_set_style_text_color(alarm, lv_color_hex(0xB8B8C4), 0);
        lv_obj_set_style_text_font(alarm, font_body, 0);

        lv_obj_t * alerts = lv_label_create(lv_obj_0);
        lv_obj_set_name(alerts, "alerts");
        lv_obj_set_x(alerts, -20);
        lv_obj_set_y(alerts, 272);
        lv_obj_set_align(alerts, LV_ALIGN_TOP_RIGHT);
        lv_label_set_text(alerts, "3");
        lv_obj_set_style_text_color(alerts, lv_color_hex(0xFFFFFF), 0);
        lv_obj_set_style_text_font(alerts, font_h4, 0);

        the_root = lv_obj_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

