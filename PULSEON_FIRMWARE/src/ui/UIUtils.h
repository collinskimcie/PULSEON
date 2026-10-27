#pragma once

#include <lvgl.h>

// Tile handlers for UIApps::addTile
void uiStopwatchOpen(void* user);
void uiTimerOpen(void* user);
void uiFlashlightOpen(void* user);

// Call from the main UI loop (keeps the stopwatch, timer and alert running)
void uiUtilsPoll();
