#include "UIOverlays.h"
#include "UIText.h"

#include <stdio.h>

#include "PULSEON_WATCH_UI.h"
#include "../chronos/ChronosManager.h"

namespace
{
constexpr uint32_t BANNER_MS = 6000;

const lv_color_t OV_BG = lv_color_hex(0x090A0E);
const lv_color_t OV_CARD = lv_color_hex(0x15161C);
const lv_color_t OV_CARD_ALT = lv_color_hex(0x25262D);
const lv_color_t OV_TEXT = lv_color_hex(0xF7F7FA);
const lv_color_t OV_MUTED = lv_color_hex(0xA8A3AB);
const lv_color_t OV_ACCENT = lv_color_hex(0xFF5D6C);
const lv_color_t OV_ACCENT_DARK = lv_color_hex(0x54252D);
const lv_color_t OV_GOOD = lv_color_hex(0x75D6B1);
const lv_color_t OV_AMBER = lv_color_hex(0xFFC66D);

lv_obj_t* makeLabel(
    lv_obj_t* parent,
    const char* text,
    int32_t x,
    int32_t y,
    int32_t w,
    int32_t h,
    const lv_font_t* font,
    lv_color_t color,
    lv_text_align_t align = LV_TEXT_ALIGN_LEFT,
    lv_label_long_mode_t mode = LV_LABEL_LONG_DOT
)
{
    lv_obj_t* label = lv_label_create(parent);
    lv_label_set_long_mode(label, mode);
    lv_label_set_text(label, text);
    lv_obj_set_pos(label, x, y);
    lv_obj_set_size(label, w, h);
    lv_obj_set_style_text_font(label, font, 0);
    lv_obj_set_style_text_color(label, color, 0);
    lv_obj_set_style_text_align(label, align, 0);
    lv_obj_add_flag(label, LV_OBJ_FLAG_EVENT_BUBBLE);
    return label;
}

lv_obj_t* makePanel(
    lv_obj_t* parent,
    int32_t x,
    int32_t y,
    int32_t w,
    int32_t h,
    lv_color_t color,
    int32_t radius
)
{
    lv_obj_t* panel = lv_obj_create(parent);
    lv_obj_set_pos(panel, x, y);
    lv_obj_set_size(panel, w, h);
    lv_obj_set_style_bg_color(panel, color, 0);
    lv_obj_set_style_bg_opa(panel, LV_OPA_COVER, 0);
    lv_obj_set_style_border_width(panel, 0, 0);
    lv_obj_set_style_radius(panel, radius, 0);
    lv_obj_set_style_pad_all(panel, 0, 0);
    lv_obj_clear_flag(panel, LV_OBJ_FLAG_SCROLLABLE);
    return panel;
}

lv_obj_t* makeButton(
    lv_obj_t* parent,
    const char* text,
    int32_t x,
    int32_t y,
    int32_t w,
    int32_t h,
    lv_color_t bg,
    lv_color_t fg,
    lv_event_cb_t cb,
    void* user
)
{
    lv_obj_t* button = lv_button_create(parent);
    lv_obj_set_pos(button, x, y);
    lv_obj_set_size(button, w, h);
    lv_obj_set_style_bg_color(button, bg, 0);
    lv_obj_set_style_bg_opa(button, LV_OPA_COVER, 0);
    lv_obj_set_style_border_width(button, 0, 0);
    lv_obj_set_style_shadow_width(button, 0, 0);
    lv_obj_set_style_radius(button, h / 2, 0);
    lv_obj_add_event_cb(button, cb, LV_EVENT_CLICKED, user);

    lv_obj_t* label = lv_label_create(button);
    lv_label_set_text(label, text);
    lv_obj_set_style_text_font(label, font_h5, 0);
    lv_obj_set_style_text_color(label, fg, 0);
    lv_obj_center(label);
    return button;
}

UIOverlays* selfFrom(lv_event_t* event)
{
    return static_cast<UIOverlays*>(lv_event_get_user_data(event));
}
} // namespace

// ------------------------------------------------------------------
// Setup
// ------------------------------------------------------------------

void UIOverlays::begin(AppStateManager* state, ChronosManager* chronosManager)
{
    appState = state;
    chronos = chronosManager;

    if (appState != nullptr)
    {
        const PulseonAppState& st = appState->getState();
        lastNotifHead = st.notificationHead;
        lastNotifStored = st.notificationStored;
        lastFindEvent = st.findWatchEventId;
    }

    buildBanner();
    buildHistory();
    buildCall();
    buildAlarm();
    buildFind();
}

void UIOverlays::buildBanner()
{
    banner = makePanel(lv_layer_top(), 8, 52, 224, 84, OV_CARD, 16);
    lv_obj_set_style_border_color(banner, OV_ACCENT, 0);
    lv_obj_set_style_border_width(banner, 1, 0);
    lv_obj_add_flag(banner, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(banner, bannerClicked, LV_EVENT_CLICKED, this);

    bannerApp = makeLabel(banner, "", 12, 6, 200, 16, font_body, OV_MUTED);
    bannerTitle = makeLabel(banner, "", 12, 22, 200, 22, font_h5, OV_TEXT);
    bannerText = makeLabel(banner, "", 12, 46, 200, 32, font_body, OV_MUTED,
                           LV_TEXT_ALIGN_LEFT, LV_LABEL_LONG_WRAP);

    lv_obj_add_flag(banner, LV_OBJ_FLAG_HIDDEN);

    bannerTimer = lv_timer_create(bannerTimerCallback, BANNER_MS, this);
    lv_timer_pause(bannerTimer);
}

void UIOverlays::buildHistory()
{
    historyRoot = makePanel(lv_layer_top(), 0, 0, 240, 320, OV_BG, 0);
    lv_obj_add_flag(historyRoot, LV_OBJ_FLAG_CLICKABLE);

    makeLabel(historyRoot, "NOTIFICATIONS", 16, 10, 208, 28, font_h4, OV_TEXT);

    historyList = lv_obj_create(historyRoot);
    lv_obj_set_pos(historyList, 8, 44);
    lv_obj_set_size(historyList, 224, 220);
    lv_obj_set_style_bg_opa(historyList, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_width(historyList, 0, 0);
    lv_obj_set_style_pad_all(historyList, 0, 0);
    lv_obj_set_style_pad_row(historyList, 8, 0);
    lv_obj_set_flex_flow(historyList, LV_FLEX_FLOW_COLUMN);

    makeButton(historyRoot, "Clear", 8, 272, 108, 40, OV_ACCENT_DARK, OV_ACCENT,
               historyClearClicked, this);
    makeButton(historyRoot, "Close", 124, 272, 108, 40, OV_CARD_ALT, OV_TEXT,
               historyCloseClicked, this);

    lv_obj_add_flag(historyRoot, LV_OBJ_FLAG_HIDDEN);
}

void UIOverlays::buildCall()
{
    callRoot = makePanel(lv_layer_top(), 0, 0, 240, 320, OV_BG, 0);
    lv_obj_add_flag(callRoot, LV_OBJ_FLAG_CLICKABLE);

    makeLabel(callRoot, "INCOMING CALL", 16, 70, 208, 24, font_h5, OV_GOOD,
              LV_TEXT_ALIGN_CENTER);
    callName = makeLabel(callRoot, "", 12, 120, 216, 80, font_h3, OV_TEXT,
                         LV_TEXT_ALIGN_CENTER, LV_LABEL_LONG_WRAP);
    makeButton(callRoot, "Hide", 60, 250, 120, 44, OV_CARD_ALT, OV_TEXT,
               callHideClicked, this);

    lv_obj_add_flag(callRoot, LV_OBJ_FLAG_HIDDEN);
}

void UIOverlays::buildAlarm()
{
    alarmRoot = makePanel(lv_layer_top(), 0, 0, 240, 320, OV_BG, 0);
    lv_obj_add_flag(alarmRoot, LV_OBJ_FLAG_CLICKABLE);

    makeLabel(alarmRoot, "ALARM", 16, 60, 208, 24, font_h5, OV_AMBER,
              LV_TEXT_ALIGN_CENTER);
    alarmTime = makeLabel(alarmRoot, "--:--", 8, 110, 224, 70, font_h2, OV_TEXT,
                          LV_TEXT_ALIGN_CENTER);
    makeButton(alarmRoot, "Snooze", 8, 250, 108, 44, OV_CARD_ALT, OV_AMBER,
               alarmSnoozeClicked, this);
    makeButton(alarmRoot, "Stop", 124, 250, 108, 44, OV_ACCENT_DARK, OV_ACCENT,
               alarmStopClicked, this);

    lv_obj_add_flag(alarmRoot, LV_OBJ_FLAG_HIDDEN);
}

// ------------------------------------------------------------------
// Polling (call every loop, cheap when nothing changed)
// ------------------------------------------------------------------

void UIOverlays::poll()
{
    if (appState == nullptr)
    {
        return;
    }

    const PulseonAppState& st = appState->getState();

    // Call
    if (st.callActive)
    {
        if (!callVisible || !(st.callerName == lastCallName))
        {
            showCall(st.callerName);
        }
    }
    else if (callVisible)
    {
        hideCall();
    }

    // Alarm
    if (st.alarmRinging != lastAlarm)
    {
        if (st.alarmRinging >= 0)
        {
            showAlarm(st.alarmRinging);
        }
        else
        {
            hideAlarm();
        }
        lastAlarm = st.alarmRinging;
    }

    // Find watch
    if (st.findWatchEventId != lastFindEvent)
    {
        lastFindEvent = st.findWatchEventId;
        showFind();
    }
    if (findVisible && millis() - findStartMs > 30000)
    {
        hideFind();
    }

    // Notifications
    if (st.notificationHead != lastNotifHead ||
        st.notificationStored != lastNotifStored)
    {
        lastNotifHead = st.notificationHead;
        lastNotifStored = st.notificationStored;

        if (historyVisible)
        {
            rebuildHistory();
        }

        Serial.println("[UI] showing banner");
        const PulseonNotification* newest = appState->getNotification(0);
        if (newest != nullptr && !callVisible && !alarmVisible && !historyVisible)
        {
            showBanner(*newest);
        }
    }
}

bool UIOverlays::isModalVisible() const
{
    return callVisible || alarmVisible || historyVisible;
}

// ------------------------------------------------------------------
// Banner
// ------------------------------------------------------------------

void UIOverlays::showBanner(const PulseonNotification& n)
{
    if (banner == nullptr)
    {
        return;
    }

    String header = n.app;
    if (n.time.length() > 0)
    {
        header += "  ";
        header += n.time;
    }

    lv_obj_set_style_text_font(bannerTitle, uiEmojiFont(font_h5), 0);
    lv_obj_set_style_text_font(bannerText, uiEmojiFont(font_body), 0);
    lv_label_set_text(bannerApp, uiText(header).c_str());
    lv_label_set_text(bannerTitle, uiText(n.title).c_str());
    lv_label_set_text(bannerText, uiText(n.message).c_str());

    lv_obj_clear_flag(banner, LV_OBJ_FLAG_HIDDEN);
    lv_obj_move_foreground(banner);
    bannerVisible = true;

    lv_timer_reset(bannerTimer);
    lv_timer_resume(bannerTimer);
}

void UIOverlays::hideBanner()
{
    if (banner != nullptr)
    {
        lv_obj_add_flag(banner, LV_OBJ_FLAG_HIDDEN);
    }
    if (bannerTimer != nullptr)
    {
        lv_timer_pause(bannerTimer);
    }
    bannerVisible = false;
}

void UIOverlays::bannerTimerCallback(lv_timer_t* timer)
{
    UIOverlays* self = static_cast<UIOverlays*>(lv_timer_get_user_data(timer));
    if (self != nullptr)
    {
        self->hideBanner();
    }
}

void UIOverlays::bannerClicked(lv_event_t* event)
{
    UIOverlays* self = selfFrom(event);
    if (self == nullptr)
    {
        return;
    }
    self->hideBanner();
    self->showHistory();
}

// ------------------------------------------------------------------
// History
// ------------------------------------------------------------------

void UIOverlays::showHistory()
{
    if (historyRoot == nullptr)
    {
        return;
    }

    hideBanner();
    rebuildHistory();
    lv_obj_clear_flag(historyRoot, LV_OBJ_FLAG_HIDDEN);
    lv_obj_move_foreground(historyRoot);

    // Calls and alarms must stay on top.
    if (callVisible) lv_obj_move_foreground(callRoot);
    if (alarmVisible) lv_obj_move_foreground(alarmRoot);

    historyVisible = true;
}

void UIOverlays::hideHistory()
{
    if (historyRoot != nullptr)
    {
        lv_obj_add_flag(historyRoot, LV_OBJ_FLAG_HIDDEN);
    }
    historyVisible = false;
}

void UIOverlays::rebuildHistory()
{
    if (historyList == nullptr || appState == nullptr)
    {
        return;
    }

    lv_obj_clean(historyList);

    const uint8_t stored = appState->getState().notificationStored;
    if (stored == 0)
    {
        makeLabel(historyList, "No notifications", 0, 0, 224, 24, font_body, OV_MUTED,
                  LV_TEXT_ALIGN_CENTER);
        return;
    }

    for (uint8_t i = 0; i < stored; ++i)
    {
        const PulseonNotification* n = appState->getNotification(i);
        if (n == nullptr)
        {
            continue;
        }

        lv_obj_t* card = makePanel(historyList, 0, 0, 224, 80, OV_CARD, 14);

        String header = n->app;
        if (n->time.length() > 0)
        {
            header += "  ";
            header += n->time;
        }

        makeLabel(card, uiText(header).c_str(), 12, 6, 200, 16, font_body, OV_MUTED);
        makeLabel(card, uiText(n->title).c_str(), 12, 22, 200, 22, uiEmojiFont(font_h5), OV_TEXT);
        makeLabel(card, uiText(n->message).c_str(), 12, 44, 200, 32, uiEmojiFont(font_body), OV_MUTED,
                  LV_TEXT_ALIGN_LEFT, LV_LABEL_LONG_WRAP);
    }
}

void UIOverlays::historyCloseClicked(lv_event_t* event)
{
    UIOverlays* self = selfFrom(event);
    if (self != nullptr)
    {
        self->hideHistory();
    }
}

void UIOverlays::historyClearClicked(lv_event_t* event)
{
    UIOverlays* self = selfFrom(event);
    if (self == nullptr)
    {
        return;
    }

    if (self->chronos != nullptr)
    {
        self->chronos->clearNotifications();
    }
    self->rebuildHistory();
}

// ------------------------------------------------------------------
// Call
// ------------------------------------------------------------------

void UIOverlays::showCall(const String& caller)
{
    Serial.println("[UI] showing call");
    lastCallName = caller;
    lv_obj_set_style_text_font(callName, uiEmojiFont(font_h3), 0);
    const String shownCaller = uiText(caller);
    lv_label_set_text(callName, shownCaller.length() > 0 ? shownCaller.c_str() : "Unknown");

    hideBanner();
    lv_obj_clear_flag(callRoot, LV_OBJ_FLAG_HIDDEN);
    lv_obj_move_foreground(callRoot);
    if (alarmVisible) lv_obj_move_foreground(alarmRoot);
    callVisible = true;
}

void UIOverlays::hideCall()
{
    lv_obj_add_flag(callRoot, LV_OBJ_FLAG_HIDDEN);
    callVisible = false;
    lastCallName = "";
}

void UIOverlays::callHideClicked(lv_event_t* event)
{
    UIOverlays* self = selfFrom(event);
    if (self == nullptr)
    {
        return;
    }

    // Clears the call in AppState so the overlay does not pop back up.
    // The phone itself keeps ringing; answering stays on the phone.
    if (self->appState != nullptr)
    {
        self->appState->setIncomingCall("", false);
    }
    self->hideCall();
}

// ------------------------------------------------------------------
// Alarm
// ------------------------------------------------------------------

void UIOverlays::showAlarm(int8_t index)
{
    if (appState == nullptr || index < 0 || index >= static_cast<int8_t>(PULSEON_MAX_ALARMS))
    {
        return;
    }

    const PulseonAppState& st = appState->getState();
    const PulseonAlarm& a = st.alarms[index];

    char buf[16];
    if (st.is24Hour)
    {
        snprintf(buf, sizeof(buf), "%02u:%02u",
                 static_cast<unsigned>(a.hour), static_cast<unsigned>(a.minute));
    }
    else
    {
        unsigned h12 = a.hour % 12;
        if (h12 == 0) h12 = 12;
        snprintf(buf, sizeof(buf), "%u:%02u %s", h12,
                 static_cast<unsigned>(a.minute), a.hour >= 12 ? "PM" : "AM");
    }
    lv_label_set_text(alarmTime, buf);

    hideBanner();
    lv_obj_clear_flag(alarmRoot, LV_OBJ_FLAG_HIDDEN);
    lv_obj_move_foreground(alarmRoot);
    alarmVisible = true;
}

void UIOverlays::hideAlarm()
{
    lv_obj_add_flag(alarmRoot, LV_OBJ_FLAG_HIDDEN);
    alarmVisible = false;
}

void UIOverlays::alarmSnoozeClicked(lv_event_t* event)
{
    UIOverlays* self = selfFrom(event);
    if (self != nullptr && self->chronos != nullptr)
    {
        self->chronos->snoozeAlarm(5);
    }
}

void UIOverlays::alarmStopClicked(lv_event_t* event)
{
    UIOverlays* self = selfFrom(event);
    if (self != nullptr && self->chronos != nullptr)
    {
        self->chronos->dismissAlarm();
    }
}

void UIOverlays::buildFind()
{
    findRoot = makePanel(lv_layer_top(), 0, 0, 240, 320, OV_ACCENT_DARK, 0);
    lv_obj_add_flag(findRoot, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(findRoot, findDismissClicked, LV_EVENT_CLICKED, this);

    makeLabel(findRoot, "FIND WATCH", 16, 110, 208, 28, font_h4, OV_TEXT, LV_TEXT_ALIGN_CENTER);
    makeLabel(findRoot, "Your phone is looking for me", 16, 150, 208, 40, font_body, OV_TEXT,
              LV_TEXT_ALIGN_CENTER, LV_LABEL_LONG_WRAP);
    makeLabel(findRoot, "Tap anywhere to stop", 16, 270, 208, 20, font_body, OV_MUTED,
              LV_TEXT_ALIGN_CENTER);

    lv_obj_add_flag(findRoot, LV_OBJ_FLAG_HIDDEN);

    findTimer = lv_timer_create(findTimerCallback, 700, this);
    lv_timer_pause(findTimer);
}

void UIOverlays::showFind()
{
    if (findRoot == nullptr)
    {
        return;
    }

    Serial.println("[UI] find watch requested");
    findStartMs = millis();
    findPhase = 0;
    findVisible = true;

    lv_obj_set_style_bg_color(findRoot, OV_ACCENT_DARK, 0);
    lv_obj_clear_flag(findRoot, LV_OBJ_FLAG_HIDDEN);
    lv_obj_move_foreground(findRoot);

    // Calls and alarms stay on top.
    if (callVisible) lv_obj_move_foreground(callRoot);
    if (alarmVisible) lv_obj_move_foreground(alarmRoot);

    lv_timer_reset(findTimer);
    lv_timer_resume(findTimer);
}

void UIOverlays::hideFind()
{
    if (findRoot != nullptr)
    {
        lv_obj_add_flag(findRoot, LV_OBJ_FLAG_HIDDEN);
    }
    if (findTimer != nullptr)
    {
        lv_timer_pause(findTimer);
    }
    findVisible = false;
}

void UIOverlays::findTimerCallback(lv_timer_t* timer)
{
    UIOverlays* self = static_cast<UIOverlays*>(lv_timer_get_user_data(timer));
    if (self == nullptr || self->findRoot == nullptr)
    {
        return;
    }
    self->findPhase ^= 1;
    lv_obj_set_style_bg_color(self->findRoot, self->findPhase ? OV_ACCENT : OV_ACCENT_DARK, 0);
}

void UIOverlays::findDismissClicked(lv_event_t* event)
{
    UIOverlays* self = selfFrom(event);
    if (self != nullptr)
    {
        self->hideFind();
    }
}
