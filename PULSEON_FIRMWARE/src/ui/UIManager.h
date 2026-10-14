#pragma once

#include <Arduino.h>
#include <lvgl.h>

#include "../app/AppState.h"

class UIManager
{
public:
    enum Screen : uint8_t
    {
        SCREEN_WATCH_HOME = 0,
        SCREEN_NOTIFICATIONS,
        SCREEN_QUICK_CONTROLS,
        SCREEN_HEALTH,
        SCREEN_WEATHER,
        SCREEN_MUSIC,
        SCREEN_SETTINGS,
        SCREEN_COUNT
    };

    void begin(AppStateManager* appState);
    void update();

    void showScreen(Screen screen);
    Screen getCurrentScreen() const;

private:
    void createScreens();

    void createWatchHome();
    void updateWatchHome();

    void createNotifications();
    void updateNotifications();

    void createWeather();
    void updateWeather();

    void updateActiveScreen();

    AppStateManager* appState = nullptr;

    Screen currentScreen = SCREEN_WATCH_HOME;

    // Screens
    lv_obj_t* watchHome = nullptr;
    lv_obj_t* notifications = nullptr;
    lv_obj_t* quickControls = nullptr;
    lv_obj_t* health = nullptr;
    lv_obj_t* weather = nullptr;
    lv_obj_t* music = nullptr;
    lv_obj_t* settings = nullptr;

    // WatchHome
    lv_obj_t* dateLabel = nullptr;
    lv_obj_t* bluetoothLabel = nullptr;
    lv_obj_t* batteryLabel = nullptr;
    lv_obj_t* timeLabel = nullptr;
    lv_obj_t* periodLabel = nullptr;

    lv_obj_t* heartRateLabel = nullptr;
    lv_obj_t* weatherLabel = nullptr;
    lv_obj_t* stepsLabel = nullptr;
    lv_obj_t* activityLabel = nullptr;

    // Notifications
    lv_obj_t* notificationTitleLabel = nullptr;
    lv_obj_t* notificationAppLabel = nullptr;
    lv_obj_t* notificationMessageLabel = nullptr;
    lv_obj_t* notificationPhoneLabel = nullptr;
    lv_obj_t* notificationPhoneStatusLabel = nullptr;
    lv_obj_t* notificationRefreshLabel = nullptr;

    // Weather
    lv_obj_t* weatherTemperatureLabel = nullptr;
    lv_obj_t* weatherConditionLabel = nullptr;
    lv_obj_t* weatherLowLabel = nullptr;
    lv_obj_t* weatherHighLabel = nullptr;
    lv_obj_t* weatherCityLabel = nullptr;
};
