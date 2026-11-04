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
    void setBrightness(uint8_t percent);

    enum class ScreenState : uint8_t { Awake, Dimmed, Off };

    void wake();
    void setSleepEnabled(bool enabled);
    void setSleepTimeouts(uint32_t dimMs, uint32_t offMs);
    ScreenState getScreenState() const { return screenState; }
    uint8_t getBrightness() const { return userBrightness; }

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

    static void sleepTimerCb(lv_timer_t* timer);
    void applyBrightness(uint8_t percent);

    ScreenState screenState = ScreenState::Awake;
    uint8_t userBrightness = 100;
    uint32_t lastActivityMs = 0;
    uint32_t dimAfterMs = 15000;
    uint32_t offAfterMs = 30000;
    bool sleepEnabled = true;
    bool swallowTouch = false;
};
