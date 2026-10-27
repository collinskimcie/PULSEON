#include "UIManager.h"

#include <cmath>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <Preferences.h>

#include "app_config.h"
#include "UIUtils.h"
#include "PULSEON_WATCH_UI.h"

namespace
{
constexpr int32_t DISPLAY_WIDTH = 240;
constexpr int32_t DISPLAY_HEIGHT = 320;
constexpr int32_t MARGIN = 16;
constexpr int32_t CONTENT_WIDTH = DISPLAY_WIDTH - (MARGIN * 2);
constexpr int32_t FACE_CIRCLE_TOP = 40;

const lv_color_t UI_COLOR_BACKGROUND = lv_color_hex(0x090A0E);
const lv_color_t UI_COLOR_CARD = lv_color_hex(0x15161C);
const lv_color_t UI_COLOR_CARD_ALT = lv_color_hex(0x25262D);
const lv_color_t UI_COLOR_TEXT = lv_color_hex(0xF7F7FA);
const lv_color_t UI_COLOR_MUTED = lv_color_hex(0xA8A3AB);
const lv_color_t UI_COLOR_ACCENT = lv_color_hex(0xFF5D6C);
const lv_color_t UI_COLOR_ACCENT_DARK = lv_color_hex(0x54252D);
const lv_color_t UI_COLOR_GOOD = lv_color_hex(0x75D6B1);
const lv_color_t UI_COLOR_AMBER = lv_color_hex(0xFFC66D);
const lv_color_t UI_COLOR_TOPO = lv_color_hex(0x3A8997);
const lv_color_t UI_COLOR_CIRCUIT = lv_color_hex(0xFF796D);
const lv_color_t UI_COLOR_PRISM = lv_color_hex(0xB8A5FF);
lv_obj_t* homeFacePanels[6] = {};

int32_t faceChildY(lv_obj_t* parent, int32_t y)
{
    for (lv_obj_t* facePanel : homeFacePanels)
    {
        if (facePanel == parent)
        {
            return y - FACE_CIRCLE_TOP;
        }
    }
    return y;
}

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
    lv_obj_set_pos(label, x, faceChildY(parent, y));
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
    lv_obj_set_pos(card, x, faceChildY(parent, y));
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

lv_obj_t* createFacePanel(lv_obj_t* parent, uint8_t index)
{
    lv_obj_t* panel = lv_obj_create(parent);
    lv_obj_set_pos(panel, 0, FACE_CIRCLE_TOP);
    lv_obj_set_size(panel, DISPLAY_WIDTH, DISPLAY_WIDTH);
    lv_obj_set_style_bg_opa(panel, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_width(panel, 0, 0);
    lv_obj_set_style_radius(panel, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_style_pad_all(panel, 0, 0);
    lv_obj_clear_flag(panel, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_flag(panel, LV_OBJ_FLAG_EVENT_BUBBLE);
    homeFacePanels[index] = panel;
    return panel;
}

lv_obj_t* createWatchFaceFrame(lv_obj_t* parent, lv_color_t borderColor)
{
    lv_obj_t* frame = createCard(
        parent,
        7,
        47,
        226,
        226,
        UI_COLOR_BACKGROUND,
        LV_RADIUS_CIRCLE
    );
    lv_obj_set_style_bg_opa(frame, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_color(frame, borderColor, 0);
    lv_obj_set_style_border_width(frame, 2, 0);
    return frame;
}

lv_obj_t* createMetricPill(
    lv_obj_t* parent,
    int32_t x,
    int32_t y,
    int32_t width,
    const char* text,
    lv_color_t color,
    lv_color_t background
)
{
    lv_obj_t* pill = createCard(parent, x, y, width, 26, background, 13);
    lv_obj_set_style_bg_opa(pill, 190, 0);
    return createLabel(pill, text, 4, 2, width - 8, 22, font_h5, color, LV_TEXT_ALIGN_CENTER);
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
    if (selectedHomeFace >= 9)
    {
        selectedHomeFace = 0;
    }
    {
        Preferences goalPrefs;
        if (goalPrefs.begin("pulseon", true))
        {
            stepGoal = goalPrefs.getUShort("stepGoal", 10000);
            goalPrefs.end();
        }
        if (stepGoal < 1000 || stepGoal > 20000)
        {
            stepGoal = 10000;
        }
    }
    restoreClock();

    Serial.println("[UI] Initializing six-screen health interface...");
    PULSEON_WATCH_UI_init(nullptr);
    createScreens();
    rebuildClassicFaces();
    overlays.begin(appState, chronos);
    apps.begin(appState, chronos, &overlays);
    sysui.begin(appState, chronos, &apps);
    apps.addTile("Step goal", stepGoalTile, this);
    apps.addTile("Stopwatch", uiStopwatchOpen, nullptr);
    apps.addTile("Timer", uiTimerOpen, nullptr);
    apps.addTile("Flashlight", uiFlashlightOpen, nullptr);
    showScreen(SCREEN_WATCH_HOME);
    updateScreens();
    lastUpdateMs = millis();
    Serial.println("[UI] Six-screen health interface initialized");
}

void UIManager::createScreens()
{
    for (uint8_t index = 0; index < SCREEN_COUNT; ++index)
    {
        screenRoots[index] = createScreen(static_cast<Screen>(index));
        if (screenRoots[index] == nullptr)
        {
            Serial.printf("[UI] ERROR: Could not create screen %u\n", index);
            continue;
        }

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

    createFacePicker();
    applyHomeFace();
    createConnectionToast();
}

void UIManager::createConnectionToast()
{
    connectionToast = lv_obj_create(lv_layer_top());
    if (connectionToast == nullptr)
    {
        Serial.println("[UI] ERROR: Could not create connection notification");
        return;
    }

    lv_obj_set_size(connectionToast, 184, 36);
    lv_obj_align(connectionToast, LV_ALIGN_TOP_MID, 0, 8);
    lv_obj_set_style_bg_color(connectionToast, UI_COLOR_CARD, 0);
    lv_obj_set_style_bg_opa(connectionToast, LV_OPA_COVER, 0);
    lv_obj_set_style_border_color(connectionToast, UI_COLOR_GOOD, 0);
    lv_obj_set_style_border_width(connectionToast, 1, 0);
    lv_obj_set_style_radius(connectionToast, 18, 0);
    lv_obj_set_style_pad_all(connectionToast, 0, 0);
    lv_obj_clear_flag(connectionToast, LV_OBJ_FLAG_SCROLLABLE);
    connectionToastLabel = createLabel(
        connectionToast,
        "Phone connected",
        8,
        7,
        168,
        22,
        font_h5,
        UI_COLOR_GOOD,
        LV_TEXT_ALIGN_CENTER
    );
    lv_obj_add_flag(connectionToast, LV_OBJ_FLAG_HIDDEN);

    connectionToastTimer = lv_timer_create(connectionToastTimerCallback, 2500, this);
    if (connectionToastTimer == nullptr)
    {
        Serial.println("[UI] ERROR: Could not create connection notification timer");
        return;
    }
    lv_timer_pause(connectionToastTimer);
}

void UIManager::showConnectionToast(bool connected)
{
    if (connectionToast == nullptr ||
        connectionToastLabel == nullptr ||
        connectionToastTimer == nullptr)
    {
        return;
    }

    lv_label_set_text(
        connectionToastLabel,
        connected ? "Phone connected" : "Phone disconnected"
    );
    const lv_color_t color = connected ? UI_COLOR_GOOD : UI_COLOR_ACCENT;
    lv_obj_set_style_border_color(connectionToast, color, 0);
    lv_obj_set_style_text_color(connectionToastLabel, color, 0);
    lv_obj_clear_flag(connectionToast, LV_OBJ_FLAG_HIDDEN);
    lv_timer_reset(connectionToastTimer);
    lv_timer_resume(connectionToastTimer);
}

void UIManager::connectionToastTimerCallback(lv_timer_t* timer)
{
    UIManager* ui = static_cast<UIManager*>(lv_timer_get_user_data(timer));
    if (ui != nullptr && ui->connectionToast != nullptr)
    {
        lv_obj_add_flag(ui->connectionToast, LV_OBJ_FLAG_HIDDEN);
    }
    lv_timer_pause(timer);
}

static void saveTimezone(bool clockSynced)
{
    static String savedTz;
    const char* tz = getenv("TZ");
    if (!clockSynced || tz == nullptr || tz[0] == 0 || savedTz.equals(tz))
    {
        return;
    }
    savedTz = tz;
    Preferences p;
    if (p.begin("pulseon", false))
    {
        if (!p.getString("tz", "").equals(tz))
        {
            p.putString("tz", tz);
        }
        p.end();
    }
}

void UIManager::restoreClock()
{
    if (appState == nullptr)
    {
        return;
    }
    Preferences p;
    if (p.begin("pulseon", true))
    {
        const String tz = p.getString("tz", "");
        p.end();
        if (tz.length() > 0 && getenv("TZ") == nullptr)
        {
            setenv("TZ", tz.c_str(), 1);
            tzset();
        }
    }
    if (time(nullptr) > 1704067200)  // 1 Jan 2024: the clock survived the reset
    {
        appState->setClockSynced(true);
        Serial.println("[UI] System clock still valid after reset");
    }
}

void UIManager::showToast(const char* text, lv_color_t color)
{
    if (connectionToast == nullptr || connectionToastLabel == nullptr || connectionToastTimer == nullptr)
    {
        return;
    }
    lv_label_set_text(connectionToastLabel, text);
    lv_obj_set_style_border_color(connectionToast, color, 0);
    lv_obj_set_style_text_color(connectionToastLabel, color, 0);
    lv_obj_clear_flag(connectionToast, LV_OBJ_FLAG_HIDDEN);
    lv_timer_reset(connectionToastTimer);
    lv_timer_resume(connectionToastTimer);
}

void UIManager::stepGoalTile(void* user)
{
    UIManager* ui = static_cast<UIManager*>(user);
    if (ui == nullptr)
    {
        return;
    }
    static const uint16_t GOALS[5] = {5000, 8000, 10000, 12000, 15000};
    uint8_t next = 0;
    for (uint8_t i = 0; i < 5; ++i)
    {
        if (GOALS[i] == ui->stepGoal)
        {
            next = (i + 1) % 5;
            break;
        }
    }
    ui->stepGoal = GOALS[next];
    Preferences p;
    if (p.begin("pulseon", false))
    {
        p.putUShort("stepGoal", ui->stepGoal);
        p.end();
    }
    char b[32];
    snprintf(b, sizeof(b), "Step goal %u", (unsigned)ui->stepGoal);
    ui->showToast(b, UI_COLOR_GOOD);
}

static HomeColors homeColorsFor(uint8_t themeIndex)
{
    if (themeIndex >= UI_PALETTE_COUNT)
    {
        themeIndex = 0;
    }
    const UIPalette& p = UI_PALETTES[themeIndex];
    HomeColors c;
    c.bg = lv_color_hex(p.bg);
    c.card = lv_color_hex(p.card);
    c.text = lv_color_hex(p.text);
    c.dim = lv_color_hex(p.muted);
    c.a1 = lv_color_hex(p.tile[0]);
    c.a2 = lv_color_hex(p.tile[1]);
    c.a3 = lv_color_hex(p.tile[2]);
    c.a4 = lv_color_hex(p.tile[3]);
    return c;
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
        "EDITORIAL",
        "BENTO",
        "AURA",
        "REGULATOR",
        "SWISS POSTER",
        "LIQUID GLASS",
        "ORBIT RINGS",
        "TODAY CARDS",
        "STACKED TIME"
    };
    const char* descriptions[] =
    {
        "Cream page, big numerals",
        "Colorful tile grid",
        "Soft glowing orbs",
        "Emerald dial, sub-dials",
        "Black type, red accent",
        "Glowing rings on glass",
        "Rings for time and phone",
        "Colored status cards",
        "Two-tone stacked clock"
    };

    lv_obj_t* faceList = lv_obj_create(facePickerRoot);
    lv_obj_remove_style_all(faceList);
    lv_obj_set_pos(faceList, MARGIN, 61);
    lv_obj_set_size(faceList, CONTENT_WIDTH, 220);
    lv_obj_set_scroll_dir(faceList, LV_DIR_VER);
    lv_obj_set_scrollbar_mode(faceList, LV_SCROLLBAR_MODE_OFF);

    for (uint8_t face = 0; face < 9; ++face)
    {
        lv_obj_t* button = lv_button_create(faceList);
        const int32_t y = static_cast<int32_t>(face) * 36;
        lv_obj_set_pos(button, 0, y);
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
                homeFaces[face] = createFacePanel(root, face);
            }

            homeThemeIndex = uiThemeLoad();
            for (uint8_t kind = 0; kind < HOME_FACE_KINDS; ++kind)
            {
                lv_obj_t* panel = lv_obj_create(root);
                lv_obj_set_pos(panel, 0, 0);
                lv_obj_set_size(panel, DISPLAY_WIDTH, DISPLAY_HEIGHT);
                lv_obj_set_style_border_width(panel, 0, 0);
                lv_obj_set_style_radius(panel, 0, 0);
                lv_obj_set_style_pad_all(panel, 0, 0);
                lv_obj_add_flag(panel, LV_OBJ_FLAG_EVENT_BUBBLE);
                lv_obj_add_flag(panel, LV_OBJ_FLAG_HIDDEN);
                homeFaces[6 + kind] = panel;
                uiHomeBuildFace(panel, kind, homeColorsFor(homeThemeIndex));
            }

            lv_obj_t* brutalist = homeFaces[0];
            lv_obj_set_style_bg_color(brutalist, lv_color_hex(0x050608), 0);
            lv_obj_set_style_bg_opa(brutalist, LV_OPA_COVER, 0);
            createWatchFaceFrame(brutalist, lv_color_hex(0x858A91));
            faceClock[0] = createLabel(brutalist, "--:--", 5, 112, 230, 78, font_h1, lv_color_hex(0xD9DDE1), LV_TEXT_ALIGN_CENTER);
            createCard(brutalist, 36, 115, 2, 55, lv_color_hex(0x777D84), 0);
            createCard(brutalist, 76, 176, 34, 2, lv_color_hex(0x777D84), 0);
            createCard(brutalist, 157, 119, 2, 44, lv_color_hex(0x777D84), 0);
            createCard(brutalist, 186, 166, 22, 2, lv_color_hex(0x777D84), 0);
            faceHeart[0] = createLabel(brutalist, "-- BPM", 24, 211, 56, 20, font_body, UI_COLOR_TEXT, LV_TEXT_ALIGN_CENTER);
            faceBattery[0] = createLabel(brutalist, "--%", 84, 211, 44, 20, font_body, UI_COLOR_TEXT, LV_TEXT_ALIGN_CENTER);
            faceDate[0] = createLabel(brutalist, "--", 132, 211, 84, 20, font_body, UI_COLOR_MUTED, LV_TEXT_ALIGN_CENTER);

            lv_obj_t* dotMatrix = homeFaces[1];
            lv_obj_set_style_bg_color(dotMatrix, lv_color_hex(0x050505), 0);
            lv_obj_set_style_bg_opa(dotMatrix, LV_OPA_COVER, 0);
            createWatchFaceFrame(dotMatrix, lv_color_hex(0x5A4B32));
            const uint8_t heartRows[] = {0x36, 0x7F, 0x7F, 0x3E, 0x1C, 0x08};
            for (uint8_t row = 0; row < 6; ++row)
            {
                for (uint8_t column = 0; column < 7; ++column)
                {
                    if ((heartRows[row] & (1U << (6 - column))) != 0)
                    {
                        createCard(dotMatrix, 92 + column * 8, 84 + row * 6, 4, 4, UI_COLOR_AMBER, LV_RADIUS_CIRCLE);
                    }
                }
            }
            faceClock[1] = createLabel(dotMatrix, "--:--", 6, 127, 228, 72, font_h1, UI_COLOR_AMBER, LV_TEXT_ALIGN_CENTER);
            faceHeart[1] = createLabel(dotMatrix, "-- BPM", 62, 201, 116, 23, font_h4, UI_COLOR_AMBER, LV_TEXT_ALIGN_CENTER);
            faceSteps[1] = createLabel(dotMatrix, "---- STEPS", 42, 232, 156, 22, font_h5, UI_COLOR_AMBER, LV_TEXT_ALIGN_CENTER);

            lv_obj_t* topo = homeFaces[2];
            lv_obj_set_style_bg_color(topo, lv_color_hex(0x061016), 0);
            lv_obj_set_style_bg_opa(topo, LV_OPA_COVER, 0);
            createWatchFaceFrame(topo, UI_COLOR_TOPO);
            const int32_t topoSizes[] = {208, 178, 146, 112, 76};
            for (uint8_t ring = 0; ring < 5; ++ring)
            {
                lv_obj_t* contour = createCard(
                    topo,
                    (DISPLAY_WIDTH - topoSizes[ring]) / 2,
                    58 + (208 - topoSizes[ring]) / 2,
                    topoSizes[ring],
                    topoSizes[ring],
                    UI_COLOR_BACKGROUND,
                    LV_RADIUS_CIRCLE
                );
                lv_obj_set_style_bg_opa(contour, LV_OPA_TRANSP, 0);
                lv_obj_set_style_border_color(contour, lv_color_hex(0x163644), 0);
                lv_obj_set_style_border_width(contour, 1, 0);
            }
            createLabel(topo, "ELEV 214M", 52, 83, 136, 17, font_body, UI_COLOR_TOPO, LV_TEXT_ALIGN_CENTER);
            faceClock[2] = createLabel(topo, "--:--", 9, 126, 222, 78, font_h1, UI_COLOR_TEXT, LV_TEXT_ALIGN_CENTER);
            faceWeather[2] = createLabel(topo, "NW 12°", 38, 207, 84, 22, font_body, UI_COLOR_TEXT, LV_TEXT_ALIGN_CENTER);
            faceBattery[2] = createLabel(topo, "82%", 126, 207, 76, 22, font_body, UI_COLOR_TEXT, LV_TEXT_ALIGN_CENTER);
            faceSteps[2] = createLabel(topo, "---- STEPS", 42, 232, 156, 18, font_body, UI_COLOR_TEXT, LV_TEXT_ALIGN_CENTER);
            faceDate[2] = createLabel(topo, "--", 64, 250, 112, 16, font_body, UI_COLOR_MUTED, LV_TEXT_ALIGN_CENTER);

            lv_obj_t* glass = homeFaces[3];
            lv_obj_set_style_bg_color(glass, lv_color_hex(0x65759A), 0);
            lv_obj_set_style_bg_grad_color(glass, lv_color_hex(0xA1A9C1), 0);
            lv_obj_set_style_bg_grad_dir(glass, LV_GRAD_DIR_VER, 0);
            lv_obj_set_style_bg_opa(glass, LV_OPA_COVER, 0);
            createWatchFaceFrame(glass, lv_color_hex(0xC7D5F2));
            lv_obj_t* glassCard = createCard(glass, 32, 88, 176, 144, lv_color_hex(0xE3EAFB), 48);
            lv_obj_set_style_bg_opa(glassCard, 56, 0);
            lv_obj_set_style_border_color(glassCard, lv_color_hex(0xE7EEFF), 0);
            lv_obj_set_style_border_opa(glassCard, 110, 0);
            lv_obj_set_style_border_width(glassCard, 1, 0);
            faceClock[3] = createLabel(glass, "--:--", 5, 118, 230, 80, font_h1, lv_color_hex(0xF4F6FF), LV_TEXT_ALIGN_CENTER);
            faceHeart[3] = createMetricPill(glass, 52, 194, 136, "-- BPM", UI_COLOR_TEXT, lv_color_hex(0x66799C));
            faceWeather[3] = createMetricPill(glass, 43, 229, 154, "--°", UI_COLOR_TEXT, lv_color_hex(0x66799C));
            faceDate[3] = createLabel(glass, "--", 64, 252, 112, 16, font_body, lv_color_hex(0xE7EDFC), LV_TEXT_ALIGN_CENTER);

            lv_obj_t* circuit = homeFaces[4];
            lv_obj_set_style_bg_color(circuit, lv_color_hex(0x030813), 0);
            lv_obj_set_style_bg_opa(circuit, LV_OPA_COVER, 0);
            createWatchFaceFrame(circuit, lv_color_hex(0x293E66));
            constexpr int32_t FACE_CENTER = DISPLAY_WIDTH / 2;
            constexpr int32_t FACE_RADIUS = DISPLAY_WIDTH / 2;
            for (int32_t gridX = 48; gridX <= 192; gridX += 18)
            {
                const int32_t offsetX = gridX - FACE_CENTER;
                const int32_t halfHeight = static_cast<int32_t>(
                    std::sqrt(FACE_RADIUS * FACE_RADIUS - offsetX * offsetX)
                ) - 2;
                createCard(
                    circuit,
                    gridX,
                    FACE_CIRCLE_TOP + FACE_CENTER - halfHeight,
                    1,
                    halfHeight * 2,
                    lv_color_hex(0x101D35),
                    0
                );
            }
            for (int32_t gridY = 64; gridY <= 256; gridY += 18)
            {
                const int32_t offsetY = gridY - FACE_CIRCLE_TOP - FACE_CENTER;
                const int32_t halfWidth = static_cast<int32_t>(
                    std::sqrt(FACE_RADIUS * FACE_RADIUS - offsetY * offsetY)
                ) - 2;
                createCard(
                    circuit,
                    FACE_CENTER - halfWidth,
                    gridY,
                    halfWidth * 2,
                    1,
                    lv_color_hex(0x101D35),
                    0
                );
            }
            createCard(circuit, 44, 96, 46, 2, UI_COLOR_CIRCUIT, 0);
            createCard(circuit, 44, 96, 2, 24, UI_COLOR_CIRCUIT, 0);
            createCard(circuit, 90, 96, 2, 16, UI_COLOR_CIRCUIT, 0);
            createCard(circuit, 150, 213, 42, 2, UI_COLOR_CIRCUIT, 0);
            createCard(circuit, 190, 190, 2, 25, UI_COLOR_CIRCUIT, 0);
            createLabel(circuit, "PWR 3.3V", 78, 83, 84, 18, font_body, UI_COLOR_TEXT, LV_TEXT_ALIGN_CENTER);
            createLabel(circuit, "CLK 32kHz", 78, 101, 84, 18, font_body, UI_COLOR_TEXT, LV_TEXT_ALIGN_CENTER);
            faceClock[4] = createLabel(circuit, "--:--", 8, 132, 224, 66, font_h1, lv_color_hex(0xE6E9F0), LV_TEXT_ALIGN_CENTER);
            faceHeart[4] = createMetricPill(circuit, 55, 207, 130, "-- BPM", UI_COLOR_TEXT, lv_color_hex(0x17253C));
            createLabel(circuit, "SIGNAL OK", 55, 238, 130, 18, font_body, UI_COLOR_GOOD, LV_TEXT_ALIGN_CENTER);
            faceDate[4] = createLabel(circuit, "--", 64, 254, 112, 16, font_body, UI_COLOR_TEXT, LV_TEXT_ALIGN_CENTER);

            lv_obj_t* prism = homeFaces[5];
            lv_obj_set_style_bg_color(prism, lv_color_hex(0x030309), 0);
            lv_obj_set_style_bg_opa(prism, LV_OPA_COVER, 0);
            createWatchFaceFrame(prism, lv_color_hex(0x25233B));
            lv_obj_t* prismBlue = createLabel(prism, "--:--", 9, 125, 224, 76, font_h1, lv_color_hex(0x5F8FFF), LV_TEXT_ALIGN_CENTER);
            lv_obj_set_pos(prismBlue, 11, 123);
            lv_obj_t* prismPink = createLabel(prism, "--:--", 9, 125, 224, 76, font_h1, lv_color_hex(0xFF86D2), LV_TEXT_ALIGN_CENTER);
            lv_obj_set_pos(prismPink, 7, 127);
            faceClock[5] = createLabel(prism, "--:--", 9, 125, 224, 76, font_h1, lv_color_hex(0xDDE8FF), LV_TEXT_ALIGN_CENTER);
            faceHeart[5] = createMetricPill(prism, 56, 197, 128, "-- BPM", UI_COLOR_TEXT, lv_color_hex(0x454267));
            faceOxygen[5] = createLabel(prism, "--% O2", 66, 227, 108, 20, font_h5, UI_COLOR_TEXT, LV_TEXT_ALIGN_CENTER);
            faceDate[5] = createLabel(prism, "UV 3  MODERATE", 48, 245, 144, 16, font_body, UI_COLOR_MUTED, LV_TEXT_ALIGN_CENTER);

            break;
        }
    }

    return root;
}

void UIManager::showScreen(Screen screen, bool fade)
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

    if (fade)
    {
        lv_screen_load_anim(
            screenRoots[screen],
            LV_SCREEN_LOAD_ANIM_FADE_ON,
            200,
            0,
            false
        );
    }
    else
    {
        lv_screen_load(screenRoots[screen]);
    }
}

void UIManager::rebuildClassicFaces()
{
    for (uint8_t face = 0; face < 6; ++face)
    {
        lv_obj_t* panel = homeFaces[face];
        if (panel == nullptr)
        {
            continue;
        }
        faceClock[face] = nullptr;
        faceDate[face] = nullptr;
        faceHeart[face] = nullptr;
        faceSteps[face] = nullptr;
        faceBattery[face] = nullptr;
        faceWeather[face] = nullptr;
        faceOxygen[face] = nullptr;
        lv_obj_clean(panel);
        lv_obj_set_pos(panel, 0, 0);
        lv_obj_set_size(panel, DISPLAY_WIDTH, DISPLAY_HEIGHT);
        lv_obj_set_style_radius(panel, 0, 0);
        uiHomeBuildFace(panel, HOME_FACE_BRUTALIST + face, homeColorsFor(homeThemeIndex));
    }
}

void UIManager::applyHomeFace()
{
    for (uint8_t face = 0; face < 9; ++face)
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
    if (selection == nullptr || selection->manager == nullptr || selection->face >= 9)
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

    ui->showScreen(ui->facePickerReturnScreen, true);
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
    if (direction == LV_DIR_TOP)
    {
        ui->apps.show();
        return;
    }
    if (direction == LV_DIR_LEFT)
    {
        ui->overlays.showHistory();
    }
    else if (direction == LV_DIR_RIGHT)
    {
        ui->apps.showMusic();
    }
    else if (direction == LV_DIR_BOTTOM)
    {
        ui->sysui.showSettings();
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

    overlays.poll();
    apps.poll();
    sysui.poll();
    uiUtilsPoll();

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
    const uint16_t heartRate = state.heartRate;
    const uint16_t steps = state.steps;
    const uint8_t bloodOxygen = state.bloodOxygen;

    if (state.phoneConnectionEventId != lastPhoneConnectionEventId)
    {
        lastPhoneConnectionEventId = state.phoneConnectionEventId;
        showConnectionToast(state.phoneConnected);
    }

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
            if (heartRate > 0)
            {
                lv_label_set_text_fmt(faceHeart[face], "%u BPM", static_cast<unsigned>(heartRate));
            }
            else
            {
                lv_label_set_text(faceHeart[face], "-- BPM");
            }
        }
        if (faceSteps[face] != nullptr)
        {
            if (steps > 0)
            {
                lv_label_set_text_fmt(faceSteps[face], "%u STEPS", static_cast<unsigned>(steps));
            }
            else
            {
                lv_label_set_text(faceSteps[face], "---- STEPS");
            }
        }
    }

    if (faceBattery[0] != nullptr)
    {
        if (state.phoneConnected)
        {
            lv_label_set_text_fmt(
                faceBattery[0],
                "%u%%",
                static_cast<unsigned>(state.phoneBattery)
            );
        }
        else
        {
            lv_label_set_text(faceBattery[0], "--%");
        }
    }


    if (faceWeather[2] != nullptr)
    {
        if (state.weatherAvailable)
        {
            lv_label_set_text_fmt(faceWeather[2], "%d°", state.weatherTemperature);
        }
        else
        {
            lv_label_set_text(faceWeather[2], "--°");
        }
    }
    if (faceWeather[3] != nullptr)
    {
        if (state.weatherAvailable)
        {
            lv_label_set_text_fmt(faceWeather[3], "%d°C", state.weatherTemperature);
        }
        else
        {
            lv_label_set_text(faceWeather[3], "--°C");
        }
    }
    if (faceBattery[2] != nullptr)
    {
        if (state.phoneConnected)
        {
            lv_label_set_text_fmt(faceBattery[2], "%u%%", static_cast<unsigned>(state.phoneBattery));
        }
        else
        {
            lv_label_set_text(faceBattery[2], "--%");
        }
    }

    if (faceOxygen[5] != nullptr)
    {
        if (bloodOxygen > 0)
        {
            lv_label_set_text_fmt(faceOxygen[5], "%u%% O2", static_cast<unsigned>(bloodOxygen));
        }
        else
        {
            lv_label_set_text(faceOxygen[5], "--% O2");
        }
    }

    saveTimezone(state.clockSynced);
    {
        HomeData home;
        int nowMinutes = -1;
        time_t homeNow;
        if (state.clockSynced && time(&homeNow) != static_cast<time_t>(-1))
        {
            struct tm homeInfo;
            if (localtime_r(&homeNow, &homeInfo) != nullptr)
            {
                uint8_t hour = static_cast<uint8_t>(homeInfo.tm_hour);
                nowMinutes = homeInfo.tm_hour * 60 + homeInfo.tm_min;
                if (!state.is24Hour)
                {
                    hour = (hour % 12 == 0) ? 12 : (hour % 12);
                }
                home.timeValid = true;
                home.hour = hour;
                home.minute = static_cast<uint8_t>(homeInfo.tm_min);
                home.second = static_cast<uint8_t>(homeInfo.tm_sec);
                home.weekday = static_cast<uint8_t>(homeInfo.tm_wday);
                home.day = static_cast<uint8_t>(homeInfo.tm_mday);
                home.month = static_cast<uint8_t>(homeInfo.tm_mon + 1);
            }
        }
        if (state.phoneConnected)
        {
            home.battery = static_cast<int8_t>(state.phoneBattery > 100 ? 100 : state.phoneBattery);
        }
        if (state.weatherAvailable)
        {
            home.hasTemp = true;
            home.tempC = static_cast<int8_t>(state.weatherTemperature);
        }
        strncpy(home.weather, state.weatherCity.c_str(), sizeof(home.weather) - 1);

        int best = -1;
        int bestWait = 24 * 60 + 1;
        for (uint8_t i = 0; i < PULSEON_MAX_ALARMS; ++i)
        {
            const PulseonAlarm& alarm = state.alarms[i];
            if (!alarm.enabled)
            {
                continue;
            }
            const int minutes = alarm.hour * 60 + alarm.minute;
            const int wait = (nowMinutes >= 0) ? (minutes - nowMinutes + 1440) % 1440 : minutes;
            if (wait < bestWait)
            {
                bestWait = wait;
                best = i;
            }
        }
        if (best >= 0)
        {
            snprintf(home.nextAlarm, sizeof(home.nextAlarm), "%02u:%02u",
                     static_cast<unsigned>(state.alarms[best].hour),
                     static_cast<unsigned>(state.alarms[best].minute));
        }
        home.notifCount = state.notificationStored;
        home.heartRate = heartRate;
        home.steps = steps;
        home.oxygen = bloodOxygen;
        home.connected = state.phoneConnected;
        home.charging = state.phoneCharging;
        home.stepGoal = stepGoal;

        const uint32_t pollNow = millis();
        if (pollNow - lastThemePollMs >= 1000)
        {
            lastThemePollMs = pollNow;
            const uint8_t themeNow = uiThemeLoad();
            if (themeNow != homeThemeIndex)
            {
                homeThemeIndex = themeNow;
                uiHomeRecolor(homeColorsFor(homeThemeIndex));
            }
        }
        uiHomeUpdate(home);
    }

}

void UIManager::setBrightnessHandler(UISystem::BrightnessHandler handler)
{
    sysui.setBrightnessHandler(handler);
}
