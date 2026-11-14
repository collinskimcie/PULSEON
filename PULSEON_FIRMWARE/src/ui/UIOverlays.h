#pragma once

#include <Arduino.h>
#include <lvgl.h>

#include "../app/AppState.h"

class ChronosManager;

// Call, alarm, find-watch and notification overlays on lv_layer_top().
// Call poll() every loop; it reads AppState and shows or hides panels.
// Overlay colors follow the selected theme (poll() notices theme changes).
class UIOverlays
{
public:
    void begin(AppStateManager* appState, ChronosManager* chronos);
    void poll();
    void showHistory();
    bool isModalVisible() const;

private:
    static void bannerClicked(lv_event_t* event);
    static void historyCloseClicked(lv_event_t* event);
    static void historyClearClicked(lv_event_t* event);
    static void historyDeleteClicked(lv_event_t* event);
    static void historyCardClicked(lv_event_t* event);
    static void callHideClicked(lv_event_t* event);
    static void alarmSnoozeClicked(lv_event_t* event);
    static void alarmStopClicked(lv_event_t* event);
    static void findDismissClicked(lv_event_t* event);
    static void bannerTimerCallback(lv_timer_t* timer);
    static void callTimerCallback(lv_timer_t* timer);
    static void findTimerCallback(lv_timer_t* timer);

    bool quietNow(const PulseonAppState& st) const;

    void buildAll();
    void destroyAll();
    void applyTheme(uint8_t theme);

    void buildBanner();
    void buildHistory();
    void buildCall();
    void buildAlarm();
    void buildFind();

    void showBanner(const PulseonNotification& n);
    void hideBanner();
    void rebuildHistory();
    void hideHistory();
    void showCall(const String& caller);
    void hideCall();
    void showAlarm(int8_t index);
    void hideAlarm();
    void showFind();
    void hideFind();

    AppStateManager* appState = nullptr;
    ChronosManager* chronos = nullptr;

    // Banner
    lv_obj_t* banner = nullptr;
    lv_obj_t* bannerApp = nullptr;
    lv_obj_t* bannerTitle = nullptr;
    lv_obj_t* bannerText = nullptr;
    lv_obj_t* bannerBadge = nullptr;
    lv_obj_t* bannerBar = nullptr;
    lv_timer_t* bannerTimer = nullptr;

    // History
    lv_obj_t* historyRoot = nullptr;
    lv_obj_t* historyList = nullptr;
    int8_t expandedIdx = -1;
    bool historyDirty = false;

    // Call
    lv_obj_t* callRoot = nullptr;
    lv_obj_t* callName = nullptr;
    lv_obj_t* callBadge = nullptr;
    lv_obj_t* callRing = nullptr;
    lv_obj_t* callElapsed = nullptr;
    lv_timer_t* callTimer = nullptr;
    uint32_t callStartMs = 0;

    // Alarm
    lv_obj_t* alarmRoot = nullptr;
    lv_obj_t* alarmTime = nullptr;
    lv_obj_t* alarmRing = nullptr;

    // Find watch
    lv_obj_t* findRoot = nullptr;
    lv_timer_t* findTimer = nullptr;
    bool findVisible = false;
    uint8_t findPhase = 0;
    uint32_t findStartMs = 0;
    uint32_t lastFindEvent = 0;

    struct DeleteCtx
    {
        UIOverlays* self;
        uint8_t index;
    };
    DeleteCtx deleteCtx[PULSEON_MAX_NOTIFICATIONS] = {};
    uint32_t lastNotifSeq = 0;

    bool historyVisible = false;
    bool callVisible = false;
    bool alarmVisible = false;
    bool bannerVisible = false;

    String lastCallName;
    int8_t lastAlarm = -1;
    uint8_t lastNotifHead = 0;
    uint8_t lastNotifStored = 0;
    uint32_t lastThemeCheckMs = 0;
};
