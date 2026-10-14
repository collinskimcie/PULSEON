#pragma once

#include <Arduino.h>
#include <lvgl.h>
#include <esp_display_panel.hpp>

class DisplayManager
{
public:
    bool begin();
    void loop();

    lv_display_t* getDisplay() const;
    bool isInitialized() const;

private:
    static void flushCallback(
        lv_display_t* display,
        const lv_area_t* area,
        uint8_t* px_map
    );

    static void touchReadCallback(
        lv_indev_t* indev,
        lv_indev_data_t* data
    );

    static DisplayManager* instance;

    esp_panel::board::Board* board = nullptr;
    esp_panel::drivers::LCD* lcd = nullptr;
    esp_panel::drivers::Touch* touch = nullptr;
    esp_panel::drivers::Backlight* backlight = nullptr;

    lv_display_t* display = nullptr;
    lv_indev_t* inputDevice = nullptr;

    bool initialized = false;
};
