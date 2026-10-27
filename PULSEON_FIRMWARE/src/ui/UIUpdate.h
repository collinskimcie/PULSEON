#pragma once

#include <Arduino.h>
#include <lvgl.h>

class UIApps;

// Wi-Fi firmware update page (Apps > Update).
void uiUpdateBegin(UIApps* apps);
void uiUpdateOpen(void* user);
void uiUpdatePoll();
