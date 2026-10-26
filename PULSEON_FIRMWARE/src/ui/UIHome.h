#pragma once

// Three extra home faces for PULSEON, built into panels owned by UIManager.
//   ORBIT  - rings for seconds, phone battery and alerts around a big clock
//   TODAY  - time header plus four colored cards
//   STACK  - hour and minute stacked in two accent colors, with status chips
// Each face is a plain panel: no gestures or scrolling, so the screen swipes still work.

#include <lvgl.h>
#include <stdint.h>

enum HomeFaceKind : uint8_t
{
    HOME_FACE_ORBIT = 0,
    HOME_FACE_TODAY = 1,
    HOME_FACE_STACK = 2,
    HOME_FACE_KINDS = 3
};

struct HomeColors
{
    lv_color_t bg;
    lv_color_t card;
    lv_color_t text;
    lv_color_t dim;
    lv_color_t a1;
    lv_color_t a2;
    lv_color_t a3;
    lv_color_t a4;
};

struct HomeData
{
    uint8_t hour = 0;
    uint8_t minute = 0;
    uint8_t second = 0;
    uint8_t weekday = 0;     // 0 = Sunday
    uint8_t day = 1;
    uint8_t month = 1;
    int8_t battery = -1;     // phone battery 0..100, -1 = unknown
    bool hasTemp = false;
    int8_t tempC = 0;
    char weather[16] = "";
    char nextAlarm[8] = "--:--";
    uint8_t notifCount = 0;
};

// Fills `panel` with one face. Call once per face after the panel exists.
void uiHomeBuildFace(lv_obj_t* panel, uint8_t kind, const HomeColors& colors);

// Call about once per second. Updates every face that has been built.
void uiHomeUpdate(const HomeData& data);

// Call after a theme change. Rebuilds the built faces with the new colors.
void uiHomeRecolor(const HomeColors& colors);
