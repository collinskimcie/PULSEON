#pragma once

// Extra home faces: ANALOG, EMBER (animated eyes), WAYFINDER (red dashboard).
// Same contract as UIHome: build into a panel, update about once per second, recolor on theme change.

#include "UIHome.h"

enum NewFaceKind : uint8_t
{
    NEW_FACE_ANALOG = 0,
    NEW_FACE_EMBER = 1,
    NEW_FACE_WAYFINDER = 2,
    NEW_FACE_STACK = 3,
    NEW_FACE_GLANCE = 4,
    NEW_FACE_NOW = 5,
    NEW_FACE_COUNT = 6
};

void uiNewBuildFace(lv_obj_t* panel, uint8_t kind, const HomeColors& colors);
void uiNewUpdate(const HomeData& data);
void uiNewRecolor(const HomeColors& colors);

// Music buttons on the Now face: action 0 = previous, 1 = play/pause, 2 = next.
typedef void (*NewMusicHandler)(uint8_t action);
void uiNewSetMusicHandler(NewMusicHandler handler);
