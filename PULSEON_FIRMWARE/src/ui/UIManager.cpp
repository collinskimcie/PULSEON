#include "UIManager.h"

#include <time.h>

#include "PULSEON_WATCH_UI.h"

static lv_obj_t* getChild(lv_obj_t* parent, uint32_t index)
{
    if (parent == nullptr)
    {
        return nullptr;
    }

    return lv_obj_get_child(parent, index);
}

void UIManager::begin(AppStateManager* state)
{
    appState = state;

    Serial.println("[UI] Initializing UI manager...");

    PULSEON_WATCH_UI_init(nullptr);

    createScreens();

    showScreen(SCREEN_WATCH_HOME);

    Serial.println("[UI] UI manager initialized");
}

void UIManager::createScreens()
{
    createWatchHome();
    createNotifications();

    quickControls = QuickControls_create();

    if (quickControls == nullptr)
    {
        Serial.println(
            "[UI] ERROR: QuickControls_create() returned NULL"
        );
    }

    health = Health_create();

    if (health == nullptr)
    {
        Serial.println(
            "[UI] ERROR: Health_create() returned NULL"
        );
    }

    createWeather();

    music = Music_create();

    if (music == nullptr)
    {
        Serial.println(
            "[UI] ERROR: Music_create() returned NULL"
        );
    }

    settings = Settings_create();

    if (settings == nullptr)
    {
        Serial.println(
            "[UI] ERROR: Settings_create() returned NULL"
        );
    }

    lv_obj_t* screens[] =
    {
        watchHome,
        notifications,
        quickControls,
        health,
        weather,
        music,
        settings
    };

    for (lv_obj_t* screen : screens)
    {
        if (screen != nullptr)
        {
            lv_obj_add_event_cb(
                screen,
                screenGestureCallback,
                LV_EVENT_GESTURE,
                this
            );
        }
    }

    Serial.println("[UI] All generated screens created");
}

void UIManager::createWatchHome()
{
    watchHome = WatchHome_create();

    if (watchHome == nullptr)
    {
        Serial.println(
            "[UI] ERROR: WatchHome_create() returned NULL"
        );
        return;
    }

    dateLabel = getChild(watchHome, 0);
    bluetoothLabel = getChild(watchHome, 1);
    batteryLabel = getChild(watchHome, 2);
    timeLabel = getChild(watchHome, 3);
    periodLabel = getChild(watchHome, 4);

    lv_obj_t* heartRateCard =
        getChild(watchHome, 5);

    lv_obj_t* weatherCard =
        getChild(watchHome, 6);

    heartRateLabel =
        getChild(heartRateCard, 1);

    weatherLabel =
        getChild(weatherCard, 1);

    stepsLabel =
        getChild(watchHome, 8);

    activityLabel =
        getChild(watchHome, 10);
}

void UIManager::createNotifications()
{
    notifications = Notifications_create();

    if (notifications == nullptr)
    {
        Serial.println(
            "[UI] ERROR: Notifications_create() returned NULL"
        );
        return;
    }

    notificationTitleLabel =
        getChild(notifications, 0);

    lv_obj_t* messagesCard =
        getChild(notifications, 1);

    notificationAppLabel =
        getChild(messagesCard, 0);

    notificationMessageLabel =
        getChild(messagesCard, 1);

    lv_obj_t* phoneCard =
        getChild(notifications, 2);

    notificationPhoneLabel =
        getChild(phoneCard, 0);

    notificationPhoneStatusLabel =
        getChild(phoneCard, 1);

    notificationRefreshLabel =
        getChild(notifications, 3);
}

void UIManager::createWeather()
{
    weather = Weather_create();

    if (weather == nullptr)
    {
        Serial.println(
            "[UI] ERROR: Weather_create() returned NULL"
        );
        return;
    }

    weatherTemperatureLabel =
        getChild(weather, 1);

    weatherConditionLabel =
        getChild(weather, 2);

    lv_obj_t* weatherInfoPanel =
        getChild(weather, 3);

    weatherLowLabel =
        getChild(weatherInfoPanel, 0);

    weatherHighLabel =
        getChild(weatherInfoPanel, 1);

    weatherCityLabel =
        getChild(weatherInfoPanel, 2);
}

void UIManager::showScreen(Screen screen)
{
    if (screen >= SCREEN_COUNT)
    {
        return;
    }

    lv_obj_t* target = nullptr;

    switch (screen)
    {
        case SCREEN_WATCH_HOME:
            target = watchHome;
            break;

        case SCREEN_NOTIFICATIONS:
            target = notifications;
            break;

        case SCREEN_QUICK_CONTROLS:
            target = quickControls;
            break;

        case SCREEN_HEALTH:
            target = health;
            break;

        case SCREEN_WEATHER:
            target = weather;
            break;

        case SCREEN_MUSIC:
            target = music;
            break;

        case SCREEN_SETTINGS:
            target = settings;
            break;

        default:
            return;
    }

    if (target == nullptr)
    {
        Serial.print(
            "[UI] ERROR: Screen unavailable: "
        );

        Serial.println(
            static_cast<int>(screen)
        );

        return;
    }

    currentScreen = screen;

    if (appState != nullptr)
    {
        appState->setActiveScreen(
            static_cast<uint8_t>(screen)
        );
    }

    lv_screen_load(target);

    Serial.print("[UI] Screen changed to: ");

    switch (screen)
    {
        case SCREEN_WATCH_HOME:
            Serial.println("WATCH HOME");
            break;

        case SCREEN_NOTIFICATIONS:
            Serial.println("NOTIFICATIONS");
            break;

        case SCREEN_QUICK_CONTROLS:
            Serial.println("QUICK CONTROLS");
            break;

        case SCREEN_HEALTH:
            Serial.println("HEALTH");
            break;

        case SCREEN_WEATHER:
            Serial.println("WEATHER");
            break;

        case SCREEN_MUSIC:
            Serial.println("MUSIC");
            break;

        case SCREEN_SETTINGS:
            Serial.println("SETTINGS");
            break;

        default:
            Serial.println("UNKNOWN");
            break;
    }
}

void UIManager::screenGestureCallback(lv_event_t* event)
{
    UIManager* ui = static_cast<UIManager*>(lv_event_get_user_data(event));
    lv_indev_t* input = lv_event_get_indev(event);

    if (ui == nullptr || input == nullptr)
    {
        return;
    }

    const lv_dir_t direction = lv_indev_get_gesture_dir(input);

    if (direction == LV_DIR_RIGHT)
    {
        const uint8_t next =
            (static_cast<uint8_t>(ui->currentScreen) + 1) % SCREEN_COUNT;
        ui->showScreen(static_cast<Screen>(next));
    }
    else if (direction == LV_DIR_LEFT)
    {
        const uint8_t previous =
            (static_cast<uint8_t>(ui->currentScreen) + SCREEN_COUNT - 1) %
            SCREEN_COUNT;
        ui->showScreen(static_cast<Screen>(previous));
    }
}

UIManager::Screen UIManager::getCurrentScreen() const
{
    return currentScreen;
}

void UIManager::update()
{
    if (appState == nullptr)
    {
        return;
    }

    updateWatchHome();
    updateNotifications();
    updateWeather();

    updateActiveScreen();
}

void UIManager::updateActiveScreen()
{
    /*
     * Keep the currently displayed screen synchronized
     * with AppState.
     *
     * Navigation input will later call showScreen().
     */
}

void UIManager::updateWatchHome()
{
    if (watchHome == nullptr)
    {
        return;
    }

    const PulseonAppState& state =
        appState->getState();

    time_t now = time(nullptr);
    struct tm timeInfo;

    if (localtime_r(&now, &timeInfo) != nullptr)
    {
        char timeBuffer[8];
        char periodBuffer[4];

        if (state.is24Hour)
        {
            snprintf(
                timeBuffer,
                sizeof(timeBuffer),
                "%02d:%02d",
                timeInfo.tm_hour,
                timeInfo.tm_min
            );

            periodBuffer[0] = '\0';
            periodBuffer[1] = '\0';
        }
        else
        {
            int hour = timeInfo.tm_hour % 12;

            if (hour == 0)
            {
                hour = 12;
            }

            snprintf(
                timeBuffer,
                sizeof(timeBuffer),
                "%02d:%02d",
                hour,
                timeInfo.tm_min
            );

            snprintf(
                periodBuffer,
                sizeof(periodBuffer),
                "%s",
                timeInfo.tm_hour >= 12
                    ? "PM"
                    : "AM"
            );
        }

        static const char* weekdays[] =
        {
            "SUN",
            "MON",
            "TUE",
            "WED",
            "THU",
            "FRI",
            "SAT"
        };

        lv_label_set_text(
            timeLabel,
            timeBuffer
        );

        lv_label_set_text(
            periodLabel,
            periodBuffer
        );

        lv_label_set_text_fmt(
            dateLabel,
            "%s %02d",
            weekdays[timeInfo.tm_wday],
            timeInfo.tm_mday
        );
    }

    lv_label_set_text(
        bluetoothLabel,
        state.phoneConnected
            ? "BT"
            : "--"
    );

    lv_label_set_text_fmt(
        batteryLabel,
        "%u%%",
        state.phoneBattery
    );

    if (state.heartRate > 0)
    {
        lv_label_set_text_fmt(
            heartRateLabel,
            "%u BPM",
            state.heartRate
        );
    }
    else
    {
        lv_label_set_text(
            heartRateLabel,
            "-- BPM"
        );
    }

    if (state.weatherCity.length() > 0)
    {
        lv_label_set_text(
            weatherLabel,
            state.weatherCity.c_str()
        );
    }
    else
    {
        lv_label_set_text(
            weatherLabel,
            "--"
        );
    }

    lv_label_set_text_fmt(
        stepsLabel,
        "%u",
        state.steps
    );

    uint8_t activity = 0;

    if (state.steps >= 10000)
    {
        activity = 100;
    }
    else
    {
        activity = static_cast<uint8_t>(
            (
                static_cast<uint32_t>(state.steps) * 100
            ) / 10000
        );
    }

    lv_label_set_text_fmt(
        activityLabel,
        "%u%%",
        activity
    );
}

void UIManager::updateNotifications()
{
    if (notifications == nullptr)
    {
        return;
    }

    const PulseonAppState& state =
        appState->getState();

    lv_label_set_text(
        notificationTitleLabel,
        "NOTIFICATIONS"
    );

    if (state.notificationCount > 0)
    {
        if (state.notificationApp.length() > 0)
        {
            lv_label_set_text(
                notificationAppLabel,
                state.notificationApp.c_str()
            );
        }
        else
        {
            lv_label_set_text(
                notificationAppLabel,
                "Messages"
            );
        }

        if (state.notificationMessage.length() > 0)
        {
            lv_label_set_text(
                notificationMessageLabel,
                state.notificationMessage.c_str()
            );
        }
        else if (state.notificationTitle.length() > 0)
        {
            lv_label_set_text(
                notificationMessageLabel,
                state.notificationTitle.c_str()
            );
        }
        else
        {
            lv_label_set_text(
                notificationMessageLabel,
                "New notification"
            );
        }
    }
    else
    {
        lv_label_set_text(
            notificationAppLabel,
            "Messages"
        );

        lv_label_set_text(
            notificationMessageLabel,
            "No new messages"
        );
    }

    lv_label_set_text(
        notificationPhoneLabel,
        "Phone"
    );

    lv_label_set_text(
        notificationPhoneStatusLabel,
        state.phoneConnected
            ? "Connected"
            : "Disconnected"
    );

    lv_label_set_text(
        notificationRefreshLabel,
        "Swipe down to refresh"
    );
}

void UIManager::updateWeather()
{
    if (weather == nullptr)
    {
        return;
    }

    const PulseonAppState& state =
        appState->getState();

    if (!state.weatherAvailable)
    {
        lv_label_set_text(
            weatherTemperatureLabel,
            "-- C"
        );

        lv_label_set_text(
            weatherConditionLabel,
            "NO WEATHER DATA"
        );

        lv_label_set_text(
            weatherLowLabel,
            "LOW  -- C"
        );

        lv_label_set_text(
            weatherHighLabel,
            "HIGH  -- C"
        );

        lv_label_set_text(
            weatherCityLabel,
            "--"
        );

        return;
    }

    lv_label_set_text_fmt(
        weatherTemperatureLabel,
        "%d C",
        state.weatherTemperature
    );

    lv_label_set_text(
        weatherConditionLabel,
        "CURRENT WEATHER"
    );

    lv_label_set_text_fmt(
        weatherLowLabel,
        "LOW  %d C",
        state.weatherLow
    );

    lv_label_set_text_fmt(
        weatherHighLabel,
        "HIGH  %d C",
        state.weatherHigh
    );

    if (state.weatherCity.length() > 0)
    {
        lv_label_set_text(
            weatherCityLabel,
            state.weatherCity.c_str()
        );
    }
    else
    {
        lv_label_set_text(
            weatherCityLabel,
            "--"
        );
    }
}
