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
    HOME_FACE_KINDS = 3,  // the three extra faces
    HOME_FACE_BRUTALIST = 3,
    HOME_FACE_DOT = 4,
    HOME_FACE_TOPO = 5,
    HOME_FACE_GLASS = 6,
    HOME_FACE_CIRCUIT = 7,
    HOME_FACE_PRISM = 8,
    HOME_FACE_TOTAL = 9
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
    bool timeValid = false;  // false until the phone has synced the clock
    uint16_t heartRate = 0;  // 0 = no reading
    uint16_t steps = 0;
    uint8_t oxygen = 0;      // SpO2 percent, 0 = no reading
    bool connected = false;  // phone link
    bool charging = false;
    uint16_t stepGoal = 10000;
};

// Fills `panel` with one face. Call once per face after the panel exists.
void uiHomeBuildFace(lv_obj_t* panel, uint8_t kind, const HomeColors& colors);

// Call about once per second. Updates every face that has been built.
void uiHomeUpdate(const HomeData& data);

// Call after a theme change. Rebuilds the built faces with the new colors.
void uiHomeRecolor(const HomeColors& colors);

// Internal: the six classic faces live in UIHomeFaces.cpp.
void uiHomeExtBuild(lv_obj_t* panel, uint8_t kind, const HomeColors& colors);
void uiHomeExtUpdate(const HomeData& data);
void uiHomeExtRecolor(const HomeColors& colors);
