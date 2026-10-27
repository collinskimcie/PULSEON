#include "UIUpdate.h"

#include <ArduinoOTA.h>
#include <WiFi.h>
#include <esp_task_wdt.h>
#include <stdio.h>

#include "PULSEON_WATCH_UI.h"
#include "UIApps.h"
#include "WifiSetup.h"

#if __has_include("wifi_secrets.h")
#include "wifi_secrets.h"
#define PULSEON_HAVE_WIFI 1
#else
#define PULSEON_HAVE_WIFI 0
#endif

namespace
{
constexpr const char* HOSTNAME = "pulseon";
constexpr uint32_t CONNECT_TIMEOUT_MS = 20000;
constexpr uint32_t READY_TIMEOUT_MS = 300000;

const lv_color_t C_BG = lv_color_hex(0x090A0E);
const lv_color_t C_CARD = lv_color_hex(0x15161C);
const lv_color_t C_CARD_ALT = lv_color_hex(0x25262D);
const lv_color_t C_TEXT = lv_color_hex(0xF7F7FA);
const lv_color_t C_MUTED = lv_color_hex(0xA8A3AB);
const lv_color_t C_ACCENT = lv_color_hex(0xFF5D6C);
const lv_color_t C_ACCENT_DARK = lv_color_hex(0x54252D);
const lv_color_t C_GOOD = lv_color_hex(0x75D6B1);
const lv_color_t C_AMBER = lv_color_hex(0xFFC66D);

enum State : uint8_t
{
    ST_OFF,
    ST_CONNECTING,
    ST_READY,
    ST_UPDATING,
    ST_ERROR,
    ST_SETUP
};

UIApps* gApps = nullptr;
lv_obj_t* root = nullptr;
lv_obj_t* statusLabel = nullptr;
lv_obj_t* detailLabel = nullptr;
lv_obj_t* bar = nullptr;
lv_obj_t* toggleLabel = nullptr;
State state = ST_OFF;
uint32_t stateSinceMs = 0;
bool radioOn = false;
bool callbacksSet = false;
int lastPct = -1;

lv_obj_t* makeLabel(
    lv_obj_t* parent, const char* text, int32_t x, int32_t y, int32_t w, int32_t h,
    const lv_font_t* font, lv_color_t color,
    lv_text_align_t align = LV_TEXT_ALIGN_LEFT,
    lv_label_long_mode_t mode = LV_LABEL_LONG_DOT)
{
    lv_obj_t* label = lv_label_create(parent);
    lv_label_set_long_mode(label, mode);
    lv_label_set_text(label, text);
    lv_obj_set_pos(label, x, y);
    lv_obj_set_size(label, w, h);
    lv_obj_set_style_text_font(label, font, 0);
    lv_obj_set_style_text_color(label, color, 0);
    lv_obj_set_style_text_align(label, align, 0);
    return label;
}

lv_obj_t* makeButton(
    lv_obj_t* parent, const char* text, int32_t x, int32_t y, int32_t w, int32_t h,
    lv_color_t bg, lv_color_t fg, lv_event_cb_t cb, lv_obj_t** labelOut)
{
    lv_obj_t* button = lv_button_create(parent);
    lv_obj_set_pos(button, x, y);
    lv_obj_set_size(button, w, h);
    lv_obj_set_style_bg_color(button, bg, 0);
    lv_obj_set_style_bg_opa(button, LV_OPA_COVER, 0);
    lv_obj_set_style_border_width(button, 0, 0);
    lv_obj_set_style_shadow_width(button, 0, 0);
    lv_obj_set_style_radius(button, h / 2 > 22 ? 22 : h / 2, 0);
    lv_obj_add_event_cb(button, cb, LV_EVENT_CLICKED, nullptr);

    lv_obj_t* label = lv_label_create(button);
    lv_label_set_text(label, text);
    lv_obj_set_style_text_font(label, font_h5, 0);
    lv_obj_set_style_text_color(label, fg, 0);
    lv_obj_center(label);
    if (labelOut != nullptr)
    {
        *labelOut = label;
    }
    return button;
}

void setStatus(const char* text, lv_color_t color, const char* detail)
{
    lv_label_set_text(statusLabel, text);
    lv_obj_set_style_text_color(statusLabel, color, 0);
    lv_label_set_text(detailLabel, detail);
}

void ensureCallbacks()
{
    if (callbacksSet)
    {
        return;
    }
    callbacksSet = true;

    ArduinoOTA.onStart([]() {
        state = ST_UPDATING;
        lastPct = -1;
        esp_task_wdt_reset();
        setStatus("Updating...", C_AMBER, "Do not turn the watch off");
        lv_bar_set_value(bar, 0, LV_ANIM_OFF);
        lv_obj_clear_flag(bar, LV_OBJ_FLAG_HIDDEN);
        lv_timer_handler();
    });

    ArduinoOTA.onProgress([](unsigned int done, unsigned int total) {
        esp_task_wdt_reset();
        const int pct = total > 0 ? static_cast<int>((static_cast<uint64_t>(done) * 100) / total) : 0;
        if (pct != lastPct)
        {
            lastPct = pct;
            lv_bar_set_value(bar, pct, LV_ANIM_OFF);
            lv_label_set_text_fmt(detailLabel, "%d%% - do not turn the watch off", pct);
            lv_timer_handler();
        }
    });

    ArduinoOTA.onEnd([]() {
        setStatus("Done", C_GOOD, "Restarting...");
        lv_timer_handler();
    });

    ArduinoOTA.onError([](ota_error_t error) {
        Serial.printf("[OTA] error %u\n", static_cast<unsigned>(error));
        state = ST_ERROR;
        stateSinceMs = millis();
        setStatus("Update failed", C_ACCENT, "Nothing was changed. Tap Start to try again.");
    });
}

void startRadio()
{
#if PULSEON_HAVE_WIFI
    ensureCallbacks();
    lv_obj_add_flag(bar, LV_OBJ_FLAG_HIDDEN);
    WiFi.mode(WIFI_STA);
    WiFi.setHostname(HOSTNAME);
    wifiConnectBegin();
    radioOn = true;
    state = ST_CONNECTING;
    stateSinceMs = millis();
    setStatus("Connecting...", C_AMBER, "Joining your Wi-Fi network");
    lv_label_set_text(toggleLabel, "Stop");
    lv_obj_center(toggleLabel);
#else
    state = ST_ERROR;
    stateSinceMs = millis();
    setStatus("No Wi-Fi details", C_ACCENT,
              "Create include/wifi_secrets.h on the PC and rebuild.");
#endif
}

void stopRadio()
{
    wifiSetupStop();
    if (radioOn)
    {
        ArduinoOTA.end();
        WiFi.disconnect(true);
        WiFi.mode(WIFI_OFF);
        radioOn = false;
    }
    lv_label_set_text(toggleLabel, "Start");
    lv_obj_center(toggleLabel);
}

void toggleClicked(lv_event_t* event)
{
    (void)event;
    if (state == ST_OFF || state == ST_ERROR)
    {
        startRadio();
    }
    else
    {
        stopRadio();
        state = ST_OFF;
        lv_obj_add_flag(bar, LV_OBJ_FLAG_HIDDEN);
        setStatus("Wi-Fi off", C_MUTED, "Tap Start to turn Wi-Fi on again.");
    }
}

void backClicked(lv_event_t* event)
{
    (void)event;
    stopRadio();
    state = ST_OFF;
    lv_obj_add_flag(root, LV_OBJ_FLAG_HIDDEN);
    if (gApps != nullptr)
    {
        gApps->show();
    }
}
} // namespace

void uiUpdateBegin(UIApps* apps)
{
    gApps = apps;

    root = lv_obj_create(lv_layer_top());
    lv_obj_set_pos(root, 0, 0);
    lv_obj_set_size(root, 240, 320);
    lv_obj_set_style_bg_color(root, C_BG, 0);
    lv_obj_set_style_bg_opa(root, LV_OPA_COVER, 0);
    lv_obj_set_style_border_width(root, 0, 0);
    lv_obj_set_style_radius(root, 0, 0);
    lv_obj_set_style_pad_all(root, 0, 0);
    lv_obj_clear_flag(root, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_flag(root, LV_OBJ_FLAG_CLICKABLE);

    makeLabel(root, "UPDATE", 16, 10, 208, 28, font_h4, C_TEXT);
    statusLabel = makeLabel(root, "", 16, 52, 208, 26, font_h5, C_MUTED);
    detailLabel = makeLabel(root, "", 16, 84, 208, 80, font_body, C_MUTED,
                            LV_TEXT_ALIGN_LEFT, LV_LABEL_LONG_WRAP);

    bar = lv_bar_create(root);
    lv_obj_set_pos(bar, 24, 170);
    lv_obj_set_size(bar, 192, 12);
    lv_bar_set_range(bar, 0, 100);
    lv_obj_set_style_bg_color(bar, C_CARD, LV_PART_MAIN);
    lv_obj_set_style_bg_color(bar, C_ACCENT, LV_PART_INDICATOR);
    lv_obj_add_flag(bar, LV_OBJ_FLAG_HIDDEN);

    makeButton(root, "Start", 40, 196, 160, 48, C_ACCENT_DARK, C_ACCENT, toggleClicked, &toggleLabel);
    makeButton(root, "Back", 12, 268, 216, 44, C_CARD_ALT, C_TEXT, backClicked, nullptr);

    lv_obj_add_flag(root, LV_OBJ_FLAG_HIDDEN);
}

void uiUpdateOpen(void* user)
{
    (void)user;
    Serial.println("[UPDATE] page opened");
    if (root == nullptr)
    {
        return;
    }
    if (state == ST_OFF)
    {
        setStatus("Wi-Fi update", C_MUTED,
                  "Turns Wi-Fi on so the PC can send new firmware. It turns off again when you leave.");
    }
    lv_obj_clear_flag(root, LV_OBJ_FLAG_HIDDEN);
    lv_obj_move_foreground(root);
    if (state == ST_OFF)
    {
        startRadio();
    }
}

void uiUpdatePoll()
{
    if (root == nullptr)
    {
        return;
    }

    if (state == ST_CONNECTING)
    {
#if PULSEON_HAVE_WIFI
        if (WiFi.status() == WL_CONNECTED)
        {
            ArduinoOTA.setHostname(HOSTNAME);
            ArduinoOTA.setPassword(OTA_PASSWORD);
            ArduinoOTA.begin();
            Serial.printf("[UPDATE] ready, IP %s\n", WiFi.localIP().toString().c_str());
            state = ST_READY;
            stateSinceMs = millis();
            lv_label_set_text_fmt(detailLabel, "IP %s\n%s.local",
                                  WiFi.localIP().toString().c_str(), HOSTNAME);
            lv_label_set_text(statusLabel, "Ready");
            lv_obj_set_style_text_color(statusLabel, C_GOOD, 0);
        }
        else if (millis() - stateSinceMs > CONNECT_TIMEOUT_MS)
        {
            if (wifiConnectAdvance())
            {
                stateSinceMs = millis();
            }
            else
            {
                Serial.printf("[UPDATE] could not join, WiFi status %d\n", static_cast<int>(WiFi.status()));
                wifiSetupStart();
                state = ST_SETUP;
                stateSinceMs = millis();
                setStatus("Add Wi-Fi", C_AMBER, wifiSetupHelp());
            }
        }
#endif
    }
    else if (state == ST_READY || state == ST_UPDATING)
    {
        ArduinoOTA.handle();
        if (state == ST_READY && millis() - stateSinceMs > READY_TIMEOUT_MS)
        {
            stopRadio();
            state = ST_OFF;
            setStatus("Wi-Fi off", C_MUTED, "Timed out after 5 minutes. Tap Start to turn it on again.");
        }
    }
    else if (state == ST_ERROR && radioOn)
    {
        stopRadio();
    }
    else if (state == ST_SETUP)
    {
        wifiSetupLoop();
        if (wifiSetupSaved())
        {
            stopRadio();
            state = ST_OFF;
            startRadio();
        }
        else if (millis() - stateSinceMs > READY_TIMEOUT_MS)
        {
            stopRadio();
            state = ST_OFF;
            setStatus("Wi-Fi off", C_MUTED, "Setup timed out. Open this page again to retry.");
        }
    }
}
