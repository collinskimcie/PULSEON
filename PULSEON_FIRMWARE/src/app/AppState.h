#pragma once

#include <Arduino.h>

struct PulseonAppState
{
    // Watch / phone connection
    bool phoneConnected = false;
    uint8_t phoneBattery = 0;
    bool phoneCharging = false;

    // Notifications
    int notificationCount = 0;
    String notificationApp = "";
    String notificationTime = "";
    String notificationTitle = "";
    String notificationMessage = "";

    // Weather
    String weatherCity = "";
    int weatherTemperature = 0;
    int weatherHigh = 0;
    int weatherLow = 0;
    bool weatherAvailable = false;

    // Watch configuration
    bool is24Hour = true;
    bool clockSynced = false;

    // Navigation
    bool navigationActive = false;

    // Camera
    bool cameraReady = false;

    // Synchronization
    bool synchronized = false;

    // Health data
    uint16_t steps = 0;
    uint16_t heartRate = 0;
    uint8_t bloodOxygen = 0;

    // UI state
    uint8_t activeScreen = 0;
};

class AppStateManager
{
public:
    void begin();

    const PulseonAppState& getState() const;

    void setPhoneConnection(bool connected);
    void setPhoneBattery(uint8_t battery);
    void setPhoneCharging(bool charging);

    void setNotificationCount(int count);

    void setNotification(
        const String& app,
        const String& time,
        const String& title,
        const String& message
    );

    void setWeatherCity(const String& city);

    void setWeather(
        const String& city,
        int temperature,
        int high,
        int low
    );

    void set24Hour(bool enabled);
    void setClockSynced(bool synced);
    void setNavigationActive(bool active);
    void setCameraReady(bool ready);
    void setSynchronized(bool synced);

    void setSteps(uint16_t value);
    void setHeartRate(uint16_t value);
    void setBloodOxygen(uint8_t value);

    void setActiveScreen(uint8_t screen);

private:
    PulseonAppState state;
};
