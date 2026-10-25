#pragma once

#include <Arduino.h>
#include <lvgl.h>

#include "../app/AppState.h"
#include "UIOverlays.h"

class ChronosManager;

class UIManager
{
public:
    enum Screen : uint8_t
    {
        SCREEN_WATCH_HOME = 0,
        SCREEN_HEART_RATE,
        SCREEN_SLEEP,
        SCREEN_ACTIVITY,
        SCREEN_BLOOD_OXYGEN,
        SCREEN_WORKOUT,
        SCREEN_COUNT
    };

    void begin(AppStateManager* appState);
    void update();
    void attachChronos(ChronosManager* chronosManager);

    void showScreen(Screen screen, bool fade = false);
    Screen getCurrentScreen() const;

private:
    static void screenGestureCallback(lv_event_t* event);
    static void openFacePickerCallback(lv_event_t* event);
    static void selectHomeFaceCallback(lv_event_t* event);
    static void closeFacePickerCallback(lv_event_t* event);
    static void workoutModeCallback(lv_event_t* event);
    static void workoutStartCallback(lv_event_t* event);
    static void connectionToastTimerCallback(lv_timer_t* timer);

    void createScreens();
    void createFacePicker();
    void createConnectionToast();
    void showConnectionToast(bool connected);
    void updateScreens();
    void applyHomeFace();
    lv_obj_t* createScreen(Screen screen);

    struct FaceSelectionContext
    {
        UIManager* manager;
        uint8_t face;
    };

    struct WorkoutModeContext
    {
        UIManager* manager;
        uint8_t mode;
    };

    AppStateManager* appState = nullptr;
    ChronosManager* chronos = nullptr;
    Screen currentScreen = SCREEN_WATCH_HOME;

    lv_obj_t* screenRoots[SCREEN_COUNT] = {};
    lv_obj_t* facePickerRoot = nullptr;
    lv_obj_t* connectionToast = nullptr;
    lv_obj_t* connectionToastLabel = nullptr;
    lv_timer_t* connectionToastTimer = nullptr;
    lv_obj_t* homeFaces[6] = {};
    lv_obj_t* faceSelectionButtons[6] = {};
    FaceSelectionContext faceSelectionContexts[6] = {};
    uint8_t selectedHomeFace = 0;

    lv_obj_t* faceClock[6] = {};
    lv_obj_t* faceDate[6] = {};
    lv_obj_t* faceHeart[6] = {};
    lv_obj_t* faceSteps[6] = {};
    lv_obj_t* faceBattery[6] = {};
    lv_obj_t* faceWeather[6] = {};
    lv_obj_t* faceOxygen[6] = {};
    Screen facePickerReturnScreen = SCREEN_WATCH_HOME;

    lv_obj_t* heartRateValue = nullptr;
    lv_obj_t* heartRateStatus = nullptr;
    lv_obj_t* sleepDuration = nullptr;
    lv_obj_t* sleepStatus = nullptr;
    lv_obj_t* activitySteps = nullptr;
    lv_obj_t* activityCalories = nullptr;
    lv_obj_t* oxygenValue = nullptr;
    lv_obj_t* oxygenStatus = nullptr;
    lv_obj_t* workoutStatus = nullptr;
    lv_obj_t* workoutModeButtons[3] = {};
    WorkoutModeContext workoutModeContexts[3] = {};
    uint8_t selectedWorkoutMode = 0;

    uint32_t lastUpdateMs = 0;
    uint32_t lastPhoneConnectionEventId = 0;

    UIOverlays overlays;
};
