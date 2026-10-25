#pragma once

#include <Arduino.h>
#include <ChronosESP32.h>
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>

#include "../app/AppState.h"

class ChronosManager
{
public:
    void begin();
    void loop();

    bool isConnected();
    bool isBluetoothOn() const;
    void setBluetoothEnabled(bool enabled);
    String getAddress();
    int getSosContactIndex();

    uint8_t getPhoneBattery();
    bool isPhoneCharging();

    int getNotificationCount();

    String getWeatherCity();
    String getClockText(bool is24Hour);
    String getClockPeriod();
    String getDateText();

    // ---- Chronos actions for the UI ----
    void controlMusic(Control command);
    void setVolume(uint8_t level);
    void findPhone(bool start);
    bool capturePhoto();
    void clearNotifications();

    void dismissAlarm();
    void snoozeAlarm(uint8_t minutes = 5);

    int getContactCount();
    Contact getContact(int index);

    void attachAppState(AppStateManager* appState);

private:
    // Chronos callbacks run on the BLE task. They only enqueue an event;
    // loop() drains the queue on the main task so AppState stays single-threaded.
    struct Event
    {
        enum Type : uint8_t
        {
            NONE,
            CONNECTION,
            NOTIFICATION,
            RINGER,
            CONFIG,
            HEALTH
        };

        Type type = NONE;
        bool flag = false;
        Config config{};
        uint32_t a = 0;
        uint32_t b = 0;
        HealthRequest health{};
        Notification notification;
        String text;
    };

    static constexpr uint8_t kQueueSize = 16;

    static ChronosManager* instance;

    static void connectionCallback(bool connected);
    static void notificationCallback(Notification notification);
    static void ringerCallback(String caller, bool state);
    static void configurationCallback(Config config, uint32_t a, uint32_t b);
    static void healthRequestCallback(HealthRequest request, bool state);

    void push(const Event& ev);
    bool pop(Event& ev);
    void dispatch(const Event& ev);

    void handleConnection(bool connected);
    void handleNotification(const Notification& notification);
    void handleRinger(const String& caller, bool state);
    void handleConfiguration(Config config, uint32_t a, uint32_t b);
    void handleHealthRequest(HealthRequest request, bool state);

    void pollPhoneState();
    void pollAlarms();

    void updateWeather();
    void updateNavigation();
    void updateAlarms();
    void updateQr();

    ChronosESP32 watch;

    bool connected = false;
    bool bluetoothOn = true;
    AppStateManager* appState = nullptr;

    HealthRequest activeHealthRequest = HR_HEART_RATE_MEASURE;
    bool healthMeasurementRunning = false;

    SemaphoreHandle_t queueMutex = nullptr;
    Event queue[kQueueSize];
    uint8_t queueHead = 0;
    uint8_t queueCount = 0;
    uint32_t droppedEvents = 0;
    uint32_t lastPollMs = 0;

    bool alarmPrimed = false;
    bool alarmWasActive[PULSEON_MAX_ALARMS] = {};
    int8_t snoozeAlarmIndex = -1;
    uint32_t snoozeUntilMs = 0;
};
