#pragma once

#include <Arduino.h>
#include <lvgl.h>

#include "../app/AppState.h"
#include "UIOverlays.h"
#include "UIApps.h"
#include "UISystem.h"
#include "UIHome.h"
#include "UITheme.h"

class ChronosManager;

class UIManager
{
public:
    enum Screen : uint8_t
    {
        SCREEN_WATCH_HOME = 0,
        SCREEN_COUNT
    };

    void begin(AppStateManager* appState);
    void update();
    void attachChronos(ChronosManager* chronosManager);
    void setBrightnessHandler(UISystem::BrightnessHandler handler);

    void showScreen(Screen screen, bool fade = false);
    Screen getCurrentScreen() const;

private:
    static void screenGestureCallback(lv_event_t* event);
    static void openFacePickerCallback(lv_event_t* event);
    static void selectHomeFaceCallback(lv_event_t* event);
    static void closeFacePickerCallback(lv_event_t* event);
    static void connectionToastTimerCallback(lv_timer_t* timer);

    void createScreens();
    void createFacePicker();
    void createConnectionToast();
    void showConnectionToast(bool connected);
    void updateScreens();
    void applyHomeFace();
    void rebuildClassicFaces();
    void restoreClock();
    void showToast(const char* text, lv_color_t color);
    static void stepGoalTile(void* user);
    lv_obj_t* createScreen(Screen screen);

    struct FaceSelectionContext
    {
        UIManager* manager;
        uint8_t face;
    };

    AppStateManager* appState = nullptr;
    ChronosManager* chronos = nullptr;
    Screen currentScreen = SCREEN_WATCH_HOME;

    lv_obj_t* screenRoots[SCREEN_COUNT] = {};
    lv_obj_t* facePickerRoot = nullptr;
    lv_obj_t* connectionToast = nullptr;
    lv_obj_t* connectionToastLabel = nullptr;
    lv_timer_t* connectionToastTimer = nullptr;
    lv_obj_t* homeFaces[9] = {};
    lv_obj_t* faceSelectionButtons[9] = {};
    FaceSelectionContext faceSelectionContexts[9] = {};
    uint8_t selectedHomeFace = 0;
    uint8_t homeThemeIndex = 0;
    uint32_t lastThemePollMs = 0;
    uint16_t stepGoal = 10000;

    lv_obj_t* faceClock[6] = {};
    lv_obj_t* faceDate[6] = {};
    lv_obj_t* faceHeart[6] = {};
    lv_obj_t* faceSteps[6] = {};
    lv_obj_t* faceBattery[6] = {};
    lv_obj_t* faceWeather[6] = {};
    lv_obj_t* faceOxygen[6] = {};
    Screen facePickerReturnScreen = SCREEN_WATCH_HOME;

    uint32_t lastUpdateMs = 0;
    uint32_t lastPhoneConnectionEventId = 0;

    UIOverlays overlays;
    UIApps apps;
    UISystem sysui;
};
