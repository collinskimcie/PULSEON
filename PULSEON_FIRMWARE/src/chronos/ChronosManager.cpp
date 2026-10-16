#include "ChronosManager.h"

ChronosManager* ChronosManager::instance = nullptr;

void ChronosManager::begin()
{
    instance = this;

    Serial.println("[CHRONOS] Initializing...");

    watch.setName("PULSEON");
    watch.setScreen(CS_0x0_000_CFF);

    watch.setConnectionCallback(connectionCallback);
    watch.setNotificationCallback(notificationCallback);
    watch.setRingerCallback(ringerCallback);
    watch.setConfigurationCallback(configurationCallback);
    watch.setHealthRequestCallback(healthRequestCallback);

    watch.begin();

    Serial.println("[CHRONOS] Started");
    Serial.println("[CHRONOS] Bluetooth name: PULSEON");
}

void ChronosManager::loop()
{
    watch.loop();

    if (appState != nullptr)
    {
        appState->setPhoneBattery(
            watch.getPhoneBattery()
        );

        appState->setPhoneCharging(
            watch.isPhoneCharging()
        );

        appState->setNotificationCount(
            watch.getNotificationCount()
        );

        updateWeather();
    }
}

void ChronosManager::updateWeather()
{
    if (appState == nullptr)
    {
        return;
    }

    int weatherCount = watch.getWeatherCount();

    if (weatherCount <= 0)
    {
        return;
    }

    Weather weather = watch.getWeatherAt(0);

    String city = watch.getWeatherCity();

    appState->setWeather(
        city,
        weather.temp,
        weather.high,
        weather.low
    );
}

bool ChronosManager::isConnected()
{
    return connected;
}

uint8_t ChronosManager::getPhoneBattery()
{
    return watch.getPhoneBattery();
}

bool ChronosManager::isPhoneCharging()
{
    return watch.isPhoneCharging();
}

int ChronosManager::getNotificationCount()
{
    return watch.getNotificationCount();
}

String ChronosManager::getWeatherCity()
{
    return watch.getWeatherCity();
}

String ChronosManager::getClockText(bool is24Hour)
{
    return watch.getTime(is24Hour ? "%H:%M" : "%I:%M");
}

String ChronosManager::getClockPeriod()
{
    return watch.getAmPmC();
}

String ChronosManager::getDateText()
{
    return watch.getTime("%a %d %b");
}

void ChronosManager::controlMusic(Control command)
{
    watch.musicControl(command);
}

void ChronosManager::attachAppState(AppStateManager* state)
{
    appState = state;
}

void ChronosManager::connectionCallback(bool state)
{
    if (instance != nullptr)
    {
        instance->handleConnection(state);
    }
}

void ChronosManager::notificationCallback(Notification notification)
{
    if (instance != nullptr)
    {
        instance->handleNotification(notification);
    }
}

void ChronosManager::ringerCallback(String caller, bool state)
{
    if (instance != nullptr)
    {
        instance->handleRinger(caller, state);
    }
}

void ChronosManager::configurationCallback(
    Config config,
    uint32_t a,
    uint32_t b
)
{
    if (instance != nullptr)
    {
        instance->handleConfiguration(config, a, b);
    }
}

void ChronosManager::healthRequestCallback(
    HealthRequest request,
    bool state
)
{
    if (instance != nullptr)
    {
        instance->handleHealthRequest(request, state);
    }
}

void ChronosManager::handleConnection(bool state)
{
    connected = state;

    if (appState != nullptr)
    {
        appState->setPhoneConnection(state);
    }

    Serial.print("[CHRONOS] Connection: ");
    Serial.println(
        connected
            ? "CONNECTED"
            : "DISCONNECTED"
    );
}

void ChronosManager::handleNotification(Notification notification)
{
    Serial.println("[CHRONOS] Notification");

    Serial.print("  App: ");
    Serial.println(notification.app);

    Serial.print("  Time: ");
    Serial.println(notification.time);

    Serial.print("  Title: ");
    Serial.println(notification.title);

    Serial.print("  Message: ");
    Serial.println(notification.message);

    if (appState != nullptr)
    {
        appState->setNotification(
            notification.app,
            notification.time,
            notification.title,
            notification.message
        );

        appState->setNotificationCount(
            watch.getNotificationCount()
        );
    }
}

void ChronosManager::handleRinger(String caller, bool state)
{
    if (state)
    {
        Serial.print("[CHRONOS] Incoming call: ");
        Serial.println(caller);
    }
    else
    {
        Serial.println("[CHRONOS] Ringer dismissed");
    }
}

void ChronosManager::handleConfiguration(
    Config config,
    uint32_t a,
    uint32_t b
)
{
    Serial.print("[CHRONOS] Configuration: ");
    Serial.print(static_cast<int>(config));
    Serial.print(" a=");
    Serial.print(a);
    Serial.print(" b=");
    Serial.println(b);

    if (appState == nullptr)
    {
        return;
    }

    switch (config)
    {
        case CF_TIME:
            appState->setClockSynced(a == 1);

            if (a == 1)
            {
                Serial.println("[CHRONOS] Clock synchronized from phone");
            }
            break;

        case CF_HR24:
            appState->set24Hour(b != 0);

            Serial.print("[CHRONOS] 24-hour mode: ");
            Serial.println(b ? "ON" : "OFF");
            break;

        case CF_PBAT:
            appState->setPhoneBattery(
                static_cast<uint8_t>(b)
            );

            Serial.print("[CHRONOS] Phone battery: ");
            Serial.print(b);
            Serial.println("%");
            break;

        case CF_WEATHER:
            updateWeather();

            Serial.println("[CHRONOS] Weather update");
            break;

        case CF_NAV_DATA:
            appState->setNavigationActive(true);

            Serial.println("[CHRONOS] Navigation data");
            break;

        case CF_NAV_ICON:
            Serial.println("[CHRONOS] Navigation icon");
            break;

        case CF_CAMERA:
            appState->setCameraReady(b != 0);

            Serial.print("[CHRONOS] Camera: ");
            Serial.println(
                b ? "READY" : "NOT READY"
            );
            break;

        case CF_SYNCED:
            appState->setSynchronized(true);

            Serial.println(
                "[CHRONOS] Synchronization complete"
            );
            break;

        default:
            break;
    }
}

void ChronosManager::handleHealthRequest(
    HealthRequest request,
    bool state
)
{
    switch (request)
    {
        case HR_STEPS_RECORDS:
            Serial.println(
                "[CHRONOS] Health request: STEPS RECORDS"
            );
            break;

        case HR_SLEEP_RECORDS:
            Serial.println(
                "[CHRONOS] Health request: SLEEP RECORDS"
            );
            break;

        case HR_HEART_RATE_MEASURE:
            activeHealthRequest = request;
            healthMeasurementRunning = state;

            Serial.print(
                "[CHRONOS] Heart-rate measurement: "
            );
            Serial.println(
                state ? "START" : "STOP"
            );
            break;

        case HR_BLOOD_OXYGEN_MEASURE:
            activeHealthRequest = request;
            healthMeasurementRunning = state;

            Serial.print(
                "[CHRONOS] Blood-oxygen measurement: "
            );
            Serial.println(
                state ? "START" : "STOP"
            );
            break;

        case HR_BLOOD_PRESSURE_MEASURE:
            activeHealthRequest = request;
            healthMeasurementRunning = state;

            Serial.print(
                "[CHRONOS] Blood-pressure measurement: "
            );
            Serial.println(
                state ? "START" : "STOP"
            );
            break;

        case HR_MEASURE_ALL:
            activeHealthRequest = request;
            healthMeasurementRunning = state;

            Serial.print(
                "[CHRONOS] All health measurements: "
            );
            Serial.println(
                state ? "START" : "STOP"
            );
            break;

        default:
            Serial.println(
                "[CHRONOS] Unknown health request"
            );
            break;
    }
}
