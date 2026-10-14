#include "DisplayManager.h"

#include <Arduino.h>
#include <esp_display_panel.hpp>

using namespace esp_panel::board;
using namespace esp_panel::drivers;

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

    static lv_color_t drawBuffer[320 * 20];

    display = lv_display_create(320, 240);

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

    instance->lcd->drawBitmap(
        area->x1,
        area->y1,
        width,
        height,
        px_map
    );

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
