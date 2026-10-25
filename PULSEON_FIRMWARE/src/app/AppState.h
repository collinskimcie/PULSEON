#pragma once

#include <Arduino.h>

constexpr uint8_t PULSEON_MAX_NOTIFICATIONS = 10;
constexpr uint8_t PULSEON_MAX_FORECAST_DAYS = 7;
constexpr uint8_t PULSEON_MAX_ALARMS = 8;
constexpr uint8_t PULSEON_MAX_QR = 9;
constexpr uint16_t PULSEON_NAV_ICON_BYTES = 288; // 48x48, 1 bit per pixel

struct PulseonNotification
{
    int icon = 0;
    String app;
    String time;
    String title;
    String message;
};

struct PulseonForecastDay
{
    int icon = 0;
    int day = 0;
    int temp = 0;
    int high = 0;
    int low = 0;
};

struct PulseonNavigation
{
    bool active = false;
    bool isNavigation = false;
    bool hasIcon = false;
    String distance;
    String duration;
    String eta;
    String title;
    String directions;
    String speed;
    uint32_t iconCRC = 0;
    uint8_t icon[PULSEON_NAV_ICON_BYTES] = {};
};

struct PulseonAlarm
{
    uint8_t hour = 0;
    uint8_t minute = 0;
    uint8_t repeat = 0;
    bool enabled = false;
};

struct PulseonAppState
{
    // Watch / phone connection
    bool phoneConnected = false;
    uint32_t phoneConnectionEventId = 0;
    uint8_t phoneBattery = 0;
    bool phoneCharging = false;

    // Notifications
    int notificationCount = 0;
    String notificationApp = "";
    String notificationTime = "";
    String notificationTitle = "";
    String notificationMessage = "";

    // Notification history (ring buffer; use getNotification(0) for newest)
    PulseonNotification notifications[PULSEON_MAX_NOTIFICATIONS];
    uint8_t notificationStored = 0;
    uint8_t notificationHead = 0;

    // Calls
    bool callActive = false;
    String callerName = "";

    // Weather
    String weatherCity = "";
    int weatherTemperature = 0;
    int weatherHigh = 0;
    int weatherLow = 0;
    bool weatherAvailable = false;
    String weatherTime = "";
    int weatherIcon = 0;
    PulseonForecastDay weatherDays[PULSEON_MAX_FORECAST_DAYS];
    uint8_t weatherDayCount = 0;

    // Watch configuration
    bool is24Hour = true;
    bool clockSynced = false;

    // Navigation
    bool navigationActive = false;
    PulseonNavigation navigation;

    // Camera
    bool cameraReady = false;

    // Synchronization
    bool synchronized = false;

    // Alarms (ringing index, or -1)
    PulseonAlarm alarms[PULSEON_MAX_ALARMS];
    int8_t alarmRinging = -1;

    // QR codes sent from the Chronos app
    String qrCodes[PULSEON_MAX_QR];

    // "Find watch" requests from the phone (UI reacts when the id changes)
    uint32_t findWatchEventId = 0;

    // Chronos app info
    String appVersion = "";

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

    // ---- Chronos feature state (implemented in AppStateChronos.cpp) ----
    void addNotification(
        const String& app,
        const String& time,
        const String& title,
        const String& message,
        int icon = 0
    );
    void clearNotifications();
    const PulseonNotification* getNotification(uint8_t index) const;

    void setIncomingCall(const String& caller, bool active);

    void setWeatherForecast(
        const String& city,
        const String& updated,
        const PulseonForecastDay* days,
        uint8_t count
    );

    void setNavigationData(const PulseonNavigation& nav);
    void clearNavigation();

    void setAlarms(const PulseonAlarm* alarms, uint8_t count);
    void setAlarmRinging(int8_t index);

    void setQr(uint8_t index, const String& value);
    void requestFindWatch();
    void setAppVersion(const String& version);

private:
    PulseonAppState state;
};
