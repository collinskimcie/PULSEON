#include "UIApps.h"

#include <stdio.h>
#include <time.h>

#include "PULSEON_WATCH_UI.h"
#include "UIOverlays.h"
#include "UIText.h"
#include "UITheme.h"
#include "UIIcons.h"
#include "../chronos/ChronosManager.h"

namespace
{
lv_color_t OV_BG, OV_BG2, OV_CARD, OV_CARD_ALT, OV_TEXT, OV_MUTED, OV_ACCENT, OV_ACCENT_DARK, OV_GOOD;
lv_color_t OV_TILE[8];
uint8_t themeIndex = 0;

void loadPalette(const UIPalette& p)
{
    OV_BG = lv_color_hex(p.bg);
    OV_BG2 = lv_color_hex(p.bg2);
    OV_CARD = lv_color_hex(p.card);
    OV_CARD_ALT = lv_color_hex(p.cardAlt);
    OV_TEXT = lv_color_hex(p.text);
    OV_MUTED = lv_color_hex(p.muted);
    OV_ACCENT = lv_color_hex(p.accent);
    OV_ACCENT_DARK = lv_color_hex(p.accentDark);
    OV_GOOD = lv_color_hex(p.good);
    for (uint8_t i = 0; i < 8; ++i)
    {
        OV_TILE[i] = lv_color_hex(p.tile[i]);
    }
}

// Maps every color of the old palette to the new one on all existing objects.
struct Remap
{
    uint32_t bgFrom[12];
    uint32_t bgTo[12];
    uint8_t bgCount = 0;
    uint32_t txFrom[4];
    uint32_t txTo[4];
    uint32_t grFrom = 0;
    uint32_t grTo = 0;
};

void addBg(Remap& m, uint32_t a, uint32_t b)
{
    if (a != b && m.bgCount < 12)
    {
        m.bgFrom[m.bgCount] = a;
        m.bgTo[m.bgCount] = b;
        ++m.bgCount;
    }
}

Remap makeRemap(const UIPalette& from, const UIPalette& to)
{
    Remap m;
    addBg(m, from.bg, to.bg);
    addBg(m, from.card, to.card);
    addBg(m, from.cardAlt, to.cardAlt);
    addBg(m, from.accentDark, to.accentDark);
    addBg(m, from.accent, to.accent);
    for (uint8_t i = 1; i < 8; ++i)
    {
        addBg(m, from.tile[i], to.tile[i]);
    }
    m.txFrom[0] = from.text;   m.txTo[0] = to.text;
    m.txFrom[1] = from.muted;  m.txTo[1] = to.muted;
    m.txFrom[2] = from.accent; m.txTo[2] = to.accent;
    m.txFrom[3] = from.good;   m.txTo[3] = to.good;
    m.grFrom = from.bg2;
    m.grTo = to.bg2;
    return m;
}

uint32_t rgb(lv_color_t c)
{
    return lv_color_to_u32(c) & 0xFFFFFF;
}

void recolor(lv_obj_t* obj, const Remap& m)
{
    const uint32_t bg = rgb(lv_obj_get_style_bg_color(obj, LV_PART_MAIN));
    for (uint8_t i = 0; i < m.bgCount; ++i)
    {
        if (bg == m.bgFrom[i])
        {
            lv_obj_set_style_bg_color(obj, lv_color_hex(m.bgTo[i]), 0);
            break;
        }
    }

    const uint32_t tx = rgb(lv_obj_get_style_text_color(obj, LV_PART_MAIN));
    for (uint8_t i = 0; i < 4; ++i)
    {
        if (tx == m.txFrom[i])
        {
            lv_obj_set_style_text_color(obj, lv_color_hex(m.txTo[i]), 0);
            break;
        }
    }

    if (rgb(lv_obj_get_style_bg_grad_color(obj, LV_PART_MAIN)) == m.grFrom)
    {
        lv_obj_set_style_bg_grad_color(obj, lv_color_hex(m.grTo), 0);
    }

    const uint32_t count = lv_obj_get_child_count(obj);
    for (uint32_t i = 0; i < count; ++i)
    {
        recolor(lv_obj_get_child(obj, i), m);
    }
}

lv_obj_t* makeLabel(
    lv_obj_t* parent, const char* text, int32_t x, int32_t y, int32_t w, int32_t h,
    const lv_font_t* font, lv_color_t color,
    lv_text_align_t align = LV_TEXT_ALIGN_LEFT,
    lv_label_long_mode_t mode = LV_LABEL_LONG_DOT)
{
    lv_obj_t* label = lv_label_create(parent);
    lv_label_set_long_mode(label, mode);
    lv_label_set_text(label, text);
    lv_obj_set_pos(label, x, y);
    lv_obj_set_size(label, w, h);
    lv_obj_set_style_text_font(label, font, 0);
    lv_obj_set_style_text_color(label, color, 0);
    lv_obj_set_style_text_align(label, align, 0);
    lv_obj_add_flag(label, LV_OBJ_FLAG_EVENT_BUBBLE);
    return label;
}

lv_obj_t* makePanel(
    lv_obj_t* parent, int32_t x, int32_t y, int32_t w, int32_t h,
    lv_color_t color, int32_t radius)
{
    lv_obj_t* panel = lv_obj_create(parent);
    lv_obj_set_pos(panel, x, y);
    lv_obj_set_size(panel, w, h);
    lv_obj_set_style_bg_color(panel, color, 0);
    lv_obj_set_style_bg_opa(panel, LV_OPA_COVER, 0);
    lv_obj_set_style_border_width(panel, 0, 0);
    lv_obj_set_style_radius(panel, radius, 0);
    lv_obj_set_style_pad_all(panel, 0, 0);
    lv_obj_clear_flag(panel, LV_OBJ_FLAG_SCROLLABLE);
    return panel;
}

lv_obj_t* makeList(lv_obj_t* parent, int32_t x, int32_t y, int32_t w, int32_t h)
{
    lv_obj_t* list = lv_obj_create(parent);
    lv_obj_set_pos(list, x, y);
    lv_obj_set_size(list, w, h);
    lv_obj_set_style_bg_opa(list, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_width(list, 0, 0);
    lv_obj_set_style_pad_all(list, 0, 0);
    lv_obj_set_style_pad_row(list, 6, 0);
    lv_obj_set_flex_flow(list, LV_FLEX_FLOW_COLUMN);
    return list;
}

constexpr int32_t NAV_ICON_PX = 96;      // 48x48 icon drawn at 2x
constexpr bool NAV_ICON_INVERT = false;  // set true if the icon looks like a negative

void weekdayName(uint8_t offset, bool clockSynced, char* buf, size_t n)
{
    static const char* const NAMES[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    time_t t;
    struct tm info;
    if (clockSynced && time(&t) != static_cast<time_t>(-1) && localtime_r(&t, &info) != nullptr)
    {
        snprintf(buf, n, "%s", NAMES[(info.tm_wday + offset) % 7]);
    }
    else
    {
        snprintf(buf, n, "In %u days", static_cast<unsigned>(offset));
    }
}

lv_obj_t* decorateTile(lv_obj_t* button, lv_obj_t* label, uint8_t iconId, lv_color_t accent)
{
    lv_obj_set_style_radius(button, 18, 0);
    lv_obj_set_style_bg_opa(button, LV_OPA_70, LV_STATE_PRESSED);
    lv_obj_align(label, LV_ALIGN_BOTTOM_LEFT, 12, -8);

    lv_obj_t* img = lv_image_create(button);
    lv_image_set_src(img, uiIcon(iconId));
    lv_obj_set_style_image_recolor(img, accent, 0);
    lv_obj_set_style_image_recolor_opa(img, LV_OPA_COVER, 0);
    lv_obj_align(img, LV_ALIGN_TOP_LEFT, 10, 5);
    lv_obj_clear_flag(img, LV_OBJ_FLAG_CLICKABLE);
    return img;
}

void formatTime(uint8_t hour, uint8_t minute, bool is24, char* buf, size_t n)
{
    if (is24)
    {
        snprintf(buf, n, "%02u:%02u", static_cast<unsigned>(hour), static_cast<unsigned>(minute));
        return;
    }
    unsigned h12 = hour % 12;
    if (h12 == 0) h12 = 12;
    snprintf(buf, n, "%u:%02u %s", h12, static_cast<unsigned>(minute), hour >= 12 ? "PM" : "AM");
}
} // namespace

// ------------------------------------------------------------------
// Setup
// ------------------------------------------------------------------

void UIApps::begin(AppStateManager* state, ChronosManager* chronosManager, UIOverlays* overlaysPtr)
{
    appState = state;
    chronos = chronosManager;
    overlays = overlaysPtr;

    themeIndex = uiThemeLoad();
    loadPalette(UI_PALETTES[themeIndex]);

    for (uint8_t i = 0; i < ACT_COUNT; ++i)
    {
        actions[i].self = this;
        actions[i].id = i;
    }

    buildApps();
    buildMusic();
    buildWeather();
    buildAlarms();
    buildFind();
    buildCamera();
    buildNav();
}

lv_obj_t* UIApps::makeRoot(Page page, const char* title)
{
    lv_obj_t* root = makePanel(lv_layer_top(), 0, 0, 240, 320, OV_BG, 0);
    lv_obj_add_flag(root, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_bg_grad_color(root, OV_BG2, 0);
    lv_obj_set_style_bg_grad_dir(root, LV_GRAD_DIR_VER, 0);
    makeLabel(root, title, 16, 10, 208, 28, font_h4, OV_TEXT);
    lv_obj_t* bar = makePanel(root, 16, 38, 36, 3, OV_ACCENT, 2);
    lv_obj_clear_flag(bar, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_flag(root, LV_OBJ_FLAG_HIDDEN);
    roots[page] = root;
    return root;
}

lv_obj_t* UIApps::addAction(
    lv_obj_t* parent, const char* text, int32_t x, int32_t y, int32_t w, int32_t h,
    lv_color_t bg, lv_color_t fg, Act act)
{
    lv_obj_t* button = lv_button_create(parent);
    lv_obj_set_pos(button, x, y);
    lv_obj_set_size(button, w, h);
    lv_obj_set_style_bg_color(button, bg, 0);
    lv_obj_set_style_bg_opa(button, LV_OPA_COVER, 0);
    lv_obj_set_style_border_width(button, 0, 0);
    lv_obj_set_style_shadow_width(button, 0, 0);
    lv_obj_set_style_radius(button, h / 2 > 22 ? 22 : h / 2, 0);
    lv_obj_set_style_bg_opa(button, LV_OPA_70, LV_STATE_PRESSED);
    lv_obj_add_event_cb(button, actionClicked, LV_EVENT_CLICKED, &actions[act]);

    lv_obj_t* label = lv_label_create(button);
    lv_label_set_text(label, text);
    lv_obj_set_style_text_font(label, font_h5, 0);
    lv_obj_set_style_text_color(label, fg, 0);
    lv_obj_center(label);
    return button;
}

void UIApps::buildApps()
{
    lv_obj_t* root = makeRoot(PAGE_APPS, "APPS");

    struct Tile { const char* text; Act act; };
    const Tile tiles[8] = {
        {"Music", ACT_OPEN_MUSIC},     {"Weather", ACT_OPEN_WEATHER},
        {"Alarms", ACT_OPEN_ALARMS},   {"Find phone", ACT_OPEN_FIND},
        {"Camera", ACT_OPEN_CAMERA},   {"Alerts", ACT_OPEN_ALERTS},
        {"Navigate", ACT_OPEN_NAV},
        {"Theme", ACT_THEME},
    };

    tileArea = lv_obj_create(root);
    lv_obj_set_pos(tileArea, 0, 44);
    lv_obj_set_size(tileArea, 240, 216);
    lv_obj_set_style_bg_opa(tileArea, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_width(tileArea, 0, 0);
    lv_obj_set_style_radius(tileArea, 0, 0);
    lv_obj_set_style_pad_all(tileArea, 0, 0);
    lv_obj_set_scroll_dir(tileArea, LV_DIR_VER);

    for (uint8_t i = 0; i < 8; ++i)
    {
        const int32_t x = 12 + (i % 2) * 112;
        const int32_t y = 4 + (i / 2) * 72;
        lv_obj_t* tileButton = addAction(tileArea, tiles[i].text, x, y, 104, 62, OV_CARD, OV_TEXT, tiles[i].act);
        lv_obj_t* tileImg = decorateTile(tileButton, lv_obj_get_child(tileButton, 0),
                                         uiIconForName(tiles[i].text), OV_TILE[i]);
        if (tileIconCount < kMaxTileIcons)
        {
            tileIcons[tileIconCount] = tileImg;
            tileIconColor[tileIconCount++] = i;
        }
    }
    tileCount = 8;

    addAction(root, "Close", 12, 266, 216, 50, OV_ACCENT_DARK, OV_ACCENT, ACT_CLOSE);
}

void UIApps::buildMusic()
{
    lv_obj_t* root = makeRoot(PAGE_MUSIC, "MUSIC");

    addAction(root, "Prev", 8, 60, 60, 48, OV_CARD, OV_TEXT, ACT_MUSIC_PREV);
    addAction(root, "Play/Pause", 76, 60, 88, 48, OV_ACCENT_DARK, OV_ACCENT, ACT_MUSIC_TOGGLE);
    addAction(root, "Next", 172, 60, 60, 48, OV_CARD, OV_TEXT, ACT_MUSIC_NEXT);

    addAction(root, "Vol -", 8, 124, 68, 44, OV_CARD, OV_TEXT, ACT_VOL_DOWN);
    addAction(root, "Mute", 86, 124, 68, 44, OV_CARD, OV_TEXT, ACT_VOL_MUTE);
    addAction(root, "Vol +", 164, 124, 68, 44, OV_CARD, OV_TEXT, ACT_VOL_UP);

    makeLabel(root, "Controls the music player on your phone", 16, 190, 208, 44,
              font_body, OV_MUTED, LV_TEXT_ALIGN_CENTER, LV_LABEL_LONG_WRAP);

    addAction(root, "Back", 12, 266, 216, 50, OV_CARD_ALT, OV_TEXT, ACT_BACK);
}

void UIApps::buildWeather()
{
    lv_obj_t* root = makeRoot(PAGE_WEATHER, "WEATHER");

    weatherCity = makeLabel(root, "", 16, 40, 208, 20, font_body, OV_MUTED, LV_TEXT_ALIGN_CENTER);
    weatherTemp = makeLabel(root, "--", 16, 60, 208, 56, font_h2, OV_ACCENT, LV_TEXT_ALIGN_CENTER);
    weatherRange = makeLabel(root, "", 16, 118, 208, 20, font_body, OV_MUTED, LV_TEXT_ALIGN_CENTER);
    weatherList = makeList(root, 8, 146, 224, 116);

    addAction(root, "Back", 12, 266, 216, 50, OV_CARD_ALT, OV_TEXT, ACT_BACK);
}

void UIApps::buildAlarms()
{
    lv_obj_t* root = makeRoot(PAGE_ALARMS, "ALARMS");
    alarmList = makeList(root, 8, 44, 224, 216);
    addAction(root, "Back", 12, 266, 216, 50, OV_CARD_ALT, OV_TEXT, ACT_BACK);
}

void UIApps::buildFind()
{
    lv_obj_t* root = makeRoot(PAGE_FIND, "FIND PHONE");

    findStatus = makeLabel(root, "", 16, 70, 208, 40, font_body, OV_MUTED,
                           LV_TEXT_ALIGN_CENTER, LV_LABEL_LONG_WRAP);
    lv_obj_t* button = addAction(root, "Find phone", 40, 130, 160, 56,
                                 OV_ACCENT_DARK, OV_ACCENT, ACT_FIND_TOGGLE);
    findButtonLabel = lv_obj_get_child(button, 0);

    addAction(root, "Back", 12, 266, 216, 50, OV_CARD_ALT, OV_TEXT, ACT_BACK);
}

void UIApps::buildCamera()
{
    lv_obj_t* root = makeRoot(PAGE_CAMERA, "CAMERA");

    cameraStatus = makeLabel(root, "", 16, 70, 208, 40, font_body, OV_MUTED,
                             LV_TEXT_ALIGN_CENTER, LV_LABEL_LONG_WRAP);
    addAction(root, "Take photo", 40, 130, 160, 56, OV_ACCENT_DARK, OV_ACCENT, ACT_CAMERA_SHOOT);

    addAction(root, "Back", 12, 266, 216, 50, OV_CARD_ALT, OV_TEXT, ACT_BACK);
}

// ------------------------------------------------------------------
// Navigation between pages
// ------------------------------------------------------------------

void UIApps::show()
{
    showPage(PAGE_APPS);
}

bool UIApps::isVisible() const
{
    return current != PAGE_NONE;
}

void UIApps::showPage(Page page)
{
    if (current == PAGE_FIND && page != PAGE_FIND)
    {
        stopFinding();
    }

    for (uint8_t i = PAGE_APPS; i < PAGE_COUNT; ++i)
    {
        if (roots[i] != nullptr)
        {
            lv_obj_add_flag(roots[i], LV_OBJ_FLAG_HIDDEN);
        }
    }

    current = page;
    if (page == PAGE_NONE || roots[page] == nullptr)
    {
        current = PAGE_NONE;
        return;
    }

    if (page == PAGE_WEATHER) refreshWeather();
    if (page == PAGE_ALARMS) refreshAlarms();
    if (page == PAGE_NAV) refreshNav();
    if (page == PAGE_FIND || page == PAGE_CAMERA)
    {
        setFindLabel();
        refreshStatus();
    }

    lv_obj_clear_flag(roots[page], LV_OBJ_FLAG_HIDDEN);
    lv_obj_move_foreground(roots[page]);
}

void UIApps::actionClicked(lv_event_t* event)
{
    Action* action = static_cast<Action*>(lv_event_get_user_data(event));
    {
        lv_point_t p = {0, 0};
        lv_indev_t* indev = lv_indev_active();
        if (indev != nullptr)
        {
            lv_indev_get_point(indev, &p);
        }
        lv_area_t a = {0, 0, 0, 0};
        lv_obj_get_coords(lv_event_get_target_obj(event), &a);
        Serial.printf("[TOUCH] click act=%d at (%d,%d) button=(%d,%d)-(%d,%d)\n",
                      action != nullptr ? static_cast<int>(action->id) : -1,
                      static_cast<int>(p.x), static_cast<int>(p.y),
                      static_cast<int>(a.x1), static_cast<int>(a.y1),
                      static_cast<int>(a.x2), static_cast<int>(a.y2));
    }
    if (action != nullptr && action->self != nullptr)
    {
        action->self->handle(action->id);
    }
}

void UIApps::handle(uint8_t id)
{
    switch (static_cast<Act>(id))
    {
        case ACT_OPEN_MUSIC:   showPage(PAGE_MUSIC); break;
        case ACT_OPEN_WEATHER: showPage(PAGE_WEATHER); break;
        case ACT_OPEN_ALARMS:  showPage(PAGE_ALARMS); break;
        case ACT_OPEN_FIND:    showPage(PAGE_FIND); break;
        case ACT_OPEN_CAMERA:  showPage(PAGE_CAMERA); break;
        case ACT_OPEN_NAV:     showPage(PAGE_NAV); break;
        case ACT_THEME:        cycleTheme(); break;

        case ACT_OPEN_ALERTS:
            showPage(PAGE_NONE);
            if (overlays != nullptr)
            {
                overlays->showHistory();
            }
            break;

        case ACT_CLOSE: showPage(PAGE_NONE); break;
        case ACT_BACK:  showPage(PAGE_APPS); break;

        case ACT_MUSIC_PREV:   if (chronos) chronos->controlMusic(MUSIC_PREVIOUS); break;
        case ACT_MUSIC_TOGGLE: if (chronos) chronos->controlMusic(MUSIC_TOGGLE); break;
        case ACT_MUSIC_NEXT:   if (chronos) chronos->controlMusic(MUSIC_NEXT); break;
        case ACT_VOL_DOWN:     if (chronos) chronos->controlMusic(VOLUME_DOWN); break;
        case ACT_VOL_MUTE:     if (chronos) chronos->controlMusic(VOLUME_MUTE); break;
        case ACT_VOL_UP:       if (chronos) chronos->controlMusic(VOLUME_UP); break;

        case ACT_FIND_TOGGLE:
            if (chronos != nullptr && appState != nullptr && appState->getState().phoneConnected)
            {
                findingPhone = !findingPhone;
                chronos->findPhone(findingPhone);
                setFindLabel();
                refreshStatus();
            }
            break;

        case ACT_CAMERA_SHOOT:
            if (chronos != nullptr && appState != nullptr && appState->getState().cameraReady)
            {
                chronos->capturePhoto();
            }
            break;

        default:
            break;
    }
}

// ------------------------------------------------------------------
// Page content
// ------------------------------------------------------------------

void UIApps::refreshWeather()
{
    if (appState == nullptr || weatherList == nullptr)
    {
        return;
    }

    const PulseonAppState& st = appState->getState();
    lv_obj_clean(weatherList);

    if (!st.weatherAvailable)
    {
        lv_label_set_text(weatherCity, "");
        lv_label_set_text(weatherTemp, "--");
        lv_label_set_text(weatherRange, "Waiting for the phone");
        return;
    }

    char buf[48];

    lv_label_set_text(weatherCity, st.weatherCity.c_str());

    snprintf(buf, sizeof(buf), "%d", st.weatherTemperature);
    lv_label_set_text(weatherTemp, buf);

    snprintf(buf, sizeof(buf), "High %d   Low %d", st.weatherHigh, st.weatherLow);
    lv_label_set_text(weatherRange, buf);

    for (uint8_t i = 0; i < st.weatherDayCount; ++i)
    {
        const PulseonForecastDay& d = st.weatherDays[i];
        char name[16];
        if (i == 0)      snprintf(name, sizeof(name), "Today");
        else if (i == 1) snprintf(name, sizeof(name), "Tomorrow");
        else             snprintf(name, sizeof(name), "In %u days", static_cast<unsigned>(i));

        if (i >= 2)
        {
            weekdayName(i, st.clockSynced, name, sizeof(name));
        }
        lv_obj_t* row = makePanel(weatherList, 0, 0, 220, 30, OV_CARD, 12);
        makeLabel(row, name, 12, 5, 90, 20, font_body, OV_TEXT);
        snprintf(buf, sizeof(buf), "%d", d.temp);
        makeLabel(row, buf, 100, 5, 40, 20, font_h5, OV_ACCENT, LV_TEXT_ALIGN_RIGHT);
        snprintf(buf, sizeof(buf), "H%d  L%d", d.high, d.low);
        makeLabel(row, buf, 146, 5, 68, 20, font_body, OV_MUTED, LV_TEXT_ALIGN_RIGHT);
    }
}

void UIApps::refreshAlarms()
{
    if (appState == nullptr || alarmList == nullptr)
    {
        return;
    }

    const PulseonAppState& st = appState->getState();
    lv_obj_clean(alarmList);

    uint8_t shown = 0;
    for (uint8_t i = 0; i < PULSEON_MAX_ALARMS; ++i)
    {
        const PulseonAlarm& a = st.alarms[i];
        if (!a.enabled)
        {
            continue;
        }

        char buf[16];
        formatTime(a.hour, a.minute, st.is24Hour, buf, sizeof(buf));

        lv_obj_t* card = makePanel(alarmList, 0, 0, 224, 48, OV_CARD, 14);
        makeLabel(card, buf, 14, 10, 150, 28, font_h4, OV_TEXT);
        makeLabel(card, "ON", 168, 14, 46, 22, font_h5, OV_GOOD, LV_TEXT_ALIGN_RIGHT);
        ++shown;
    }

    if (shown == 0)
    {
        makeLabel(alarmList, "No alarms set", 0, 0, 224, 24, font_body, OV_MUTED, LV_TEXT_ALIGN_CENTER);
    }
}

void UIApps::refreshStatus()
{
    if (appState == nullptr)
    {
        return;
    }

    const PulseonAppState& st = appState->getState();

    if (current == PAGE_FIND)
    {
        if (!st.phoneConnected)
        {
            if (findingPhone)
            {
                findingPhone = false;
                setFindLabel();
            }
            lv_label_set_text(findStatus, "Phone not connected");
        }
        else
        {
            lv_label_set_text(findStatus, findingPhone ? "Your phone should be ringing"
                                                       : "Makes your phone ring");
        }
    }
    else if (current == PAGE_CAMERA)
    {
        if (!st.phoneConnected)
        {
            lv_label_set_text(cameraStatus, "Phone not connected");
        }
        else if (st.cameraReady)
        {
            lv_label_set_text(cameraStatus, "Camera ready");
        }
        else
        {
            lv_label_set_text(cameraStatus, "Open the camera in the Chronos app");
        }
    }
    else if (current == PAGE_NAV)
    {
        refreshNav();
    }
}

void UIApps::setFindLabel()
{
    if (findButtonLabel != nullptr)
    {
        lv_label_set_text(findButtonLabel, findingPhone ? "Stop" : "Find phone");
        lv_obj_center(findButtonLabel);
    }
}

void UIApps::stopFinding()
{
    if (findingPhone && chronos != nullptr)
    {
        chronos->findPhone(false);
    }
    findingPhone = false;
    setFindLabel();
}

void UIApps::poll()
{
    if (current != PAGE_FIND && current != PAGE_CAMERA && current != PAGE_NAV)
    {
        return;
    }

    const uint32_t now = millis();
    if (now - lastPollMs < 500)
    {
        return;
    }
    lastPollMs = now;
    refreshStatus();
}

void UIApps::showMusic()
{
    showPage(PAGE_MUSIC);
}

void UIApps::addTile(const char* text, TileHandler handler, void* user)
{
    if (tileArea == nullptr || handler == nullptr || extraTileCount >= kMaxExtraTiles)
    {
        return;
    }

    ExtraTile& tile = extraTiles[extraTileCount++];
    tile.self = this;
    tile.handler = handler;
    tile.user = user;

    const int32_t x = 12 + (tileCount % 2) * 112;
    const int32_t y = 4 + (tileCount / 2) * 72;

    lv_obj_t* button = lv_button_create(tileArea);
    lv_obj_set_pos(button, x, y);
    lv_obj_set_size(button, 104, 62);
    lv_obj_set_style_bg_color(button, OV_CARD, 0);
    lv_obj_set_style_bg_opa(button, LV_OPA_COVER, 0);
    lv_obj_set_style_border_width(button, 0, 0);
    lv_obj_set_style_shadow_width(button, 0, 0);
    lv_obj_set_style_radius(button, 22, 0);
    lv_obj_add_event_cb(button, extraTileClicked, LV_EVENT_CLICKED, &tile);

    lv_obj_t* label = lv_label_create(button);
    lv_label_set_text(label, text);
    lv_obj_set_style_text_font(label, font_h5, 0);
    lv_obj_set_style_text_color(label, OV_TEXT, 0);
    lv_obj_t* tileImg = decorateTile(button, label, uiIconForName(text), OV_TILE[tileCount % 8]);
    if (tileIconCount < kMaxTileIcons)
    {
        tileIcons[tileIconCount] = tileImg;
        tileIconColor[tileIconCount++] = tileCount % 8;
    }

    ++tileCount;
}

void UIApps::extraTileClicked(lv_event_t* event)
{
    ExtraTile* tile = static_cast<ExtraTile*>(lv_event_get_user_data(event));
    if (tile == nullptr || tile->self == nullptr || tile->handler == nullptr)
    {
        return;
    }
    tile->self->showPage(PAGE_NONE);
    tile->handler(tile->user);
}

void UIApps::buildNav()
{
    lv_obj_t* root = makeRoot(PAGE_NAV, "NAVIGATION");

    navPixels = static_cast<uint16_t*>(
        ps_malloc(static_cast<size_t>(NAV_ICON_PX) * NAV_ICON_PX * sizeof(uint16_t)));
    if (navPixels != nullptr)
    {
        navIcon = lv_canvas_create(root);
        lv_canvas_set_buffer(navIcon, navPixels, NAV_ICON_PX, NAV_ICON_PX, LV_COLOR_FORMAT_RGB565);
        lv_canvas_fill_bg(navIcon, OV_BG, LV_OPA_COVER);
        lv_obj_set_pos(navIcon, (240 - NAV_ICON_PX) / 2, 40);
        lv_obj_add_flag(navIcon, LV_OBJ_FLAG_HIDDEN);
    }

    navTitle = makeLabel(root, "", 12, 142, 216, 28, font_h4, OV_TEXT, LV_TEXT_ALIGN_CENTER);
    navDirections = makeLabel(root, "", 12, 172, 216, 40, font_body, OV_TEXT,
                              LV_TEXT_ALIGN_CENTER, LV_LABEL_LONG_WRAP);
    navInfo = makeLabel(root, "", 12, 218, 216, 20, font_body, OV_MUTED, LV_TEXT_ALIGN_CENTER);
    navEta = makeLabel(root, "", 12, 240, 216, 20, font_body, OV_MUTED, LV_TEXT_ALIGN_CENTER);

    addAction(root, "Back", 12, 266, 216, 50, OV_CARD_ALT, OV_TEXT, ACT_BACK);
}

void UIApps::refreshNav()
{
    if (appState == nullptr || navTitle == nullptr)
    {
        return;
    }

    const PulseonNavigation& nav = appState->getState().navigation;

    if (!nav.active)
    {
        lv_label_set_text(navTitle, "No navigation");
        lv_label_set_text(navDirections, "Start navigation in the Chronos app");
        lv_label_set_text(navInfo, "");
        lv_label_set_text(navEta, "");
        if (navIcon != nullptr)
        {
            lv_obj_add_flag(navIcon, LV_OBJ_FLAG_HIDDEN);
        }
        navShownIcon = false;
        return;
    }

    lv_label_set_text(navTitle, uiText(nav.title).c_str());
    lv_label_set_text(navDirections, uiText(nav.directions).c_str());

    char buf[64];
    snprintf(buf, sizeof(buf), "%s   %s", nav.distance.c_str(), nav.duration.c_str());
    lv_label_set_text(navInfo, buf);

    if (nav.speed.length() > 0)
    {
        snprintf(buf, sizeof(buf), "ETA %s   %s", nav.eta.c_str(), nav.speed.c_str());
    }
    else
    {
        snprintf(buf, sizeof(buf), "ETA %s", nav.eta.c_str());
    }
    lv_label_set_text(navEta, buf);

    if (navIcon == nullptr)
    {
        return;
    }

    if (!nav.hasIcon)
    {
        lv_obj_add_flag(navIcon, LV_OBJ_FLAG_HIDDEN);
        navShownIcon = false;
        return;
    }

    if (!navShownIcon || nav.iconCRC != navShownCrc)
    {
        // 48x48, 1 bit per pixel, 6 bytes per row, MSB first (assumed).
        lv_canvas_fill_bg(navIcon, OV_BG, LV_OPA_COVER);
        for (int y = 0; y < 48; ++y)
        {
            for (int x = 0; x < 48; ++x)
            {
                bool on = (nav.icon[y * 6 + (x >> 3)] >> (7 - (x & 7))) & 1;
                if (NAV_ICON_INVERT)
                {
                    on = !on;
                }
                if (on)
                {
                    for (int dy = 0; dy < 2; ++dy)
                    {
                        for (int dx = 0; dx < 2; ++dx)
                        {
                            lv_canvas_set_px(navIcon, x * 2 + dx, y * 2 + dy, OV_TEXT, LV_OPA_COVER);
                        }
                    }
                }
            }
        }
        navShownCrc = nav.iconCRC;
        navShownIcon = true;
    }
    lv_obj_clear_flag(navIcon, LV_OBJ_FLAG_HIDDEN);
}

void UIApps::cycleTheme()
{
    const UIPalette& from = UI_PALETTES[themeIndex];
    themeIndex = (themeIndex + 1) % UI_PALETTE_COUNT;
    const UIPalette& to = UI_PALETTES[themeIndex];

    const Remap m = makeRemap(from, to);
    for (uint8_t i = PAGE_APPS; i < PAGE_COUNT; ++i)
    {
        if (roots[i] != nullptr)
        {
            recolor(roots[i], m);
        }
    }
    loadPalette(to);
    for (uint8_t i = 0; i < tileIconCount; ++i)
    {
        lv_obj_set_style_image_recolor(tileIcons[i], OV_TILE[tileIconColor[i]], 0);
    }
    navShownIcon = false; // redraw the navigation icon in the new colors
    uiThemeSave(themeIndex);
    Serial.printf("[UI] Theme: %s\n", to.name);
}
