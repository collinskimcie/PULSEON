#pragma once

#include <lvgl.h>

// Tile handlers for UIApps::addTile
void uiStopwatchOpen(void* user);
void uiTimerOpen(void* user);
void uiFlashlightOpen(void* user);

// Call from the main UI loop (keeps the stopwatch, timer and alert running)
void uiUtilsPoll();

// True while the stopwatch, timer or flashlight screen is open
bool uiUtilsKeepAwake();

// Slides a freshly shown panel up into place (no extra memory, ends at y = 0)
void uiSlideIn(lv_obj_t* obj);
