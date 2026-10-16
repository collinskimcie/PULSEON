#pragma once

#include <Arduino.h>
#include <ChronosESP32.h>

#include "../app/AppState.h"

class ChronosManager
{
public:
    void begin();
    void loop();

    bool isConnected();

    uint8_t getPhoneBattery();
    bool isPhoneCharging();

    int getNotificationCount();

    String getWeatherCity();
    String getClockText(bool is24Hour);
    String getClockPeriod();
    String getDateText();
    void controlMusic(Control command);

    void attachAppState(AppStateManager* appState);

private:
    static ChronosManager* instance;

    static void connectionCallback(bool connected);
    static void notificationCallback(Notification notification);
    static void ringerCallback(String caller, bool state);

    static void configurationCallback(
        Config config,
        uint32_t a,
        uint32_t b
    );

    static void healthRequestCallback(
        HealthRequest request,
        bool state
    );

    void handleConnection(bool connected);
    void handleNotification(Notification notification);
    void handleRinger(String caller, bool state);

    void handleConfiguration(
        Config config,
        uint32_t a,
        uint32_t b
    );

    void handleHealthRequest(
        HealthRequest request,
        bool state
    );

    void updateWeather();

    ChronosESP32 watch;

    bool connected = false;

    AppStateManager* appState = nullptr;

    HealthRequest activeHealthRequest = HR_HEART_RATE_MEASURE;
    bool healthMeasurementRunning = false;
};
