#include "AppState.h"

void AppStateManager::begin()
{
    state = PulseonAppState();

    Serial.println("[APP] Application state initialized");
}

const PulseonAppState& AppStateManager::getState() const
{
    return state;
}

void AppStateManager::setPhoneConnection(bool connected)
{
    if (state.phoneConnected != connected)
    {
        ++state.phoneConnectionEventId;
    }
    state.phoneConnected = connected;
}

void AppStateManager::setPhoneBattery(uint8_t battery)
{
    state.phoneBattery = battery;
}

void AppStateManager::setPhoneCharging(bool charging)
{
    state.phoneCharging = charging;
}

void AppStateManager::setNotificationCount(int count)
{
    state.notificationCount = count;
}

void AppStateManager::setNotification(
    const String& app,
    const String& time,
    const String& title,
    const String& message
)
{
    state.notificationApp = app;
    state.notificationTime = time;
    state.notificationTitle = title;
    state.notificationMessage = message;
}

void AppStateManager::setWeatherCity(const String& city)
{
    state.weatherCity = city;
}

void AppStateManager::setWeather(
    const String& city,
    int temperature,
    int high,
    int low
)
{
    state.weatherCity = city;
    state.weatherTemperature = temperature;
    state.weatherHigh = high;
    state.weatherLow = low;
    state.weatherAvailable = true;
}

void AppStateManager::set24Hour(bool enabled)
{
    state.is24Hour = enabled;
}

void AppStateManager::setClockSynced(bool synced)
{
    state.clockSynced = synced;
}

void AppStateManager::setNavigationActive(bool active)
{
    state.navigationActive = active;
}

void AppStateManager::setCameraReady(bool ready)
{
    state.cameraReady = ready;
}

void AppStateManager::setSynchronized(bool synced)
{
    state.synchronized = synced;
}

void AppStateManager::setSteps(uint16_t value)
{
    state.steps = value;
}

void AppStateManager::setHeartRate(uint16_t value)
{
    state.heartRate = value;
}

void AppStateManager::setBloodOxygen(uint8_t value)
{
    state.bloodOxygen = value;
}

void AppStateManager::setActiveScreen(uint8_t screen)
{
    state.activeScreen = screen;
}
