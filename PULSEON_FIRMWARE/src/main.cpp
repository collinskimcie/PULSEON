#include <Arduino.h>
#include <esp_task_wdt.h>
#include <lvgl.h>

#include "app_config.h"
#include "app/AppState.h"
#include "display/DisplayManager.h"
#include "ui/UIManager.h"
#include "ui/UIText.h"
#include "ui/PulseonEmoji.h"

#if PULSEON_CHRONOS_ENABLED
#include "chronos/ChronosManager.h"
ChronosManager chronos;
#endif

AppStateManager appState;
DisplayManager displayManager;
UIManager uiManager;

RTC_DATA_ATTR static uint8_t displayFailures = 0;

// Shows a built-in notification with emoji at boot. Set to false when done testing.
constexpr bool kEmojiSelfTest = false;

static const char* resetReasonName(esp_reset_reason_t reason)
{
    switch (reason)
    {
        case ESP_RST_POWERON:  return "power-on";
        case ESP_RST_SW:       return "software restart";
        case ESP_RST_PANIC:    return "crash (panic)";
        case ESP_RST_INT_WDT:  return "interrupt watchdog";
        case ESP_RST_TASK_WDT: return "task watchdog";
        case ESP_RST_WDT:      return "other watchdog";
        case ESP_RST_BROWNOUT: return "brownout";
        default:               return "other";
    }
}


static void logLvglMemory(const char* tag)
{
    lv_mem_monitor_t m;
    lv_mem_monitor(&m);
    Serial.printf("[MEM] %s: LVGL pool %u%% used, free %u of %u, biggest block %u | heap free %u\n",
                  tag, static_cast<unsigned>(m.used_pct),
                  static_cast<unsigned>(m.free_size),
                  static_cast<unsigned>(m.total_size),
                  static_cast<unsigned>(m.free_biggest_size),
                  static_cast<unsigned>(ESP.getFreeHeap()));
    Serial.printf("[MEM] PSRAM total %u, free %u\n",
                  static_cast<unsigned>(ESP.getPsramSize()),
                  static_cast<unsigned>(ESP.getFreePsram()));
}

void setup()
{
    Serial.begin(115200);
    delay(1000);

    Serial.println();
    Serial.println("================================");
    Serial.println("       PULSEON WATCH");
    Serial.println("================================");
    Serial.printf("[PULSEON] LVGL version: %s\n", PULSEON_LVGL_VERSION);
    Serial.printf("[PULSEON] Last reset: %s\n", resetReasonName(esp_reset_reason()));
    Serial.println("[PULSEON] Initializing display...");

    // LVGL must be initialized before the generated screens.
    if (!displayManager.begin())
    {
        Serial.println("[PULSEON] ERROR: Display initialization failed.");
        Serial.println("[PULSEON] Check the board configuration and display logs.");

        if (++displayFailures <= 3)
        {
            Serial.printf("[PULSEON] Restarting to retry display init (%u/3)...\n",
                          static_cast<unsigned>(displayFailures));
            delay(3000);
            ESP.restart();
        }

        Serial.println("[PULSEON] Giving up after 3 restarts. Power-cycle the watch.");
        while (true)
        {
            delay(1000);
        }
    }

    Serial.println("[PULSEON] Display initialized.");
    displayFailures = 0;

    appState.begin();

#if PULSEON_CHRONOS_ENABLED
    chronos.attachAppState(&appState);
    chronos.begin();
    uiManager.attachChronos(&chronos);
    Serial.println("[PULSEON] Chronos initialized.");
#endif

    pulseonEmojiInit();
    uiManager.setBrightnessHandler([](uint8_t percent) { displayManager.setBrightness(percent); });
    uiManager.begin(&appState);
    Serial.println("[PULSEON] UI initialized.");
    uiTextWarmup();
    logLvglMemory("after UI init");

    Serial.println("[PULSEON] Forcing initial LVGL refresh...");
    lv_refr_now(displayManager.getDisplay());
    Serial.println("[PULSEON] Initial LVGL refresh returned.");

    Serial.println("[PULSEON] Startup complete.");

    if (kEmojiSelfTest)
    {
        appState.addNotification("Test", "now", "Emoji test",
            "Hi \xF0\x9F\x98\xA9 \xF0\x9F\x91\x8D \xE2\x9D\xA4 \xF0\x9F\x94\xA5 (Wave)");
    }

    const esp_err_t wdtResult = esp_task_wdt_add(nullptr);
    Serial.printf("[PULSEON] Watchdog: %s\n", esp_err_to_name(wdtResult));
}

void loop()
{
    esp_task_wdt_reset();

#if PULSEON_CHRONOS_ENABLED
    chronos.loop();
#endif

    uiManager.update();

    static uint32_t lastMemLogMs = 0;
    if (millis() - lastMemLogMs >= 5000)
    {
        lastMemLogMs = millis();
        logLvglMemory("running");
    }
    displayManager.loop();
    lv_timer_handler();

    delay(5);
}
