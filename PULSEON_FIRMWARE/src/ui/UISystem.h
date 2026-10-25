#pragma once

#include <Arduino.h>
#include <lvgl.h>

#include "../app/AppState.h"

class ChronosManager;
class UIApps;

// Settings, Bluetooth, Contacts and QR pages, plus idle dimming.
class UISystem
{
public:
    typedef void (*BrightnessHandler)(uint8_t percent);

    void begin(AppStateManager* appState, ChronosManager* chronos, UIApps* apps);
    void poll();
    void showSettings();
    void setBrightnessHandler(BrightnessHandler handler);

private:
    enum Page : uint8_t
    {
        PAGE_NONE = 0,
        PAGE_SETTINGS,
        PAGE_BLUETOOTH,
        PAGE_CONTACTS,
        PAGE_QR,
        PAGE_COUNT
    };

    enum Act : uint8_t
    {
        ACT_BACK,
        ACT_TIMEOUT,
        ACT_HOUR,
        ACT_BT_TOGGLE,
        ACT_QR_PREV,
        ACT_QR_NEXT,
        ACT_COUNT
    };

    struct Action
    {
        UISystem* self;
        uint8_t id;
    };

    static void actionClicked(lv_event_t* event);
    static void sliderChanged(lv_event_t* event);
    static void sliderReleased(lv_event_t* event);
    static void openSettingsTile(void* user);
    static void openBluetoothTile(void* user);
    static void openContactsTile(void* user);
    static void openQrTile(void* user);

    void handle(uint8_t id);

    lv_obj_t* makeRoot(Page page, const char* title);
    lv_obj_t* addAction(lv_obj_t* parent, const char* text, int32_t x, int32_t y,
                        int32_t w, int32_t h, lv_color_t bg, lv_color_t fg, Act act);

    void buildSettings();
    void buildBluetooth();
    void buildContacts();
    void buildQr();

    void showPage(Page page);
    void loadPrefs();
    void savePrefs();
    void applyBrightness(uint8_t percent);
    void refreshSettingsLabels();
    void refreshBluetooth();
    void rebuildContacts();
    void rebuildQr();

    AppStateManager* appState = nullptr;
    ChronosManager* chronos = nullptr;
    UIApps* apps = nullptr;
    BrightnessHandler brightnessHandler = nullptr;

    Action actions[ACT_COUNT] = {};
    lv_obj_t* roots[PAGE_COUNT] = {};
    Page current = PAGE_NONE;

    // Settings
    uint8_t brightness = 100;
    uint8_t timeoutIdx = 4;
    bool h24 = true;
    bool dimmed = false;
    lv_obj_t* brightnessSlider = nullptr;
    lv_obj_t* brightnessLabel = nullptr;
    lv_obj_t* timeoutLabel = nullptr;
    lv_obj_t* hourLabel = nullptr;

    // Bluetooth
    lv_obj_t* btStatus = nullptr;
    lv_obj_t* btAddress = nullptr;
    lv_obj_t* btPhone = nullptr;
    lv_obj_t* btApp = nullptr;
    lv_obj_t* btToggleLabel = nullptr;

    // Contacts
    lv_obj_t* contactList = nullptr;

    // QR
    lv_obj_t* qrObj = nullptr;
    lv_obj_t* qrText = nullptr;
    lv_obj_t* qrIndex = nullptr;
    uint8_t qrIndices[PULSEON_MAX_QR] = {};
    uint8_t qrCount = 0;
    uint8_t qrPos = 0;

    // Wake-on-event tracking
    bool lastCall = false;
    int8_t lastAlarm = -1;
    uint8_t lastHead = 0;
    uint8_t lastStored = 0;
    uint32_t lastFind = 0;
    uint32_t lastConn = 0;

    uint32_t lastPollMs = 0;
    uint32_t lastRefreshMs = 0;
};
