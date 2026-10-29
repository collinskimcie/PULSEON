#include "UIUtils.h"

#include <Arduino.h>
#include <stdio.h>

#include "PULSEON_WATCH_UI.h"
#include "UITheme.h"

namespace
{
lv_color_t cBg, cCard, cText, cMuted, cAccent, cAccentDark;

void loadColors()
{
    const UIPalette& p = UI_PALETTES[uiThemeLoad() % UI_PALETTE_COUNT];
    cBg = lv_color_hex(p.bg);
    cCard = lv_color_hex(p.card);
    cText = lv_color_hex(p.text);
    cMuted = lv_color_hex(p.muted);
    cAccent = lv_color_hex(p.accent);
    cAccentDark = lv_color_hex(p.accentDark);
}

lv_obj_t* newRoot(const char* title)
{
    loadColors();
    lv_obj_t* r = lv_obj_create(lv_layer_top());
    lv_obj_set_pos(r, 0, 0);
    lv_obj_set_size(r, 240, 320);
    lv_obj_set_style_bg_color(r, cBg, 0);
    lv_obj_set_style_bg_opa(r, LV_OPA_COVER, 0);
    lv_obj_set_style_border_width(r, 0, 0);
    lv_obj_set_style_radius(r, 0, 0);
    lv_obj_set_style_pad_all(r, 0, 0);
    lv_obj_clear_flag(r, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_flag(r, LV_OBJ_FLAG_CLICKABLE);
    if (title != nullptr)
    {
        lv_obj_t* t = lv_label_create(r);
        lv_label_set_text(t, title);
        lv_obj_set_style_text_font(t, font_h4, 0);
        lv_obj_set_style_text_color(t, cText, 0);
        lv_obj_set_pos(t, 16, 10);
    }
    return r;
}

lv_obj_t* mkLabel(lv_obj_t* parent, const char* text, const lv_font_t* font, lv_color_t color,
                  lv_align_t align, int x, int y)
{
    lv_obj_t* l = lv_label_create(parent);
    lv_label_set_text(l, text);
    lv_obj_set_style_text_font(l, font, 0);
    lv_obj_set_style_text_color(l, color, 0);
    lv_obj_align(l, align, x, y);
    return l;
}

lv_obj_t* mkButton(lv_obj_t* parent, const char* text, int x, int y, int w, int h, lv_color_t bg,
                   lv_color_t fg, lv_event_cb_t cb, intptr_t id)
{
    lv_obj_t* b = lv_button_create(parent);
    lv_obj_set_pos(b, x, y);
    lv_obj_set_size(b, w, h);
    lv_obj_set_style_bg_color(b, bg, 0);
    lv_obj_set_style_bg_opa(b, LV_OPA_COVER, 0);
    lv_obj_set_style_border_width(b, 0, 0);
    lv_obj_set_style_shadow_width(b, 0, 0);
    lv_obj_set_style_radius(b, h / 2 > 22 ? 22 : h / 2, 0);
    lv_obj_add_event_cb(b, cb, LV_EVENT_CLICKED, reinterpret_cast<void*>(id));
    lv_obj_t* l = lv_label_create(b);
    lv_label_set_text(l, text);
    lv_obj_set_style_text_font(l, font_h5, 0);
    lv_obj_set_style_text_color(l, fg, 0);
    lv_obj_center(l);
    return b;
}

// ------------------------------------------------------------ Stopwatch
lv_obj_t *swRoot = nullptr, *swMain = nullptr, *swTenth = nullptr, *swToggleLbl = nullptr;
bool swRunning = false;
uint32_t swStartMs = 0, swAccumMs = 0;

uint32_t swElapsed()
{
    return swAccumMs + (swRunning ? millis() - swStartMs : 0);
}

void swRefresh()
{
    if (swRoot == nullptr)
    {
        return;
    }
    const uint32_t t = swElapsed();
    const uint32_t secs = t / 1000;
    char b[12];
    snprintf(b, sizeof(b), "%02u:%02u", (unsigned)((secs / 60) % 100), (unsigned)(secs % 60));
    lv_label_set_text(swMain, b);
    snprintf(b, sizeof(b), ".%u", (unsigned)((t % 1000) / 100));
    lv_label_set_text(swTenth, b);
    lv_label_set_text(swToggleLbl, swRunning ? "Stop" : "Start");
    lv_obj_center(swToggleLbl);
}

void swClick(lv_event_t* e)
{
    switch (reinterpret_cast<intptr_t>(lv_event_get_user_data(e)))
    {
        case 0:
            if (swRunning)
            {
                swAccumMs += millis() - swStartMs;
                swRunning = false;
            }
            else
            {
                swStartMs = millis();
                swRunning = true;
            }
            swRefresh();
            break;
        case 1:
            swAccumMs = 0;
            swStartMs = millis();
            swRefresh();
            break;
        default:
            if (swRoot != nullptr)
            {
                lv_obj_delete_async(swRoot);
                swRoot = nullptr;
            }
            break;
    }
}

// ------------------------------------------------------------ Timer
lv_obj_t *tmRoot = nullptr, *tmMain = nullptr, *tmStartLbl = nullptr;
uint32_t tmSetSec = 300, tmRemainMs = 300000, tmLastMs = 0;
bool tmRunning = false, tmDone = false;

void tmRefresh()
{
    if (tmRoot == nullptr)
    {
        return;
    }
    const uint32_t secs = (tmRemainMs + 999) / 1000;
    char b[12];
    snprintf(b, sizeof(b), "%02u:%02u", (unsigned)(secs / 60), (unsigned)(secs % 60));
    lv_label_set_text(tmMain, tmDone ? "TIME UP" : b);
    lv_label_set_text(tmStartLbl, tmRunning ? "Pause" : "Start");
    lv_obj_center(tmStartLbl);
}

void tmClick(lv_event_t* e)
{
    switch (reinterpret_cast<intptr_t>(lv_event_get_user_data(e)))
    {
        case 0:
            if (tmDone)
            {
                tmDone = false;
                tmRemainMs = tmSetSec * 1000;
            }
            if (tmRunning)
            {
                tmRunning = false;
            }
            else
            {
                if (tmRemainMs == 0)
                {
                    tmRemainMs = tmSetSec * 1000;
                }
                tmRunning = true;
                tmLastMs = millis();
            }
            break;
        case 1:
            tmRunning = false;
            tmDone = false;
            tmRemainMs = tmSetSec * 1000;
            break;
        case 2:
        case 3:
            if (!tmRunning)
            {
                if (reinterpret_cast<intptr_t>(lv_event_get_user_data(e)) == 2 && tmSetSec > 60)
                {
                    tmSetSec -= 60;
                }
                else if (reinterpret_cast<intptr_t>(lv_event_get_user_data(e)) == 3 && tmSetSec < 5940)
                {
                    tmSetSec += 60;
                }
                tmRemainMs = tmSetSec * 1000;
                tmDone = false;
            }
            break;
        default:
            if (tmRoot != nullptr)
            {
                lv_obj_delete_async(tmRoot);
                tmRoot = nullptr;
            }
            return;
    }
    tmRefresh();
}

// ------------------------------------------------------------ Flashlight
lv_obj_t* flRoot = nullptr;

void flClick(lv_event_t*)
{
    if (flRoot != nullptr)
    {
        lv_obj_delete_async(flRoot);
        flRoot = nullptr;
    }
}
}  // namespace

bool uiUtilsKeepAwake()
{
    return swRoot != nullptr || tmRoot != nullptr || flRoot != nullptr;
}

void uiStopwatchOpen(void*)
{
    if (swRoot != nullptr)
    {
        return;
    }
    swRoot = newRoot("STOPWATCH");
    swMain = mkLabel(swRoot, "00:00", font_h2, cAccent, LV_ALIGN_TOP_MID, 0, 70);
    swTenth = mkLabel(swRoot, ".0", font_h4, cMuted, LV_ALIGN_TOP_MID, 0, 132);
    swToggleLbl = lv_obj_get_child(
        mkButton(swRoot, "Start", 12, 190, 104, 56, cAccentDark, cAccent, swClick, 0), 0);
    mkButton(swRoot, "Reset", 124, 190, 104, 56, cCard, cText, swClick, 1);
    mkButton(swRoot, "Close", 12, 266, 216, 50, cCard, cText, swClick, 2);
    swRefresh();
}

void uiTimerOpen(void*)
{
    if (tmRoot != nullptr)
    {
        return;
    }
    tmRoot = newRoot("TIMER");
    tmMain = mkLabel(tmRoot, "05:00", font_h2, cAccent, LV_ALIGN_TOP_MID, 0, 62);
    mkButton(tmRoot, "- 1 min", 12, 130, 104, 46, cCard, cText, tmClick, 2);
    mkButton(tmRoot, "+ 1 min", 124, 130, 104, 46, cCard, cText, tmClick, 3);
    tmStartLbl = lv_obj_get_child(
        mkButton(tmRoot, "Start", 12, 190, 104, 56, cAccentDark, cAccent, tmClick, 0), 0);
    mkButton(tmRoot, "Reset", 124, 190, 104, 56, cCard, cText, tmClick, 1);
    mkButton(tmRoot, "Close", 12, 266, 216, 50, cCard, cText, tmClick, 4);
    tmRefresh();
}

void uiFlashlightOpen(void*)
{
    if (flRoot != nullptr)
    {
        return;
    }
    flRoot = newRoot(nullptr);
    lv_obj_set_style_bg_color(flRoot, lv_color_hex(0xFFFFFF), 0);
    mkLabel(flRoot, "Tap to close", font_body, lv_color_hex(0x777777), LV_ALIGN_BOTTOM_MID, 0, -14);
    lv_obj_add_event_cb(flRoot, flClick, LV_EVENT_CLICKED, nullptr);
}

void uiUtilsPoll()
{
    const uint32_t now = millis();

    if (tmRunning)
    {
        const uint32_t dt = now - tmLastMs;
        tmLastMs = now;
        if (dt >= tmRemainMs)
        {
            tmRemainMs = 0;
            tmRunning = false;
            tmDone = true;
            if (tmRoot == nullptr)
            {
                uiTimerOpen(nullptr);
            }
        }
        else
        {
            tmRemainMs -= dt;
        }
    }

    static uint32_t lastDraw = 0;
    if (now - lastDraw >= 100)
    {
        lastDraw = now;
        swRefresh();
        tmRefresh();
    }

    static uint32_t lastFlash = 0;
    static bool flashOn = false;
    if (tmRoot != nullptr && tmDone && now - lastFlash >= 500)
    {
        lastFlash = now;
        flashOn = !flashOn;
        loadColors();
        lv_obj_set_style_bg_color(tmRoot, flashOn ? cAccentDark : cBg, 0);
    }
}
