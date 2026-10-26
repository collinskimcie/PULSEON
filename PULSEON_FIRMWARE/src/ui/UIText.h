#pragma once

#include <Arduino.h>
#include <lvgl.h>

// Phone text for the display: printable ASCII plus the emoji we ship images for.
String uiText(const String& in);

// A font that draws those emoji inline and falls back to `base` for everything else.
const lv_font_t* uiEmojiFont(const lv_font_t* base);

// Creates the emoji fonts up front and logs the font line heights.
void uiTextWarmup();
