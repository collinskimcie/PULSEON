#include <Arduino.h>
#include <lvgl.h>

#include "app_config.h"
#include "app/AppState.h"
#include "display/DisplayManager.h"
#include "ui/UIManager.h"

#if PULSEON_CHRONOS_ENABLED
#include "chronos/ChronosManager.h"
ChronosManager chronos;
#endif

AppStateManager appState;
DisplayManager displayManager;
UIManager uiManager;


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
    Serial.println("[PULSEON] Initializing display...");

    // LVGL must be initialized before the generated screens.
    if (!displayManager.begin())
    {
        Serial.println("[PULSEON] ERROR: Display initialization failed.");
        Serial.println("[PULSEON] Check the board configuration and display logs.");

        while (true)
        {
            delay(1000);
        }
    }

    Serial.println("[PULSEON] Display initialized.");

    appState.begin();

#if PULSEON_CHRONOS_ENABLED
    chronos.attachAppState(&appState);
    chronos.begin();
    uiManager.attachChronos(&chronos);
    Serial.println("[PULSEON] Chronos initialized.");
#endif

    uiManager.setBrightnessHandler([](uint8_t percent) { displayManager.setBrightness(percent); });
    uiManager.begin(&appState);
    Serial.println("[PULSEON] UI initialized.");
    logLvglMemory("after UI init");

    Serial.println("[PULSEON] Forcing initial LVGL refresh...");
    lv_refr_now(displayManager.getDisplay());
    Serial.println("[PULSEON] Initial LVGL refresh returned.");

    Serial.println("[PULSEON] Startup complete.");
}

void loop()
{
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
