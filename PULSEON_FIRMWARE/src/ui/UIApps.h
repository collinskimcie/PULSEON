#pragma once

#include <Arduino.h>
#include <lvgl.h>

#include "../app/AppState.h"

class ChronosManager;
class UIOverlays;

// App launcher plus Music, Weather, Alarms, Find phone and Camera pages.
// Everything lives on lv_layer_top(), so it works over any screen.
class UIApps
{
public:
    void begin(AppStateManager* appState, ChronosManager* chronos, UIOverlays* overlays);
    void poll();
    void show();
    void showMusic();
    bool isVisible() const;

    typedef void (*TileHandler)(void* user);
    void addTile(const char* text, TileHandler handler, void* user);

private:
    enum Page : uint8_t
    {
        PAGE_NONE = 0,
        PAGE_APPS,
        PAGE_MUSIC,
        PAGE_WEATHER,
        PAGE_ALARMS,
        PAGE_FIND,
        PAGE_CAMERA,
        PAGE_COUNT
    };

    enum Act : uint8_t
    {
        ACT_OPEN_MUSIC,
        ACT_OPEN_WEATHER,
        ACT_OPEN_ALARMS,
        ACT_OPEN_FIND,
        ACT_OPEN_CAMERA,
        ACT_OPEN_ALERTS,
        ACT_CLOSE,
        ACT_BACK,
        ACT_MUSIC_PREV,
        ACT_MUSIC_TOGGLE,
        ACT_MUSIC_NEXT,
        ACT_VOL_DOWN,
        ACT_VOL_MUTE,
        ACT_VOL_UP,
        ACT_FIND_TOGGLE,
        ACT_CAMERA_SHOOT,
        ACT_COUNT
    };

    struct Action
    {
        UIApps* self;
        uint8_t id;
    };

    static void actionClicked(lv_event_t* event);
    void handle(uint8_t id);

    lv_obj_t* makeRoot(Page page, const char* title);
    lv_obj_t* addAction(lv_obj_t* parent, const char* text, int32_t x, int32_t y,
                        int32_t w, int32_t h, lv_color_t bg, lv_color_t fg, Act act);

    void buildApps();
    void buildMusic();
    void buildWeather();
    void buildAlarms();
    void buildFind();
    void buildCamera();

    void showPage(Page page);
    void refreshWeather();
    void refreshAlarms();
    void refreshStatus();
    void stopFinding();
    void setFindLabel();

    AppStateManager* appState = nullptr;
    ChronosManager* chronos = nullptr;
    UIOverlays* overlays = nullptr;

    Action actions[ACT_COUNT] = {};
    lv_obj_t* roots[PAGE_COUNT] = {};
    Page current = PAGE_NONE;

    lv_obj_t* weatherCity = nullptr;
    lv_obj_t* weatherTemp = nullptr;
    lv_obj_t* weatherRange = nullptr;
    lv_obj_t* weatherList = nullptr;
    lv_obj_t* alarmList = nullptr;
    lv_obj_t* findStatus = nullptr;
    lv_obj_t* findButtonLabel = nullptr;
    lv_obj_t* cameraStatus = nullptr;

    bool findingPhone = false;

    struct ExtraTile
    {
        UIApps* self;
        TileHandler handler;
        void* user;
    };
    static constexpr uint8_t kMaxExtraTiles = 8;
    static void extraTileClicked(lv_event_t* event);
    ExtraTile extraTiles[kMaxExtraTiles] = {};
    uint8_t extraTileCount = 0;
    uint8_t tileCount = 0;
    lv_obj_t* tileArea = nullptr;
    uint32_t lastPollMs = 0;
};
