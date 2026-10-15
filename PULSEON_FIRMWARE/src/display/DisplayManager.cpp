#include "DisplayManager.h"

#include <Arduino.h>
#include <esp_display_panel.hpp>
#include "draw/sw/lv_draw_sw_utils.h"

using namespace esp_panel::board;
using namespace esp_panel::drivers;

static constexpr int32_t DISPLAY_WIDTH = 320;
static constexpr int32_t DISPLAY_HEIGHT = 240;
static constexpr int32_t DISPLAY_DRAW_BUFFER_ROWS = 20;

DisplayManager* DisplayManager::instance = nullptr;

bool DisplayManager::begin()
{
    Serial.println();
    Serial.println("[DISPLAY] Initializing VIEWE UEDX24320028E-WB-A...");

    instance = this;

    board = new Board();

    if (board == nullptr)
    {
        Serial.println("[DISPLAY] ERROR: Failed to allocate Board");
        return false;
    }

    if (!board->init())
    {
        Serial.println("[DISPLAY] ERROR: Board init failed");
        return false;
    }

    Serial.println("[DISPLAY] Board init OK");

    if (!board->begin())
    {
        Serial.println("[DISPLAY] ERROR: Board begin failed");
        return false;
    }

    Serial.println("[DISPLAY] Board begin OK");

    lcd = board->getLCD();
    touch = board->getTouch();
    backlight = board->getBacklight();

    if (lcd == nullptr)
    {
        Serial.println("[DISPLAY] ERROR: LCD object unavailable");
        return false;
    }

    Serial.printf(
        "[DISPLAY] LCD: %dx%d\n",
        lcd->getFrameWidth(),
        lcd->getFrameHeight()
    );

    if (touch != nullptr)
    {
        Serial.println("[DISPLAY] Touch driver available");
    }
    else
    {
        Serial.println("[DISPLAY] Touch driver unavailable");
    }

    if (backlight != nullptr)
    {
        Serial.println("[DISPLAY] Backlight driver available");
        backlight->setBrightness(100);
    }

    /*
     * LVGL 9 display creation.
     *
     * We use a small draw buffer and send completed areas directly
     * through the official ESP32_Display_Panel LCD driver.
     */
    lv_init();

    // Use Arduino's millisecond clock for LVGL 9 timer scheduling.
    lv_tick_set_cb([]() -> uint32_t {
        return static_cast<uint32_t>(millis());
    });

    Serial.printf(
        "[DISPLAY] LVGL tick source registered; current tick: %lu ms\n",
        static_cast<unsigned long>(lv_tick_get())
    );

    static lv_color_t drawBuffer[DISPLAY_WIDTH * DISPLAY_DRAW_BUFFER_ROWS];

    display = lv_display_create(DISPLAY_WIDTH, DISPLAY_HEIGHT);

    if (display == nullptr)
    {
        Serial.println("[DISPLAY] ERROR: lv_display_create failed");
        return false;
    }

    lv_display_set_buffers(
        display,
        drawBuffer,
        nullptr,
        sizeof(drawBuffer),
        LV_DISPLAY_RENDER_MODE_PARTIAL
    );

    lv_display_set_flush_cb(display, flushCallback);

    /*
     * Touch input.
     */
    if (touch != nullptr)
    {
        inputDevice = lv_indev_create();

        if (inputDevice != nullptr)
        {
            lv_indev_set_type(inputDevice, LV_INDEV_TYPE_POINTER);
            lv_indev_set_read_cb(inputDevice, touchReadCallback);

            Serial.println("[DISPLAY] LVGL touch input registered");
        }
    }

    initialized = true;

    Serial.println("[DISPLAY] LVGL 9 display initialized");
    Serial.println("[DISPLAY] Hardware initialization complete");

    return true;
}

void DisplayManager::loop()
{
    /*
     * LVGL 9 handles its timers through lv_timer_handler().
     * This manager intentionally does not call it here because
     * main.cpp owns the LVGL event loop.
     */
}

lv_display_t* DisplayManager::getDisplay() const
{
    return display;
}

bool DisplayManager::isInitialized() const
{
    return initialized;
}

void DisplayManager::flushCallback(
    lv_display_t* display,
    const lv_area_t* area,
    uint8_t* px_map
)
{
    if (instance == nullptr ||
        instance->lcd == nullptr ||
        area == nullptr ||
        px_map == nullptr)
    {
        lv_display_flush_ready(display);
        return;
    }

    const int32_t width =
        area->x2 - area->x1 + 1;

    const int32_t height =
        area->y2 - area->y1 + 1;

    const uint32_t pixelCount =
        static_cast<uint32_t>(width * height);

    lv_draw_sw_rgb565_swap(
        px_map,
        pixelCount
    );

    static uint32_t flushCount = 0;
    const bool drawOk = instance->lcd->drawBitmap(
        area->x1,
        area->y1,
        width,
        height,
        px_map,
        -1
    );

    ++flushCount;
    if (flushCount <= 8) {
        Serial.printf(
            "[LVGL-FLUSH] #%lu area=(%ld,%ld)-(%ld,%ld) size=%ldx%ld drawBitmap=%s\n",
            static_cast<unsigned long>(flushCount),
            static_cast<long>(area->x1),
            static_cast<long>(area->y1),
            static_cast<long>(area->x2),
            static_cast<long>(area->y2),
            static_cast<long>(width),
            static_cast<long>(height),
            drawOk ? "OK" : "FAILED"
        );
    }

    lv_display_flush_ready(display);
}

void DisplayManager::touchReadCallback(
    lv_indev_t* indev,
    lv_indev_data_t* data
)
{
    if (instance == nullptr ||
        instance->touch == nullptr)
    {
        data->state = LV_INDEV_STATE_RELEASED;
        return;
    }

    instance->touch->readRawData(-1, -1, 30);

    std::vector<TouchPoint> points;
    instance->touch->getPoints(points);

    if (points.empty())
    {
        data->state = LV_INDEV_STATE_RELEASED;
        return;
    }

    const TouchPoint& point = points[0];

    data->state = LV_INDEV_STATE_PRESSED;
    data->point.x = point.x;
    data->point.y = point.y;

    (void)indev;
}
