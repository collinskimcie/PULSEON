#include "ChronosManager.h"

#include <string.h>

static_assert(PULSEON_MAX_NOTIFICATIONS == NOTIF_SIZE, "notification size mismatch");
static_assert(PULSEON_MAX_FORECAST_DAYS == WEATHER_SIZE, "weather size mismatch");
static_assert(PULSEON_MAX_ALARMS == ALARM_SIZE, "alarm size mismatch");
static_assert(PULSEON_MAX_QR == QR_SIZE, "qr size mismatch");
static_assert(PULSEON_NAV_ICON_BYTES == ((CHRONOS_ICON_SIZE * CHRONOS_ICON_SIZE) / 8),
              "navigation icon size mismatch");

ChronosManager* ChronosManager::instance = nullptr;

// ------------------------------------------------------------------
// Lifecycle
// ------------------------------------------------------------------

void ChronosManager::begin()
{
    instance = this;

    if (queueMutex == nullptr)
    {
        queueMutex = xSemaphoreCreateMutex();
    }

    Serial.println("[CHRONOS] Initializing...");

    watch.setName("PULSEON");
    // Identifies this board (Viewe 240x320) in the Chronos app.
    watch.setScreen(CF_VIEWE_28_240x320);

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

    // Drain a bounded number of events per pass so the UI never stalls.
    Event ev;
    for (uint8_t i = 0; i < 8 && pop(ev); ++i)
    {
        dispatch(ev);
    }

    if (droppedEvents != 0)
    {
        Serial.printf("[CHRONOS] WARNING: %lu events dropped\n",
                      static_cast<unsigned long>(droppedEvents));
        droppedEvents = 0;
    }

    const uint32_t now = millis();
    if (now - lastPollMs >= 1000)
    {
        lastPollMs = now;
        pollPhoneState();
        pollAlarms();
    }
}

void ChronosManager::pollPhoneState()
{
    if (appState == nullptr)
    {
        return;
    }

    appState->setPhoneBattery(watch.getPhoneBattery());
    appState->setPhoneCharging(watch.isPhoneCharging());
    appState->setNotificationCount(watch.getNotificationCount());
}

// ------------------------------------------------------------------
// Alarms (the library has no alarm callback, so we poll once a second)
// ------------------------------------------------------------------

void ChronosManager::pollAlarms()
{
    if (appState == nullptr)
    {
        return;
    }

    const PulseonAppState& st = appState->getState();

    // Without a phone-synced clock the RTC is meaningless.
    if (!st.clockSynced)
    {
        alarmPrimed = false;
        return;
    }

    for (uint8_t i = 0; i < PULSEON_MAX_ALARMS; ++i)
    {
        const bool active = watch.isAlarmActive(i);

        // Ring on the false -> true edge only, and never on the first pass
        // after sync (avoids ringing an alarm that is already "active").
        if (alarmPrimed && active && !alarmWasActive[i] && st.alarmRinging < 0)
        {
            appState->setAlarmRinging(static_cast<int8_t>(i));
            Serial.printf("[CHRONOS] Alarm %u ringing\n", static_cast<unsigned>(i));
        }

        alarmWasActive[i] = active;
    }

    alarmPrimed = true;

    if (snoozeAlarmIndex >= 0 &&
        st.alarmRinging < 0 &&
        static_cast<int32_t>(millis() - snoozeUntilMs) >= 0)
    {
        appState->setAlarmRinging(snoozeAlarmIndex);
        snoozeAlarmIndex = -1;
    }
}

void ChronosManager::dismissAlarm()
{
    snoozeAlarmIndex = -1;

    if (appState != nullptr)
    {
        appState->setAlarmRinging(-1);
    }
}

void ChronosManager::snoozeAlarm(uint8_t minutes)
{
    if (appState == nullptr)
    {
        return;
    }

    const int8_t ringing = appState->getState().alarmRinging;
    if (ringing < 0)
    {
        return;
    }

    snoozeAlarmIndex = ringing;
    snoozeUntilMs = millis() + static_cast<uint32_t>(minutes) * 60000UL;
    appState->setAlarmRinging(-1);
}

// ------------------------------------------------------------------
// Data copied from the library into AppState
// ------------------------------------------------------------------

void ChronosManager::updateWeather()
{
    if (appState == nullptr)
    {
        return;
    }

    int count = watch.getWeatherCount();

    if (count <= 0)
    {
        return;
    }

    if (count > PULSEON_MAX_FORECAST_DAYS)
    {
        count = PULSEON_MAX_FORECAST_DAYS;
    }

    PulseonForecastDay days[PULSEON_MAX_FORECAST_DAYS];

    for (int i = 0; i < count; ++i)
    {
        const Weather w = watch.getWeatherAt(i);
        days[i].icon = w.icon;
        days[i].day = w.day;
        days[i].temp = w.temp;
        days[i].high = w.high;
        days[i].low = w.low;
    }

    appState->setWeatherForecast(
        watch.getWeatherCity(),
        watch.getWeatherTime(),
        days,
        static_cast<uint8_t>(count)
    );
}

void ChronosManager::updateNavigation()
{
    if (appState == nullptr)
    {
        return;
    }

    const Navigation n = watch.getNavigation();

    PulseonNavigation p;
    p.active = n.active;
    p.isNavigation = n.isNavigation;
    p.hasIcon = n.hasIcon;
    p.distance = n.distance;
    p.duration = n.duration;
    p.eta = n.eta;
    p.title = n.title;
    p.directions = n.directions;
    p.speed = n.speed;
    p.iconCRC = n.iconCRC;

    if (n.hasIcon)
    {
        memcpy(p.icon, n.icon, sizeof(p.icon));
    }

    appState->setNavigationData(p);
}

void ChronosManager::updateAlarms()
{
    if (appState == nullptr)
    {
        return;
    }

    PulseonAlarm alarms[PULSEON_MAX_ALARMS];

    for (uint8_t i = 0; i < PULSEON_MAX_ALARMS; ++i)
    {
        const Alarm a = watch.getAlarm(i);
        alarms[i].hour = a.hour;
        alarms[i].minute = a.minute;
        alarms[i].repeat = a.repeat;
        alarms[i].enabled = a.enabled;
    }

    appState->setAlarms(alarms, PULSEON_MAX_ALARMS);
}

void ChronosManager::updateQr()
{
    if (appState == nullptr)
    {
        return;
    }

    for (uint8_t i = 0; i < PULSEON_MAX_QR; ++i)
    {
        appState->setQr(i, watch.getQrAt(i));
    }
}

// ------------------------------------------------------------------
// Event queue
// ------------------------------------------------------------------

void ChronosManager::push(const Event& ev)
{
    if (queueMutex == nullptr)
    {
        return;
    }

    xSemaphoreTake(queueMutex, portMAX_DELAY);
    if (queueCount < kQueueSize)
    {
        Event& slot = queue[(queueHead + queueCount) % kQueueSize];
        slot = ev;
        slot.queuedMs = millis();
        ++queueCount;
    }
    else
    {
        ++droppedEvents;
    }
    xSemaphoreGive(queueMutex);
}

bool ChronosManager::pop(Event& ev)
{
    if (queueMutex == nullptr)
    {
        return false;
    }

    bool have = false;
    xSemaphoreTake(queueMutex, portMAX_DELAY);
    if (queueCount > 0)
    {
        ev = queue[queueHead];
        queue[queueHead] = Event();
        queueHead = (queueHead + 1) % kQueueSize;
        --queueCount;
        have = true;
    }
    xSemaphoreGive(queueMutex);
    return have;
}

void ChronosManager::dispatch(const Event& ev)
{
    if (ev.type == Event::NOTIFICATION || ev.type == Event::RINGER)
    {
        Serial.printf("[CHRONOS] queue wait %lu ms\n", static_cast<unsigned long>(millis() - ev.queuedMs));
    }

    switch (ev.type)
    {
        case Event::CONNECTION:   handleConnection(ev.flag); break;
        case Event::NOTIFICATION: handleNotification(ev.notification); break;
        case Event::RINGER:       handleRinger(ev.text, ev.flag); break;
        case Event::CONFIG:       handleConfiguration(ev.config, ev.a, ev.b); break;
        case Event::HEALTH:       handleHealthRequest(ev.health, ev.flag); break;
        default: break;
    }
}

// ------------------------------------------------------------------
// Accessors and actions
// ------------------------------------------------------------------

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

void ChronosManager::setVolume(uint8_t level)
{
    watch.setVolume(level);
}

void ChronosManager::findPhone(bool start)
{
    watch.findPhone(start);
}

bool ChronosManager::capturePhoto()
{
    return watch.capturePhoto();
}

void ChronosManager::clearNotifications()
{
    watch.clearNotifications();

    if (appState != nullptr)
    {
        appState->clearNotifications();
    }
}

int ChronosManager::getContactCount()
{
    return watch.getContactCount();
}

Contact ChronosManager::getContact(int index)
{
    return watch.getContact(index);
}

void ChronosManager::attachAppState(AppStateManager* state)
{
    appState = state;
}

// ------------------------------------------------------------------
// Library callbacks (BLE task): enqueue only
// ------------------------------------------------------------------

void ChronosManager::connectionCallback(bool state)
{
    if (instance == nullptr) return;
    Event ev;
    ev.type = Event::CONNECTION;
    ev.flag = state;
    instance->push(ev);
}

void ChronosManager::notificationCallback(Notification notification)
{
    if (instance == nullptr) return;
    Event ev;
    ev.type = Event::NOTIFICATION;
    ev.notification = notification;
    instance->push(ev);
}

void ChronosManager::ringerCallback(String caller, bool state)
{
    if (instance == nullptr) return;
    Event ev;
    ev.type = Event::RINGER;
    ev.text = caller;
    ev.flag = state;
    instance->push(ev);
}

void ChronosManager::configurationCallback(Config config, uint32_t a, uint32_t b)
{
    if (instance == nullptr) return;
    Event ev;
    ev.type = Event::CONFIG;
    ev.config = config;
    ev.a = a;
    ev.b = b;
    instance->push(ev);
}

void ChronosManager::healthRequestCallback(HealthRequest request, bool state)
{
    if (instance == nullptr) return;
    Event ev;
    ev.type = Event::HEALTH;
    ev.health = request;
    ev.flag = state;
    instance->push(ev);
}

// ------------------------------------------------------------------
// Handlers (main task)
// ------------------------------------------------------------------

void ChronosManager::handleConnection(bool state)
{
    connected = state;
    if (state)
    {
        connectedAtMs = millis();
    }

    if (appState != nullptr)
    {
        appState->setPhoneConnection(state);

        if (!state)
        {
            // Phone-driven features are meaningless once the link drops.
            appState->clearNavigation();
            appState->setCameraReady(false);
            appState->setSynchronized(false);
            appState->setIncomingCall("", false);
        }
    }

    Serial.printf("[CHRONOS] Connection: %s\n", state ? "CONNECTED" : "DISCONNECTED");
}

void ChronosManager::handleNotification(const Notification& n)
{
    Serial.printf("[CHRONOS] Notification: %s | %s | %s\n",
                  n.app.c_str(), n.title.c_str(), n.message.c_str());
    Serial.print("[CHRONOS] title bytes:");
    for (size_t i = 0; i < n.title.length() && i < 32; ++i) Serial.printf(" %02X", static_cast<uint8_t>(n.title[i]));
    Serial.print("\n[CHRONOS] message bytes:");
    for (size_t i = 0; i < n.message.length() && i < 48; ++i) Serial.printf(" %02X", static_cast<uint8_t>(n.message[i]));
    Serial.println();

    if (appState == nullptr)
    {
        return;
    }

    appState->setNotification(n.app, n.time, n.title, n.message);
    appState->addNotification(n.app, n.time, n.title, n.message, n.icon);
    appState->setNotificationCount(watch.getNotificationCount());
}

void ChronosManager::handleRinger(const String& caller, bool state)
{
    if (state)
    {
        Serial.printf("[CHRONOS] Incoming call: %s\n", caller.c_str());
    }
    else
    {
        Serial.println("[CHRONOS] Ringer dismissed");
    }

    if (appState != nullptr)
    {
        appState->setIncomingCall(caller, state);
    }
}

void ChronosManager::handleConfiguration(Config config, uint32_t a, uint32_t b)
{
    Serial.printf("[CHRONOS] Configuration: %d a=%lu b=%lu\n",
                  static_cast<int>(config),
                  static_cast<unsigned long>(a),
                  static_cast<unsigned long>(b));

    if (appState == nullptr)
    {
        return;
    }

    switch (config)
    {
        case CF_TIME:
            appState->setClockSynced(a == 1);
            break;

        case CF_HR24:
            appState->set24Hour(b != 0);
            break;

        case CF_PBAT:
            appState->setPhoneBattery(static_cast<uint8_t>(b));
            break;

        case CF_WEATHER:
            updateWeather();
            break;

        case CF_NAV_DATA:
        case CF_NAV_ICON:
            updateNavigation();
            break;

        case CF_CAMERA:
            appState->setCameraReady(b != 0);
            break;

        case CF_FIND:
            if (millis() - connectedAtMs > 4000)
            {
                appState->requestFindWatch();
            }
            else
            {
                Serial.println("[CHRONOS] Ignoring find request sent during connect sync");
            }
            break;

        case CF_ALARM:
            updateAlarms();
            break;

        case CF_QR:
            updateQr();
            break;

        case CF_QUIET:
        {
            const uint8_t sh = (b >> 24) & 0xFF;
            const uint8_t sm = (b >> 16) & 0xFF;
            const uint8_t eh = (b >> 8) & 0xFF;
            const uint8_t em = b & 0xFF;
            if (sh < 24 && sm < 60 && eh < 24 && em < 60)
            {
                appState->setQuietHours(a != 0, sh, sm, eh, em);
                Serial.printf("[CHRONOS] Quiet hours: %s %02u:%02u-%02u:%02u\n", a != 0 ? "ON" : "OFF",
                              static_cast<unsigned>(sh), static_cast<unsigned>(sm),
                              static_cast<unsigned>(eh), static_cast<unsigned>(em));
            }
            else
            {
                Serial.printf("[CHRONOS] Quiet hours value not understood: a=%lu b=0x%08lX\n",
                              static_cast<unsigned long>(a), static_cast<unsigned long>(b));
            }
            break;
        }

        case CF_APP:
            appState->setAppVersion(watch.getAppVersion());
            break;

        case CF_SYNCED:
            appState->setSynchronized(true);
            updateWeather();
            updateAlarms();
            updateQr();
            break;

        default:
            break;
    }
}

void ChronosManager::handleHealthRequest(HealthRequest request, bool state)
{
    switch (request)
    {
        case HR_STEPS_RECORDS:
            Serial.println("[CHRONOS] Health request: STEPS RECORDS");
            break;

        case HR_SLEEP_RECORDS:
            Serial.println("[CHRONOS] Health request: SLEEP RECORDS");
            break;

        case HR_HEART_RATE_MEASURE:
            activeHealthRequest = request;
            healthMeasurementRunning = state;
            Serial.printf("[CHRONOS] Heart-rate measurement: %s\n", state ? "START" : "STOP");
            break;

        case HR_BLOOD_OXYGEN_MEASURE:
            activeHealthRequest = request;
            healthMeasurementRunning = state;
            Serial.printf("[CHRONOS] Blood-oxygen measurement: %s\n", state ? "START" : "STOP");
            break;

        case HR_BLOOD_PRESSURE_MEASURE:
            activeHealthRequest = request;
            healthMeasurementRunning = state;
            Serial.printf("[CHRONOS] Blood-pressure measurement: %s\n", state ? "START" : "STOP");
            break;

        case HR_MEASURE_ALL:
            activeHealthRequest = request;
            healthMeasurementRunning = state;
            Serial.printf("[CHRONOS] All health measurements: %s\n", state ? "START" : "STOP");
            break;

        default:
            Serial.println("[CHRONOS] Unknown health request");
            break;
    }
}

bool ChronosManager::isBluetoothOn() const
{
    return bluetoothOn;
}

void ChronosManager::setBluetoothEnabled(bool enabled)
{
    if (enabled == bluetoothOn)
    {
        return;
    }

    bluetoothOn = enabled;

    if (enabled)
    {
        watch.begin();
        Serial.println("[CHRONOS] Bluetooth ON");
    }
    else
    {
        watch.stop();
        handleConnection(false);
        Serial.println("[CHRONOS] Bluetooth OFF");
    }
}

String ChronosManager::getAddress()
{
    return watch.getAddress();
}

int ChronosManager::getSosContactIndex()
{
    return watch.getSOSContactIndex();
}
