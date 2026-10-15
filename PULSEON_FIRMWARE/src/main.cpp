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
    Serial.println("[PULSEON] Chronos initialized.");
#endif

    uiManager.begin(&appState);
    Serial.println("[PULSEON] UI initialized.");

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
    displayManager.loop();
    lv_timer_handler();

    delay(5);
}
