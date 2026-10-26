#include "AppState.h"

// ---------------- Display text cleanup ----------------

// The UI fonts only cover plain ASCII. Drop emoji, accents and invisible
// Unicode marks so they do not render as empty boxes.
static String displaySafe(const String& in)
{
    String out;
    out.reserve(in.length());
    for (size_t i = 0; i < in.length(); ++i)
    {
        const uint8_t c = static_cast<uint8_t>(in[i]);
        if (c == '\n' || c == '\r' || c == '\t')
        {
            out += ' ';
        }
        else if (c >= 0x20 && c != 0x7F)
        {
            out += static_cast<char>(c);
        }
    }
    out.trim();
    return out;
}

// ---------------- Notifications ----------------

void AppStateManager::addNotification(
    const String& app,
    const String& time,
    const String& title,
    const String& message,
    int icon
)
{
    state.notificationHead =
        (state.notificationHead + 1) % PULSEON_MAX_NOTIFICATIONS;

    PulseonNotification& n = state.notifications[state.notificationHead];
    const String cleanMessage = displaySafe(message);
    n.icon = icon;
    n.app = displaySafe(app);
    n.time = displaySafe(time);
    n.title = displaySafe(title);
    n.message = cleanMessage.length() > 240 ? cleanMessage.substring(0, 240) : cleanMessage;

    if (state.notificationStored < PULSEON_MAX_NOTIFICATIONS)
    {
        ++state.notificationStored;
    }
}

void AppStateManager::clearNotifications()
{
    for (uint8_t i = 0; i < PULSEON_MAX_NOTIFICATIONS; ++i)
    {
        state.notifications[i] = PulseonNotification();
    }
    state.notificationStored = 0;
    state.notificationHead = 0;
    state.notificationCount = 0;
}

const PulseonNotification* AppStateManager::getNotification(uint8_t index) const
{
    if (index >= state.notificationStored)
    {
        return nullptr;
    }

    const uint8_t i =
        (state.notificationHead + PULSEON_MAX_NOTIFICATIONS - index) %
        PULSEON_MAX_NOTIFICATIONS;

    return &state.notifications[i];
}

// ---------------- Calls ----------------

void AppStateManager::setIncomingCall(const String& caller, bool active)
{
    state.callActive = active;
    state.callerName = active ? displaySafe(caller) : String("");
}

// ---------------- Weather ----------------

void AppStateManager::setWeatherForecast(
    const String& city,
    const String& updated,
    const PulseonForecastDay* days,
    uint8_t count
)
{
    if (days == nullptr || count == 0)
    {
        return;
    }

    if (count > PULSEON_MAX_FORECAST_DAYS)
    {
        count = PULSEON_MAX_FORECAST_DAYS;
    }

    // Skip identical updates so repeated sync events cause no String churn.
    bool same = state.weatherAvailable &&
                state.weatherDayCount == count &&
                state.weatherCity == city &&
                state.weatherTime == updated;

    for (uint8_t i = 0; same && i < count; ++i)
    {
        const PulseonForecastDay& a = state.weatherDays[i];
        const PulseonForecastDay& b = days[i];
        same = a.icon == b.icon && a.day == b.day && a.temp == b.temp &&
               a.high == b.high && a.low == b.low;
    }

    if (same)
    {
        return;
    }

    for (uint8_t i = 0; i < count; ++i)
    {
        state.weatherDays[i] = days[i];
    }

    state.weatherDayCount = count;
    state.weatherCity = city;
    state.weatherTime = updated;
    state.weatherTemperature = days[0].temp;
    state.weatherHigh = days[0].high;
    state.weatherLow = days[0].low;
    state.weatherIcon = days[0].icon;
    state.weatherAvailable = true;
}

// ---------------- Navigation ----------------

void AppStateManager::setNavigationData(const PulseonNavigation& nav)
{
    state.navigation = nav;
    state.navigationActive = nav.active;
}

void AppStateManager::clearNavigation()
{
    state.navigation = PulseonNavigation();
    state.navigationActive = false;
}

// ---------------- Alarms ----------------

void AppStateManager::setAlarms(const PulseonAlarm* alarms, uint8_t count)
{
    if (alarms == nullptr)
    {
        return;
    }

    if (count > PULSEON_MAX_ALARMS)
    {
        count = PULSEON_MAX_ALARMS;
    }

    for (uint8_t i = 0; i < count; ++i)
    {
        state.alarms[i] = alarms[i];
    }
}

void AppStateManager::setAlarmRinging(int8_t index)
{
    state.alarmRinging =
        (index >= 0 && index < static_cast<int8_t>(PULSEON_MAX_ALARMS)) ? index : -1;
}

// ---------------- Misc Chronos data ----------------

void AppStateManager::setQr(uint8_t index, const String& value)
{
    if (index < PULSEON_MAX_QR && !(state.qrCodes[index] == value))
    {
        state.qrCodes[index] = value;
    }
}

void AppStateManager::requestFindWatch()
{
    ++state.findWatchEventId;
}

void AppStateManager::setAppVersion(const String& version)
{
    state.appVersion = version;
}
