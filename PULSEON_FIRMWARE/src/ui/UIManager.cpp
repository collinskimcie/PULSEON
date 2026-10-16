#include "UIManager.h"

#include <math.h>
#include <stdint.h>
#include <time.h>
#include <Preferences.h>

#include "PULSEON_WATCH_UI.h"

namespace
{
constexpr int32_t DISPLAY_WIDTH = 240;
constexpr int32_t DISPLAY_HEIGHT = 320;
constexpr int32_t MARGIN = 16;
constexpr int32_t CONTENT_WIDTH = DISPLAY_WIDTH - (MARGIN * 2);

const lv_color_t UI_COLOR_BACKGROUND = lv_color_hex(0x090A0E);
const lv_color_t UI_COLOR_CARD = lv_color_hex(0x15161C);
const lv_color_t UI_COLOR_CARD_ALT = lv_color_hex(0x25262D);
const lv_color_t UI_COLOR_TEXT = lv_color_hex(0xF7F7FA);
const lv_color_t UI_COLOR_MUTED = lv_color_hex(0xA8A3AB);
const lv_color_t UI_COLOR_ACCENT = lv_color_hex(0xFF5D6C);
const lv_color_t UI_COLOR_ACCENT_DARK = lv_color_hex(0x54252D);
const lv_color_t UI_COLOR_GOOD = lv_color_hex(0x75D6B1);
lv_point_precise_t analogHourPoints[2];
lv_point_precise_t analogMinutePoints[2];
lv_point_precise_t analogSecondPoints[2];

lv_obj_t* createLabel(
    lv_obj_t* parent,
    const char* text,
    int32_t x,
    int32_t y,
    int32_t width,
    int32_t height,
    const lv_font_t* font,
    lv_color_t color,
    lv_text_align_t align = LV_TEXT_ALIGN_LEFT
)
{
    lv_obj_t* label = lv_label_create(parent);
    lv_label_set_text(label, text);
    lv_obj_set_pos(label, x, y);
    lv_obj_set_size(label, width, height);
    lv_obj_set_style_text_font(label, font, 0);
    lv_obj_set_style_text_color(label, color, 0);
    lv_obj_set_style_text_align(label, align, 0);
    lv_label_set_long_mode(label, LV_LABEL_LONG_DOT);
    lv_obj_add_flag(label, LV_OBJ_FLAG_EVENT_BUBBLE);
    return label;
}

lv_obj_t* createCard(
    lv_obj_t* parent,
    int32_t x,
    int32_t y,
    int32_t width,
    int32_t height,
    lv_color_t color = UI_COLOR_CARD,
    int32_t radius = 16
)
{
    lv_obj_t* card = lv_obj_create(parent);
    lv_obj_set_pos(card, x, y);
    lv_obj_set_size(card, width, height);
    lv_obj_set_style_bg_color(card, color, 0);
    lv_obj_set_style_bg_opa(card, LV_OPA_COVER, 0);
    lv_obj_set_style_border_width(card, 0, 0);
    lv_obj_set_style_radius(card, radius, 0);
    lv_obj_set_style_pad_all(card, 0, 0);
    lv_obj_clear_flag(card, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_flag(card, LV_OBJ_FLAG_EVENT_BUBBLE);
    return card;
}

lv_obj_t* createFacePanel(lv_obj_t* parent)
{
    lv_obj_t* panel = lv_obj_create(parent);
    lv_obj_set_size(panel, DISPLAY_WIDTH, DISPLAY_HEIGHT);
    lv_obj_set_style_bg_opa(panel, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_width(panel, 0, 0);
    lv_obj_set_style_radius(panel, 0, 0);
    lv_obj_set_style_pad_all(panel, 0, 0);
    lv_obj_clear_flag(panel, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_flag(panel, LV_OBJ_FLAG_EVENT_BUBBLE);
    return panel;
}

lv_obj_t* createFaceLine(lv_obj_t* parent, const lv_point_precise_t* points, uint16_t count, lv_color_t color, int32_t width)
{
    lv_obj_t* line = lv_line_create(parent);
    lv_line_set_points(line, points, count);
    lv_obj_set_style_line_color(line, color, 0);
    lv_obj_set_style_line_width(line, width, 0);
    lv_obj_set_style_line_rounded(line, true, 0);
    return line;
}

void createBadge(lv_obj_t* parent, const char* text, int32_t y)
{
    lv_obj_t* badge = createCard(parent, 78, y, 84, 25, UI_COLOR_ACCENT_DARK, 12);
    createLabel(badge, text, 4, 2, 76, 21, font_h5, UI_COLOR_ACCENT, LV_TEXT_ALIGN_CENTER);
}

void styleButton(lv_obj_t* button, bool selected)
{
    lv_obj_set_style_bg_color(button, selected ? UI_COLOR_ACCENT_DARK : UI_COLOR_CARD, 0);
    lv_obj_set_style_bg_opa(button, LV_OPA_COVER, 0);
    lv_obj_set_style_border_color(button, selected ? UI_COLOR_ACCENT : UI_COLOR_CARD, 0);
    lv_obj_set_style_border_width(button, selected ? 1 : 0, 0);
    lv_obj_set_style_radius(button, 14, 0);
    lv_obj_set_style_pad_all(button, 0, 0);
    lv_obj_clear_flag(button, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_flag(button, LV_OBJ_FLAG_EVENT_BUBBLE);
}

void styleButtonLabel(lv_obj_t* label)
{
    lv_obj_add_flag(label, LV_OBJ_FLAG_EVENT_BUBBLE);
}

void logLvglMemory(const char* stage)
{
    lv_mem_monitor_t memory = {};
    lv_mem_monitor(&memory);
    Serial.printf(
        "[UI][LVGL-HEAP] %s: free=%u largest=%u used=%u%%\n",
        stage,
        static_cast<unsigned>(memory.free_size),
        static_cast<unsigned>(memory.free_biggest_size),
        static_cast<unsigned>(memory.used_pct)
    );
}
}

void UIManager::begin(AppStateManager* state)
{
    appState = state;

    Preferences preferences;
    if (preferences.begin("pulseon", true))
    {
        selectedHomeFace = preferences.getUChar("homeFace", 0);
        preferences.end();
    }
    else
    {
        Serial.println("[UI] WARNING: Could not load saved home face; using face 1");
        selectedHomeFace = 0;
    }
    if (selectedHomeFace >= 6)
    {
        selectedHomeFace = 0;
    }

    Serial.println("[UI] Initializing six-screen health interface...");
    Serial.println("[UI] Initializing generated assets...");
    PULSEON_WATCH_UI_init(nullptr);
    Serial.println("[UI] Generated assets initialized.");
    createScreens();
    Serial.println("[UI] Screens created.");
    showScreen(SCREEN_WATCH_HOME);
    Serial.println("[UI] Home screen loaded.");
    updateScreens();
    Serial.println("[UI] Screen data updated.");
    lastUpdateMs = millis();
    Serial.println("[UI] Six-screen health interface initialized");
}

void UIManager::createScreens()
{
    for (uint8_t index = 0; index < SCREEN_COUNT; ++index)
    {
        Serial.printf("[UI] Creating screen %u...\n", index);
        logLvglMemory("before screen");
        screenRoots[index] = createScreen(static_cast<Screen>(index));
        logLvglMemory("after screen");
        if (screenRoots[index] == nullptr)
        {
            Serial.printf("[UI] ERROR: Could not create screen %u\n", index);
            continue;
        }
        Serial.printf("[UI] Screen %u created.\n", index);

        lv_obj_add_event_cb(
            screenRoots[index],
            screenGestureCallback,
            LV_EVENT_GESTURE,
            this
        );
        lv_obj_add_flag(screenRoots[index], LV_OBJ_FLAG_CLICKABLE);
        lv_obj_add_event_cb(
            screenRoots[index],
            openFacePickerCallback,
            LV_EVENT_LONG_PRESSED,
            this
        );
    }

    Serial.println("[UI] Creating face picker...");
    createFacePicker();
    Serial.println("[UI] Applying home face...");
    applyHomeFace();
}

void UIManager::createFacePicker()
{
    facePickerRoot = lv_obj_create(nullptr);
    if (facePickerRoot == nullptr)
    {
        Serial.println("[UI] ERROR: Could not create home-face picker");
        return;
    }

    lv_obj_set_size(facePickerRoot, DISPLAY_WIDTH, DISPLAY_HEIGHT);
    lv_obj_set_style_bg_color(facePickerRoot, UI_COLOR_BACKGROUND, 0);
    lv_obj_set_style_bg_opa(facePickerRoot, LV_OPA_COVER, 0);
    lv_obj_set_style_border_width(facePickerRoot, 0, 0);
    lv_obj_set_style_pad_all(facePickerRoot, 0, 0);
    lv_obj_clear_flag(facePickerRoot, LV_OBJ_FLAG_SCROLLABLE);
    createLabel(facePickerRoot, "CHOOSE HOME FACE", MARGIN, 11, CONTENT_WIDTH, 28, font_h4, UI_COLOR_TEXT);
    createLabel(facePickerRoot, "Tap to preview and save", MARGIN, 38, CONTENT_WIDTH, 18, font_body, UI_COLOR_MUTED);

    const char* names[] =
    {
        "ANALOG MINIMALIST",
        "DIGITAL BOLD ECG",
        "DATA-RICH",
        "CIRCULAR PROGRESS",
        "ULTRA MINIMAL",
        "SPORTY BOLD"
    };
    const char* descriptions[] =
    {
        "Classic dial and pulse",
        "Large digital time",
        "Time, steps, heart, weather",
        "Daily step goal rings",
        "Quiet, uncluttered clock",
        "Bold time and health stats"
    };

    for (uint8_t face = 0; face < 6; ++face)
    {
        lv_obj_t* button = lv_button_create(facePickerRoot);
        const int32_t y = 61 + static_cast<int32_t>(face) * 36;
        lv_obj_set_pos(button, MARGIN, y);
        lv_obj_set_size(button, CONTENT_WIDTH, 32);
        styleButton(button, face == selectedHomeFace);
        faceSelectionButtons[face] = button;
        createLabel(button, names[face], 9, 2, CONTENT_WIDTH - 18, 14, font_body, UI_COLOR_ACCENT);
        createLabel(button, descriptions[face], 9, 16, CONTENT_WIDTH - 18, 14, font_body, UI_COLOR_TEXT);
        faceSelectionContexts[face] = {this, face};
        lv_obj_add_event_cb(
            button,
            selectHomeFaceCallback,
            LV_EVENT_CLICKED,
            &faceSelectionContexts[face]
        );
    }

    lv_obj_t* back = lv_button_create(facePickerRoot);
    lv_obj_set_pos(back, MARGIN, 286);
    lv_obj_set_size(back, CONTENT_WIDTH, 25);
    styleButton(back, false);
    lv_obj_t* backLabel = createLabel(back, "CANCEL", 8, 3, CONTENT_WIDTH - 16, 19, font_body, UI_COLOR_MUTED, LV_TEXT_ALIGN_CENTER);
    lv_obj_add_flag(backLabel, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_add_event_cb(back, closeFacePickerCallback, LV_EVENT_CLICKED, this);
}

lv_obj_t* UIManager::createScreen(Screen screen)
{
    lv_obj_t* root = lv_obj_create(nullptr);
    if (root == nullptr)
    {
        return nullptr;
    }

    lv_obj_set_size(root, DISPLAY_WIDTH, DISPLAY_HEIGHT);
    lv_obj_set_style_bg_color(root, UI_COLOR_BACKGROUND, 0);
    lv_obj_set_style_bg_opa(root, LV_OPA_COVER, 0);
    lv_obj_set_style_border_width(root, 0, 0);
    lv_obj_set_style_radius(root, 0, 0);
    lv_obj_set_style_pad_all(root, 0, 0);
    lv_obj_clear_flag(root, LV_OBJ_FLAG_SCROLLABLE);

    switch (screen)
    {
        case SCREEN_WATCH_HOME:
        {
            for (uint8_t face = 0; face < 6; ++face)
            {
                homeFaces[face] = createFacePanel(root);
            }

            lv_obj_t* analog = homeFaces[0];
            lv_obj_t* analogRing = createCard(analog, 16, 61, 208, 208, UI_COLOR_BACKGROUND, LV_RADIUS_CIRCLE);
            lv_obj_set_style_bg_opa(analogRing, LV_OPA_TRANSP, 0);
            lv_obj_set_style_border_color(analogRing, UI_COLOR_CARD_ALT, 0);
            lv_obj_set_style_border_width(analogRing, 3, 0);
            for (uint8_t tick = 0; tick < 12; ++tick)
            {
                const float angle = (static_cast<float>(tick) * 30.0f - 90.0f) * 0.0174532925f;
                const int32_t x = 120 + static_cast<int32_t>(cosf(angle) * 83.0f) - 2;
                const int32_t y = 165 + static_cast<int32_t>(sinf(angle) * 83.0f) - 2;
                createCard(analog, x, y, 4, 4, UI_COLOR_MUTED, LV_RADIUS_CIRCLE);
            }
            const lv_point_precise_t handDefault[2] = {{120, 165}, {120, 107}};
            faceAnalogHourHand = createFaceLine(analog, handDefault, 2, UI_COLOR_TEXT, 4);
            faceAnalogMinuteHand = createFaceLine(analog, handDefault, 2, UI_COLOR_MUTED, 2);
            faceAnalogSecondHand = createFaceLine(analog, handDefault, 2, UI_COLOR_ACCENT, 1);
            createCard(analog, 115, 160, 10, 10, UI_COLOR_ACCENT, LV_RADIUS_CIRCLE);
            faceClock[0] = createLabel(analog, "--:--", 91, 72, 58, 18, font_body, UI_COLOR_MUTED, LV_TEXT_ALIGN_CENTER);
            faceHeart[0] = createLabel(analog, "-- BPM", 58, 205, 124, 24, font_h5, UI_COLOR_ACCENT, LV_TEXT_ALIGN_CENTER);
            faceDate[0] = createLabel(analog, "WAITING FOR PHONE TIME", 20, 282, 200, 20, font_body, UI_COLOR_MUTED, LV_TEXT_ALIGN_CENTER);
            createLabel(analog, "PulseOn", 85, 252, 70, 16, font_body, UI_COLOR_ACCENT, LV_TEXT_ALIGN_CENTER);

            lv_obj_t* digital = homeFaces[1];
            faceClock[1] = createLabel(digital, "--:--", 8, 121, 224, 72, font_h1, UI_COLOR_TEXT, LV_TEXT_ALIGN_CENTER);
            createLabel(digital, "LIVE ECG", 8, 202, 224, 24, font_h5, UI_COLOR_ACCENT, LV_TEXT_ALIGN_CENTER);
            const lv_point_precise_t ecgPoints[] =
            {
                {12, 178}, {32, 178}, {41, 169}, {47, 188}, {56, 138},
                {66, 213}, {76, 177}, {92, 177}, {101, 169}, {109, 188},
                {119, 138}, {129, 213}, {139, 177}, {157, 177}, {166, 169},
                {174, 188}, {184, 145}, {194, 207}, {204, 178}, {228, 178}
            };
            createFaceLine(digital, ecgPoints, sizeof(ecgPoints) / sizeof(ecgPoints[0]), UI_COLOR_ACCENT, 2);
            faceDate[1] = createLabel(digital, "WAITING FOR PHONE TIME", 20, 268, 200, 20, font_body, UI_COLOR_MUTED, LV_TEXT_ALIGN_CENTER);

            lv_obj_t* data = homeFaces[2];
            faceClock[2] = createLabel(data, "--:--", 16, 39, 208, 50, font_h1, UI_COLOR_TEXT, LV_TEXT_ALIGN_CENTER);
            faceSteps[2] = createLabel(data, "-- STEPS", 22, 111, 90, 32, font_h5, UI_COLOR_TEXT, LV_TEXT_ALIGN_CENTER);
            createCard(data, 119, 104, 1, 54, UI_COLOR_CARD_ALT, 0);
            createCard(data, 22, 157, 196, 1, UI_COLOR_CARD_ALT, 0);
            faceHeart[2] = createLabel(data, "-- BPM", 22, 182, 90, 30, font_h5, UI_COLOR_ACCENT, LV_TEXT_ALIGN_CENTER);
            faceWeather[2] = createLabel(data, "--°", 128, 182, 88, 30, font_h5, UI_COLOR_TEXT, LV_TEXT_ALIGN_CENTER);
            createCard(data, 119, 169, 1, 54, UI_COLOR_CARD_ALT, 0);
            faceDate[2] = createLabel(data, "WAITING FOR PHONE TIME", 20, 261, 200, 20, font_body, UI_COLOR_MUTED, LV_TEXT_ALIGN_CENTER);

            lv_obj_t* rings = homeFaces[3];
            createBadge(rings, "MOVE", 36);
            faceActivityArc = lv_arc_create(rings);
            lv_obj_set_pos(faceActivityArc, 29, 75);
            lv_obj_set_size(faceActivityArc, 182, 182);
            lv_arc_set_range(faceActivityArc, 0, 100);
            lv_arc_set_bg_angles(faceActivityArc, 135, 45);
            lv_arc_set_angles(faceActivityArc, 135, 135);
            lv_arc_set_value(faceActivityArc, 0);
            lv_obj_set_style_bg_opa(faceActivityArc, LV_OPA_TRANSP, LV_PART_MAIN);
            lv_obj_set_style_arc_color(faceActivityArc, UI_COLOR_CARD_ALT, LV_PART_MAIN);
            lv_obj_set_style_arc_width(faceActivityArc, 5, LV_PART_MAIN);
            lv_obj_set_style_arc_color(faceActivityArc, UI_COLOR_ACCENT, LV_PART_INDICATOR);
            lv_obj_set_style_arc_width(faceActivityArc, 5, LV_PART_INDICATOR);
            lv_obj_set_style_opa(faceActivityArc, LV_OPA_TRANSP, LV_PART_KNOB);
            lv_obj_clear_flag(faceActivityArc, LV_OBJ_FLAG_CLICKABLE);
            lv_obj_t* innerRing = createCard(rings, 42, 88, 156, 156, UI_COLOR_BACKGROUND, LV_RADIUS_CIRCLE);
            lv_obj_set_style_bg_opa(innerRing, LV_OPA_TRANSP, 0);
            lv_obj_set_style_border_color(innerRing, UI_COLOR_GOOD, 0);
            lv_obj_set_style_border_width(innerRing, 3, 0);
            faceActivityPercent = createLabel(rings, "--%", 42, 135, 156, 48, font_h1, UI_COLOR_TEXT, LV_TEXT_ALIGN_CENTER);
            faceSteps[3] = createLabel(rings, "-- steps", 45, 184, 150, 24, font_h5, UI_COLOR_MUTED, LV_TEXT_ALIGN_CENTER);
            createLabel(rings, "GOAL 10,000 STEPS", 20, 273, 200, 20, font_body, UI_COLOR_MUTED, LV_TEXT_ALIGN_CENTER);

            lv_obj_t* minimal = homeFaces[4];
            faceClock[4] = createLabel(minimal, "--:--", 8, 124, 224, 74, font_h1, UI_COLOR_MUTED, LV_TEXT_ALIGN_CENTER);
            faceDate[4] = createLabel(minimal, "WAITING FOR PHONE TIME", 20, 208, 200, 20, font_body, UI_COLOR_MUTED, LV_TEXT_ALIGN_CENTER);
            createCard(minimal, 115, 257, 10, 10, UI_COLOR_ACCENT, LV_RADIUS_CIRCLE);
            createLabel(minimal, "PulseOn", 85, 282, 70, 16, font_body, UI_COLOR_MUTED, LV_TEXT_ALIGN_CENTER);

            lv_obj_t* sport = homeFaces[5];
            faceClock[5] = createLabel(sport, "--:--", 8, 68, 224, 92, font_h1, UI_COLOR_TEXT, LV_TEXT_ALIGN_CENTER);
            faceCalories[5] = createLabel(sport, "-- KCAL", 28, 172, 88, 38, font_h4, UI_COLOR_ACCENT, LV_TEXT_ALIGN_CENTER);
            faceOxygen[5] = createLabel(sport, "--% SpO2", 124, 172, 92, 38, font_h4, UI_COLOR_ACCENT, LV_TEXT_ALIGN_CENTER);
            const lv_point_precise_t sportPulse[] =
            {
                {33, 245}, {79, 245}, {88, 240}, {96, 257}, {105, 228},
                {115, 264}, {124, 245}, {207, 245}
            };
            createFaceLine(sport, sportPulse, sizeof(sportPulse) / sizeof(sportPulse[0]), UI_COLOR_ACCENT, 2);
            faceDate[5] = createLabel(sport, "WAITING FOR PHONE TIME", 20, 276, 200, 20, font_body, UI_COLOR_MUTED, LV_TEXT_ALIGN_CENTER);

            break;
        }
        case SCREEN_HEART_RATE:
        {
            createBadge(root, "HEART RATE", 26);
            heartRateValue = createLabel(root, "-- BPM", 12, 91, 216, 66, font_h1, UI_COLOR_TEXT, LV_TEXT_ALIGN_CENTER);
            heartRateStatus = createLabel(root, "No live reading", MARGIN, 158, CONTENT_WIDTH, 24, font_body, UI_COLOR_MUTED, LV_TEXT_ALIGN_CENTER);
            createCard(root, MARGIN, 207, CONTENT_WIDTH, 1, UI_COLOR_CARD_ALT, 0);
            createLabel(root, "Heart-rate data needs a supported sensor.", 28, 222, 184, 42, font_body, UI_COLOR_MUTED, LV_TEXT_ALIGN_CENTER);
            break;
        }
        case SCREEN_SLEEP:
        {
            createBadge(root, "SLEEP", 26);
            sleepDuration = createLabel(root, "--h --m", 12, 78, 216, 58, font_h1, UI_COLOR_TEXT, LV_TEXT_ALIGN_CENTER);
            sleepStatus = createLabel(root, "Sleep data unavailable", MARGIN, 137, CONTENT_WIDTH, 24, font_body, UI_COLOR_MUTED, LV_TEXT_ALIGN_CENTER);

            const char* stages[] = {"Deep", "Core", "REM"};
            for (uint8_t stage = 0; stage < 3; ++stage)
            {
                const int32_t y = 184 + static_cast<int32_t>(stage) * 36;
                createLabel(root, stages[stage], 24, y, 70, 22, font_h5, UI_COLOR_TEXT);
                createLabel(root, "--", 172, y, 42, 22, font_h5, UI_COLOR_MUTED, LV_TEXT_ALIGN_RIGHT);
                createCard(root, 24, y + 23, CONTENT_WIDTH, 5, UI_COLOR_CARD_ALT, 3);
            }
            createLabel(root, "Sleep stages appear when data is available.", MARGIN, 294, CONTENT_WIDTH, 18, font_body, UI_COLOR_MUTED, LV_TEXT_ALIGN_CENTER);
            break;
        }
        case SCREEN_ACTIVITY:
        {
            createBadge(root, "ACTIVITY", 26);
            lv_obj_t* activityRing = lv_obj_create(root);
            lv_obj_set_pos(activityRing, 30, 69);
            lv_obj_set_size(activityRing, 180, 180);
            lv_obj_set_style_bg_opa(activityRing, LV_OPA_TRANSP, 0);
            lv_obj_set_style_border_color(activityRing, UI_COLOR_ACCENT_DARK, 0);
            lv_obj_set_style_border_width(activityRing, 6, 0);
            lv_obj_set_style_radius(activityRing, LV_RADIUS_CIRCLE, 0);
            lv_obj_clear_flag(activityRing, LV_OBJ_FLAG_SCROLLABLE);
            activitySteps = createLabel(root, "--", 42, 123, 156, 54, font_h1, UI_COLOR_TEXT, LV_TEXT_ALIGN_CENTER);
            createLabel(root, "steps", 42, 175, 156, 26, font_h5, UI_COLOR_MUTED, LV_TEXT_ALIGN_CENTER);

            lv_obj_t* calories = createCard(root, MARGIN, 263, 98, 43);
            createLabel(calories, "CALORIES", 7, 3, 84, 16, font_body, UI_COLOR_MUTED, LV_TEXT_ALIGN_CENTER);
            activityCalories = createLabel(calories, "-- kcal", 7, 20, 84, 20, font_h5, UI_COLOR_TEXT, LV_TEXT_ALIGN_CENTER);
            lv_obj_t* distance = createCard(root, 126, 263, 98, 43);
            createLabel(distance, "DISTANCE", 7, 3, 84, 16, font_body, UI_COLOR_MUTED, LV_TEXT_ALIGN_CENTER);
            createLabel(distance, "-- km", 7, 20, 84, 20, font_h5, UI_COLOR_TEXT, LV_TEXT_ALIGN_CENTER);
            break;
        }
        case SCREEN_BLOOD_OXYGEN:
        {
            createBadge(root, "SpO2", 26);
            oxygenValue = createLabel(root, "--%", 12, 88, 216, 82, font_h1, UI_COLOR_TEXT, LV_TEXT_ALIGN_CENTER);
            createLabel(root, "Blood oxygen", MARGIN, 167, CONTENT_WIDTH, 26, font_h5, UI_COLOR_MUTED, LV_TEXT_ALIGN_CENTER);
            lv_obj_t* status = createCard(root, 32, 218, 176, 42, UI_COLOR_CARD);
            oxygenStatus = createLabel(status, "No reading available", 8, 10, 160, 22, font_body, UI_COLOR_MUTED, LV_TEXT_ALIGN_CENTER);
            createLabel(root, "A supported sensor must provide a reading.", 28, 273, 184, 36, font_body, UI_COLOR_MUTED, LV_TEXT_ALIGN_CENTER);
            break;
        }
        case SCREEN_WORKOUT:
        {
            createBadge(root, "WORKOUT", 22);
            workoutStatus = createLabel(root, "Choose a workout", MARGIN, 58, CONTENT_WIDTH, 26, font_h5, UI_COLOR_TEXT, LV_TEXT_ALIGN_CENTER);
            const char* modes[] = {"RUN", "CYCLE", "HIIT"};
            const char* durations[] = {"Outdoor run  |  30-60 min", "Cycling  |  20-45 min", "HIIT  |  15-30 min"};
            for (uint8_t mode = 0; mode < 3; ++mode)
            {
                lv_obj_t* button = lv_button_create(root);
                const int32_t y = 99 + static_cast<int32_t>(mode) * 51;
                lv_obj_set_pos(button, MARGIN, y);
                lv_obj_set_size(button, CONTENT_WIDTH, 43);
                styleButton(button, mode == selectedWorkoutMode);
                workoutModeButtons[mode] = button;
                lv_obj_t* modeLabel = createLabel(button, modes[mode], 12, 10, 53, 22, font_h5, UI_COLOR_ACCENT);
                styleButtonLabel(modeLabel);
                lv_obj_t* description = createLabel(button, durations[mode], 69, 11, 125, 20, font_body, UI_COLOR_TEXT);
                styleButtonLabel(description);
                workoutModeContexts[mode] = {this, mode};
                lv_obj_add_event_cb(
                    button,
                    workoutModeCallback,
                    LV_EVENT_CLICKED,
                    &workoutModeContexts[mode]
                );
            }

            lv_obj_t* startButton = lv_button_create(root);
            lv_obj_set_pos(startButton, MARGIN, 270);
            lv_obj_set_size(startButton, CONTENT_WIDTH, 40);
            lv_obj_set_style_bg_color(startButton, UI_COLOR_ACCENT, 0);
            lv_obj_set_style_bg_opa(startButton, LV_OPA_COVER, 0);
            lv_obj_set_style_border_width(startButton, 0, 0);
            lv_obj_set_style_radius(startButton, 20, 0);
            createLabel(startButton, "START", 8, 7, CONTENT_WIDTH - 16, 26, font_h5, UI_COLOR_BACKGROUND, LV_TEXT_ALIGN_CENTER);
            lv_obj_add_event_cb(startButton, workoutStartCallback, LV_EVENT_CLICKED, this);
            break;
        }
        default:
            return nullptr;
    }

    if (screen == SCREEN_WATCH_HOME)
    {
        homeConnection = createLabel(
            root,
            "BT  OFFLINE",
            MARGIN,
            18,
            150,
            22,
            font_h5,
            UI_COLOR_MUTED
        );
        homeBattery = createLabel(
            root,
            "--%",
            DISPLAY_WIDTH - MARGIN - 50,
            18,
            50,
            22,
            font_h5,
            UI_COLOR_ACCENT,
            LV_TEXT_ALIGN_RIGHT
        );
    }

    for (uint8_t index = 0; index < SCREEN_COUNT; ++index)
    {
        const int32_t dotX = 91 + static_cast<int32_t>(index) * 12;
        pageDots[index] = createCard(root, dotX, DISPLAY_HEIGHT - 10, 5, 5, UI_COLOR_CARD_ALT, LV_RADIUS_CIRCLE);
    }

    return root;
}

void UIManager::showScreen(Screen screen)
{
    if (screen >= SCREEN_COUNT || screenRoots[screen] == nullptr)
    {
        return;
    }

    currentScreen = screen;
    if (appState != nullptr)
    {
        appState->setActiveScreen(static_cast<uint8_t>(screen));
    }

    lv_screen_load(screenRoots[screen]);
    updatePageDots();
}

void UIManager::updatePageDots()
{
    for (uint8_t index = 0; index < SCREEN_COUNT; ++index)
    {
        if (pageDots[index] != nullptr)
        {
            lv_obj_set_style_bg_color(
                pageDots[index],
                index == currentScreen ? UI_COLOR_ACCENT : UI_COLOR_CARD_ALT,
                0
            );
        }
    }
}

void UIManager::applyHomeFace()
{
    for (uint8_t face = 0; face < 6; ++face)
    {
        if (homeFaces[face] != nullptr)
        {
            if (face == selectedHomeFace)
            {
                lv_obj_clear_flag(homeFaces[face], LV_OBJ_FLAG_HIDDEN);
            }
            else
            {
                lv_obj_add_flag(homeFaces[face], LV_OBJ_FLAG_HIDDEN);
            }
        }
        if (faceSelectionButtons[face] != nullptr)
        {
            styleButton(faceSelectionButtons[face], face == selectedHomeFace);
        }
    }
}

void UIManager::attachChronos(ChronosManager* chronosManager)
{
    chronos = chronosManager;
}

void UIManager::openFacePickerCallback(lv_event_t* event)
{
    UIManager* ui = static_cast<UIManager*>(lv_event_get_user_data(event));
    if (ui == nullptr || ui->facePickerRoot == nullptr)
    {
        return;
    }

    ui->facePickerReturnScreen = ui->currentScreen;
    lv_screen_load(ui->facePickerRoot);
}

void UIManager::selectHomeFaceCallback(lv_event_t* event)
{
    FaceSelectionContext* selection =
        static_cast<FaceSelectionContext*>(lv_event_get_user_data(event));
    if (selection == nullptr || selection->manager == nullptr || selection->face >= 6)
    {
        return;
    }

    UIManager* ui = selection->manager;
    ui->selectedHomeFace = selection->face;
    ui->applyHomeFace();

    Preferences preferences;
    if (!preferences.begin("pulseon", false))
    {
        Serial.println("[UI] ERROR: Could not open settings to save home face");
    }
    else
    {
        const size_t written = preferences.putUChar("homeFace", ui->selectedHomeFace);
        preferences.end();
        if (written != sizeof(uint8_t))
        {
            Serial.println("[UI] ERROR: Could not persist selected home face");
        }
    }

    ui->showScreen(ui->facePickerReturnScreen);
}

void UIManager::closeFacePickerCallback(lv_event_t* event)
{
    UIManager* ui = static_cast<UIManager*>(lv_event_get_user_data(event));
    if (ui != nullptr)
    {
        ui->showScreen(ui->facePickerReturnScreen);
    }
}

void UIManager::screenGestureCallback(lv_event_t* event)
{
    UIManager* ui = static_cast<UIManager*>(lv_event_get_user_data(event));
    lv_indev_t* input = lv_event_get_indev(event);
    if (ui == nullptr || input == nullptr)
    {
        return;
    }

    const lv_dir_t direction = lv_indev_get_gesture_dir(input);
    if (direction == LV_DIR_LEFT)
    {
        const uint8_t next =
            (static_cast<uint8_t>(ui->currentScreen) + 1) % SCREEN_COUNT;
        ui->showScreen(static_cast<Screen>(next));
    }
    else if (direction == LV_DIR_RIGHT)
    {
        const uint8_t previous =
            (static_cast<uint8_t>(ui->currentScreen) + SCREEN_COUNT - 1) %
            SCREEN_COUNT;
        ui->showScreen(static_cast<Screen>(previous));
    }
}

void UIManager::workoutModeCallback(lv_event_t* event)
{
    WorkoutModeContext* context =
        static_cast<WorkoutModeContext*>(lv_event_get_user_data(event));
    if (context == nullptr || context->manager == nullptr || context->mode >= 3)
    {
        return;
    }

    UIManager* ui = context->manager;
    ui->selectedWorkoutMode = context->mode;

    for (uint8_t mode = 0; mode < 3; ++mode)
    {
        if (ui->workoutModeButtons[mode] != nullptr)
        {
            styleButton(ui->workoutModeButtons[mode], mode == ui->selectedWorkoutMode);
        }
    }
    lv_label_set_text(ui->workoutStatus, "Choose a workout");
}

void UIManager::workoutStartCallback(lv_event_t* event)
{
    UIManager* ui = static_cast<UIManager*>(lv_event_get_user_data(event));
    if (ui != nullptr)
    {
        lv_label_set_text(ui->workoutStatus, "Tracking needs a supported sensor");
    }
}

UIManager::Screen UIManager::getCurrentScreen() const
{
    return currentScreen;
}

void UIManager::update()
{
    if (appState == nullptr)
    {
        return;
    }

    const uint32_t now = millis();
    if (now - lastUpdateMs < 1000)
    {
        return;
    }

    lastUpdateMs = now;
    updateScreens();
}

void UIManager::updateScreens()
{
    if (appState == nullptr)
    {
        return;
    }

    const PulseonAppState& state = appState->getState();
    String clockText = "--:--";
    String dateText = "WAITING FOR PHONE TIME";
    time_t currentTime;
    if (state.clockSynced && time(&currentTime) != static_cast<time_t>(-1))
    {
        struct tm timeInfo;
        if (localtime_r(&currentTime, &timeInfo) != nullptr)
        {
            char clockBuffer[6];
            char dateBuffer[16];
            strftime(clockBuffer, sizeof(clockBuffer), state.is24Hour ? "%H:%M" : "%I:%M", &timeInfo);
            strftime(dateBuffer, sizeof(dateBuffer), "%a, %b %d", &timeInfo);
            clockText = clockBuffer;
            dateText = dateBuffer;
        }
    }

    lv_label_set_text(
        homeConnection,
        state.phoneConnected ? "BT  CONNECTED" : "BT  OFFLINE"
    );
    lv_obj_set_style_text_color(
        homeConnection,
        state.phoneConnected ? UI_COLOR_GOOD : UI_COLOR_MUTED,
        0
    );
    if (state.phoneConnected)
    {
        lv_label_set_text_fmt(homeBattery, "%u%%", static_cast<unsigned>(state.phoneBattery));
    }
    else
    {
        lv_label_set_text(homeBattery, "--%");
    }

    for (uint8_t face = 0; face < 6; ++face)
    {
        if (faceClock[face] != nullptr)
        {
            lv_label_set_text(faceClock[face], clockText.c_str());
        }
        if (faceDate[face] != nullptr)
        {
            lv_label_set_text(faceDate[face], dateText.c_str());
        }
        if (faceHeart[face] != nullptr)
        {
            if (state.heartRate > 0)
            {
                lv_label_set_text_fmt(faceHeart[face], "%u BPM", static_cast<unsigned>(state.heartRate));
            }
            else
            {
                lv_label_set_text(faceHeart[face], "-- BPM");
            }
        }
    }

    if (state.heartRate > 0)
    {
        lv_label_set_text_fmt(heartRateValue, "%u BPM", static_cast<unsigned>(state.heartRate));
        lv_label_set_text(heartRateStatus, "Live reading");
    }
    else
    {
        lv_label_set_text(heartRateValue, "-- BPM");
        lv_label_set_text(heartRateStatus, "No live reading");
    }

    if (state.steps > 0)
    {
        lv_label_set_text_fmt(activitySteps, "%u", static_cast<unsigned>(state.steps));
        lv_label_set_text_fmt(faceSteps[2], "%u STEPS", static_cast<unsigned>(state.steps));
        lv_label_set_text_fmt(faceSteps[3], "%u steps", static_cast<unsigned>(state.steps));
        const uint16_t progress = state.steps >= 10000
            ? 100
            : static_cast<uint16_t>((static_cast<uint32_t>(state.steps) * 100) / 10000);
        lv_label_set_text_fmt(faceActivityPercent, "%u%%", static_cast<unsigned>(progress));
        lv_arc_set_value(faceActivityArc, progress);
    }
    else
    {
        lv_label_set_text(activitySteps, "--");
        lv_label_set_text(faceSteps[2], "-- STEPS");
        lv_label_set_text(faceSteps[3], "-- steps");
        lv_label_set_text(faceActivityPercent, "--%");
        lv_arc_set_value(faceActivityArc, 0);
    }
    lv_label_set_text(activityCalories, "-- kcal");
    lv_label_set_text(faceCalories[5], "-- KCAL");

    if (state.weatherAvailable)
    {
        lv_label_set_text_fmt(faceWeather[2], "%d°", state.weatherTemperature);
    }
    else
    {
        lv_label_set_text(faceWeather[2], "--°");
    }

    if (state.bloodOxygen > 0)
    {
        lv_label_set_text_fmt(oxygenValue, "%u%%", static_cast<unsigned>(state.bloodOxygen));
        lv_label_set_text(oxygenStatus, "Reading available");
        lv_label_set_text_fmt(faceOxygen[5], "%u%% SpO2", static_cast<unsigned>(state.bloodOxygen));
    }
    else
    {
        lv_label_set_text(oxygenValue, "--%");
        lv_label_set_text(oxygenStatus, "No reading available");
        lv_label_set_text(faceOxygen[5], "--% SpO2");
    }

    lv_label_set_text(sleepDuration, "--h --m");
    lv_label_set_text(sleepStatus, "Sleep data unavailable");

    if (state.clockSynced)
    {
        time(&currentTime);
        struct tm timeInfo;
        if (localtime_r(&currentTime, &timeInfo) != nullptr)
        {
            const float secondsAngle = (static_cast<float>(timeInfo.tm_sec) * 6.0f - 90.0f) * 0.0174532925f;
            const float minutesAngle = ((static_cast<float>(timeInfo.tm_min) + timeInfo.tm_sec / 60.0f) * 6.0f - 90.0f) * 0.0174532925f;
            const float hoursAngle = ((static_cast<float>(timeInfo.tm_hour % 12) + timeInfo.tm_min / 60.0f) * 30.0f - 90.0f) * 0.0174532925f;

            analogHourPoints[0] = {120, 165};
            analogHourPoints[1] = {
                static_cast<lv_value_precise_t>(120 + cosf(hoursAngle) * 42.0f),
                static_cast<lv_value_precise_t>(165 + sinf(hoursAngle) * 42.0f)
            };
            analogMinutePoints[0] = {120, 165};
            analogMinutePoints[1] = {
                static_cast<lv_value_precise_t>(120 + cosf(minutesAngle) * 65.0f),
                static_cast<lv_value_precise_t>(165 + sinf(minutesAngle) * 65.0f)
            };
            analogSecondPoints[0] = {120, 165};
            analogSecondPoints[1] = {
                static_cast<lv_value_precise_t>(120 + cosf(secondsAngle) * 74.0f),
                static_cast<lv_value_precise_t>(165 + sinf(secondsAngle) * 74.0f)
            };

            lv_line_set_points(faceAnalogHourHand, analogHourPoints, 2);
            lv_line_set_points(faceAnalogMinuteHand, analogMinutePoints, 2);
            lv_line_set_points(faceAnalogSecondHand, analogSecondPoints, 2);
        }
    }
}
