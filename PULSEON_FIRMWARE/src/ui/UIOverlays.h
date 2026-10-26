#pragma once

#include <Arduino.h>
#include <lvgl.h>

#include "../app/AppState.h"

class ChronosManager;

// Call, alarm and notification overlays on lv_layer_top().
// Call poll() every loop; it reads AppState and shows or hides panels.
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
    static void callHideClicked(lv_event_t* event);
    static void alarmSnoozeClicked(lv_event_t* event);
    static void alarmStopClicked(lv_event_t* event);
    static void bannerTimerCallback(lv_timer_t* timer);

    void buildBanner();
    void buildHistory();
    void buildCall();
    void buildAlarm();
    void buildFind();
    void showFind();
    void hideFind();
    static void findTimerCallback(lv_timer_t* timer);
    static void findDismissClicked(lv_event_t* event);

    void showBanner(const PulseonNotification& n);
    void hideBanner();
    void rebuildHistory();
    void hideHistory();
    void showCall(const String& caller);
    void hideCall();
    void showAlarm(int8_t index);
    void hideAlarm();

    AppStateManager* appState = nullptr;
    ChronosManager* chronos = nullptr;

    lv_obj_t* banner = nullptr;
    lv_obj_t* bannerApp = nullptr;
    lv_obj_t* bannerTitle = nullptr;
    lv_obj_t* bannerText = nullptr;
    lv_timer_t* bannerTimer = nullptr;

    lv_obj_t* historyRoot = nullptr;
    lv_obj_t* historyList = nullptr;

    lv_obj_t* callRoot = nullptr;
    lv_obj_t* callName = nullptr;

    lv_obj_t* alarmRoot = nullptr;
    lv_obj_t* alarmTime = nullptr;

    lv_obj_t* findRoot = nullptr;
    lv_timer_t* findTimer = nullptr;
    bool findVisible = false;
    uint8_t findPhase = 0;
    uint32_t findStartMs = 0;
    uint32_t lastFindEvent = 0;

    bool historyVisible = false;
    bool callVisible = false;
    bool alarmVisible = false;
    bool bannerVisible = false;

    String lastCallName;
    int8_t lastAlarm = -1;
    uint8_t lastNotifHead = 0;
    uint8_t lastNotifStored = 0;
};
