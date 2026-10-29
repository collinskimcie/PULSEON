#include "UISystem.h"
#include "UIUtils.h"

#include <Preferences.h>
#include <stdio.h>

#include "PULSEON_WATCH_UI.h"
#include "UIApps.h"
#include "UITheme.h"
#include "../chronos/ChronosManager.h"

namespace
{
constexpr const char* PREFS_NS = "pulseon_set";
constexpr uint8_t DIM_PERCENT = 4;
constexpr uint8_t TIMEOUT_COUNT = 5;
constexpr uint16_t TIMEOUT_SECONDS[TIMEOUT_COUNT] = {15, 30, 60, 300, 0};
const char* const TIMEOUT_NAMES[TIMEOUT_COUNT] = {"15 s", "30 s", "1 min", "5 min", "Never"};

const lv_color_t OV_BG = lv_color_hex(0x090A0E);
const lv_color_t OV_CARD = lv_color_hex(0x15161C);
const lv_color_t OV_CARD_ALT = lv_color_hex(0x25262D);
const lv_color_t OV_TEXT = lv_color_hex(0xF7F7FA);
const lv_color_t OV_MUTED = lv_color_hex(0xA8A3AB);
const lv_color_t OV_ACCENT = lv_color_hex(0xFF5D6C);
const lv_color_t OV_ACCENT_DARK = lv_color_hex(0x54252D);
const lv_color_t OV_GOOD = lv_color_hex(0x75D6B1);
const lv_color_t OV_AMBER = lv_color_hex(0xFFC66D);

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

// The UI fonts only cover plain ASCII.
String asciiOnly(const String& in)
{
    String out;
    for (size_t i = 0; i < in.length(); ++i)
    {
        const uint8_t c = static_cast<uint8_t>(in[i]);
        if (c >= 0x20 && c < 0x7F)
        {
            out += static_cast<char>(c);
        }
    }
    out.trim();
    return out;
}
} // namespace

// ------------------------------------------------------------------
// Setup
// ------------------------------------------------------------------

void UISystem::setBrightnessHandler(BrightnessHandler handler)
{
    brightnessHandler = handler;
}

void UISystem::begin(AppStateManager* state, ChronosManager* chronosManager, UIApps* appsPtr)
{
    appState = state;
    chronos = chronosManager;
    apps = appsPtr;

    for (uint8_t i = 0; i < ACT_COUNT; ++i)
    {
        actions[i].self = this;
        actions[i].id = i;
    }

    loadPrefs();
    applyBrightness(brightness);
    if (appState != nullptr)
    {
        appState->set24Hour(h24);

        const PulseonAppState& st = appState->getState();
        lastCall = st.callActive;
        lastAlarm = st.alarmRinging;
        lastHead = st.notificationHead;
        lastStored = st.notificationStored;
        lastFind = st.findWatchEventId;
        lastConn = st.phoneConnectionEventId;
    }

    buildSettings();
    buildBluetooth();
    buildContacts();
    buildQr();
    buildQuick();

    if (apps != nullptr)
    {
        apps->addTile("Settings", openSettingsTile, this);
        apps->addTile("Bluetooth", openBluetoothTile, this);
        apps->addTile("Contacts", openContactsTile, this);
        apps->addTile("QR codes", openQrTile, this);
    }
}

void UISystem::loadPrefs()
{
    Preferences prefs;
    if (!prefs.begin(PREFS_NS, false))
    {
        return;
    }
    brightness = prefs.getUChar("bright", 100);
    timeoutIdx = prefs.getUChar("tmo", 4);
    h24 = prefs.getBool("h24", true);
    prefs.end();

    if (brightness < 5) brightness = 5;
    if (brightness > 100) brightness = 100;
    if (timeoutIdx >= TIMEOUT_COUNT) timeoutIdx = 4;
}

void UISystem::savePrefs()
{
    Preferences prefs;
    if (!prefs.begin(PREFS_NS, false))
    {
        return;
    }
    prefs.putUChar("bright", brightness);
    prefs.putUChar("tmo", timeoutIdx);
    prefs.putBool("h24", h24);
    prefs.end();
}

void UISystem::applyBrightness(uint8_t percent)
{
    if (brightnessHandler != nullptr)
    {
        brightnessHandler(percent);
    }
}

lv_obj_t* UISystem::makeRoot(Page page, const char* title)
{
    lv_obj_t* root = makePanel(lv_layer_top(), 0, 0, 240, 320, OV_BG, 0);
    lv_obj_add_flag(root, LV_OBJ_FLAG_CLICKABLE);
    makeLabel(root, title, 16, 10, 208, 28, font_h4, OV_TEXT);
    lv_obj_add_flag(root, LV_OBJ_FLAG_HIDDEN);
    roots[page] = root;
    return root;
}

lv_obj_t* UISystem::addAction(
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
    lv_obj_add_event_cb(button, actionClicked, LV_EVENT_CLICKED, &actions[act]);

    lv_obj_t* label = lv_label_create(button);
    lv_label_set_text(label, text);
    lv_obj_set_style_text_font(label, font_h5, 0);
    lv_obj_set_style_text_color(label, fg, 0);
    lv_obj_center(label);
    return button;
}

void UISystem::buildSettings()
{
    lv_obj_t* root = makeRoot(PAGE_SETTINGS, "SETTINGS");

    brightnessLabel = makeLabel(root, "", 16, 44, 208, 22, font_h5, OV_TEXT);

    brightnessSlider = lv_slider_create(root);
    lv_obj_set_pos(brightnessSlider, 24, 78);
    lv_obj_set_size(brightnessSlider, 192, 14);
    lv_slider_set_range(brightnessSlider, 5, 100);
    lv_slider_set_value(brightnessSlider, brightness, LV_ANIM_OFF);
    lv_obj_set_style_bg_color(brightnessSlider, OV_CARD_ALT, LV_PART_MAIN);
    lv_obj_set_style_bg_color(brightnessSlider, OV_ACCENT, LV_PART_INDICATOR);
    lv_obj_set_style_bg_color(brightnessSlider, OV_TEXT, LV_PART_KNOB);
    lv_obj_set_style_pad_all(brightnessSlider, 6, LV_PART_KNOB);
    lv_obj_add_event_cb(brightnessSlider, sliderChanged, LV_EVENT_VALUE_CHANGED, this);
    lv_obj_add_event_cb(brightnessSlider, sliderReleased, LV_EVENT_RELEASED, this);

    lv_obj_t* timeoutButton = addAction(root, "", 12, 112, 216, 44, OV_CARD, OV_TEXT, ACT_TIMEOUT);
    timeoutLabel = lv_obj_get_child(timeoutButton, 0);

    lv_obj_t* hourButton = addAction(root, "", 12, 166, 216, 44, OV_CARD, OV_TEXT, ACT_HOUR);
    hourLabel = lv_obj_get_child(hourButton, 0);

    makeLabel(root, "Long-press the watch face to change it", 16, 220, 208, 36,
              font_body, OV_MUTED, LV_TEXT_ALIGN_CENTER, LV_LABEL_LONG_WRAP);

    addAction(root, "Back", 12, 268, 216, 44, OV_CARD_ALT, OV_TEXT, ACT_BACK);

    refreshSettingsLabels();
}

void UISystem::buildQuick()
{
    lv_obj_t* root = makeRoot(PAGE_QUICK, "QUICK");

    quickBrightLabel = makeLabel(root, "", 16, 40, 208, 22, font_h5, OV_TEXT);

    quickSlider = lv_slider_create(root);
    lv_obj_set_pos(quickSlider, 24, 70);
    lv_obj_set_size(quickSlider, 192, 14);
    lv_slider_set_range(quickSlider, 5, 100);
    lv_slider_set_value(quickSlider, brightness, LV_ANIM_OFF);
    lv_obj_set_style_bg_color(quickSlider, OV_CARD_ALT, LV_PART_MAIN);
    lv_obj_set_style_bg_color(quickSlider, OV_ACCENT, LV_PART_INDICATOR);
    lv_obj_set_style_bg_color(quickSlider, OV_TEXT, LV_PART_KNOB);
    lv_obj_set_style_pad_all(quickSlider, 6, LV_PART_KNOB);
    lv_obj_add_event_cb(quickSlider, quickSliderChanged, LV_EVENT_VALUE_CHANGED, this);
    lv_obj_add_event_cb(quickSlider, sliderReleased, LV_EVENT_RELEASED, this);

    lv_obj_t* quiet = addAction(root, "", 12, 100, 106, 52, OV_CARD, OV_TEXT, ACT_Q_QUIET);
    lv_obj_t* bt = addAction(root, "", 122, 100, 106, 52, OV_CARD, OV_TEXT, ACT_Q_BT);
    lv_obj_t* find = addAction(root, "", 12, 160, 106, 52, OV_CARD, OV_TEXT, ACT_Q_FIND);
    lv_obj_t* theme = addAction(root, "", 122, 160, 106, 52, OV_CARD, OV_TEXT, ACT_Q_THEME);
    quickQuietLabel = lv_obj_get_child(quiet, 0);
    quickBtLabel = lv_obj_get_child(bt, 0);
    quickFindLabel = lv_obj_get_child(find, 0);
    quickThemeLabel = lv_obj_get_child(theme, 0);

    lv_obj_t* tileLabels[4] = {quickQuietLabel, quickBtLabel, quickFindLabel, quickThemeLabel};
    for (uint8_t i = 0; i < 4; ++i)
    {
        lv_obj_set_style_text_font(tileLabels[i], font_body, 0);
        lv_obj_set_style_text_align(tileLabels[i], LV_TEXT_ALIGN_CENTER, 0);
    }

    addAction(root, "All settings", 12, 220, 216, 40, OV_CARD, OV_TEXT, ACT_Q_ALL);
    addAction(root, "Close", 12, 268, 216, 44, OV_CARD_ALT, OV_TEXT, ACT_Q_CLOSE);

    refreshQuick();
}

void UISystem::buildBluetooth()
{
    lv_obj_t* root = makeRoot(PAGE_BLUETOOTH, "BLUETOOTH");

    btStatus = makeLabel(root, "", 16, 46, 208, 24, font_h5, OV_MUTED);
    btAddress = makeLabel(root, "", 16, 78, 208, 20, font_body, OV_MUTED);
    btPhone = makeLabel(root, "", 16, 102, 208, 20, font_body, OV_MUTED);
    btApp = makeLabel(root, "", 16, 126, 208, 20, font_body, OV_MUTED);

    lv_obj_t* toggle = addAction(root, "", 40, 166, 160, 48, OV_ACCENT_DARK, OV_ACCENT, ACT_BT_TOGGLE);
    btToggleLabel = lv_obj_get_child(toggle, 0);

    makeLabel(root, "Turning it off hides the watch from the Chronos app", 16, 222, 208, 40,
              font_body, OV_MUTED, LV_TEXT_ALIGN_CENTER, LV_LABEL_LONG_WRAP);

    addAction(root, "Back", 12, 268, 216, 44, OV_CARD_ALT, OV_TEXT, ACT_BACK);
}

void UISystem::buildContacts()
{
    lv_obj_t* root = makeRoot(PAGE_CONTACTS, "CONTACTS");
    contactList = makeList(root, 8, 44, 224, 216);
    addAction(root, "Back", 12, 268, 216, 44, OV_CARD_ALT, OV_TEXT, ACT_BACK);
}

void UISystem::buildQr()
{
    lv_obj_t* root = makeRoot(PAGE_QR, "QR CODES");

    qrText = makeLabel(root, "", 16, 208, 208, 20, font_body, OV_MUTED, LV_TEXT_ALIGN_CENTER);
    qrIndex = makeLabel(root, "", 76, 238, 88, 22, font_h5, OV_TEXT, LV_TEXT_ALIGN_CENTER);

    addAction(root, "Prev", 8, 232, 64, 34, OV_CARD, OV_TEXT, ACT_QR_PREV);
    addAction(root, "Next", 168, 232, 64, 34, OV_CARD, OV_TEXT, ACT_QR_NEXT);
    addAction(root, "Back", 12, 272, 216, 40, OV_CARD_ALT, OV_TEXT, ACT_BACK);
}

// ------------------------------------------------------------------
// Pages
// ------------------------------------------------------------------

void UISystem::openSettingsTile(void* user)  { static_cast<UISystem*>(user)->showPage(PAGE_SETTINGS); }
void UISystem::openBluetoothTile(void* user) { static_cast<UISystem*>(user)->showPage(PAGE_BLUETOOTH); }
void UISystem::openContactsTile(void* user)  { static_cast<UISystem*>(user)->showPage(PAGE_CONTACTS); }
void UISystem::openQrTile(void* user)        { static_cast<UISystem*>(user)->showPage(PAGE_QR); }

void UISystem::showQuick()
{
    showPage(PAGE_QUICK);
}

void UISystem::quickSliderChanged(lv_event_t* event)
{
    UISystem* self = static_cast<UISystem*>(lv_event_get_user_data(event));
    if (self == nullptr || self->quickSlider == nullptr)
    {
        return;
    }

    self->brightness = static_cast<uint8_t>(lv_slider_get_value(self->quickSlider));
    self->dimmed = false;
    self->applyBrightness(self->brightness);
    lv_label_set_text_fmt(self->quickBrightLabel, "Brightness  %u%%",
                          static_cast<unsigned>(self->brightness));
    self->refreshSettingsLabels();
}

void UISystem::refreshQuick()
{
    if (quickSlider == nullptr)
    {
        return;
    }

    lv_label_set_text_fmt(quickBrightLabel, "Brightness  %u%%", static_cast<unsigned>(brightness));
    lv_slider_set_value(quickSlider, brightness, LV_ANIM_OFF);

    const bool quiet = appState != nullptr && appState->getState().quietEnabled;
    const bool btOn = chronos != nullptr && chronos->isBluetoothOn();

    lv_label_set_text_fmt(quickQuietLabel, "Quiet\n%s", quiet ? "On" : "Off");
    lv_label_set_text_fmt(quickBtLabel, "Bluetooth\n%s", btOn ? "On" : "Off");
    lv_label_set_text(quickFindLabel, quickFinding ? "Stop\nfinding" : "Find\nphone");
    lv_label_set_text_fmt(quickThemeLabel, "Theme\n%s", UI_PALETTES[uiThemeLoad()].name);

    lv_obj_center(quickQuietLabel);
    lv_obj_center(quickBtLabel);
    lv_obj_center(quickFindLabel);
    lv_obj_center(quickThemeLabel);
}

void UISystem::showSettings()
{
    showPage(PAGE_SETTINGS);
}

void UISystem::showPage(Page page)
{
    for (uint8_t i = PAGE_SETTINGS; i < PAGE_COUNT; ++i)
    {
        if (roots[i] != nullptr)
        {
            lv_obj_add_flag(roots[i], LV_OBJ_FLAG_HIDDEN);
        }
    }

    // Free the QR bitmap whenever the QR page is left.
    if (page != PAGE_QR && qrObj != nullptr)
    {
        lv_obj_delete(qrObj);
        qrObj = nullptr;
    }

    current = page;
    if (page == PAGE_NONE || roots[page] == nullptr)
    {
        current = PAGE_NONE;
        return;
    }

    if (page == PAGE_SETTINGS) refreshSettingsLabels();
    if (page == PAGE_BLUETOOTH) refreshBluetooth();
    if (page == PAGE_CONTACTS) rebuildContacts();
    if (page == PAGE_QR) rebuildQr();
    if (page == PAGE_QUICK) refreshQuick();

    lv_obj_clear_flag(roots[page], LV_OBJ_FLAG_HIDDEN);
    lv_obj_move_foreground(roots[page]);
}

void UISystem::refreshSettingsLabels()
{
    if (brightnessLabel == nullptr)
    {
        return;
    }

    lv_label_set_text_fmt(brightnessLabel, "Brightness  %u%%", static_cast<unsigned>(brightness));
    lv_label_set_text_fmt(timeoutLabel, "Screen dims: %s", TIMEOUT_NAMES[timeoutIdx]);
    lv_label_set_text_fmt(hourLabel, "Clock: %s", h24 ? "24-hour" : "12-hour");
    lv_obj_center(timeoutLabel);
    lv_obj_center(hourLabel);
    lv_slider_set_value(brightnessSlider, brightness, LV_ANIM_OFF);
}

void UISystem::refreshBluetooth()
{
    if (appState == nullptr || chronos == nullptr || btStatus == nullptr)
    {
        return;
    }

    const PulseonAppState& st = appState->getState();
    const bool on = chronos->isBluetoothOn();

    if (!on)
    {
        lv_label_set_text(btStatus, "Bluetooth off");
        lv_obj_set_style_text_color(btStatus, OV_MUTED, 0);
        lv_label_set_text(btAddress, "");
        lv_label_set_text(btPhone, "");
        lv_label_set_text(btApp, "");
    }
    else
    {
        if (st.phoneConnected)
        {
            lv_label_set_text(btStatus, "Phone connected");
            lv_obj_set_style_text_color(btStatus, OV_GOOD, 0);
        }
        else
        {
            lv_label_set_text(btStatus, "Waiting for phone");
            lv_obj_set_style_text_color(btStatus, OV_AMBER, 0);
        }

        const String addr = chronos->getAddress();
        lv_label_set_text_fmt(btAddress, "Address %s", addr.c_str());

        if (st.phoneConnected)
        {
            lv_label_set_text_fmt(btPhone, "Phone battery %u%%%s",
                                  static_cast<unsigned>(st.phoneBattery),
                                  st.phoneCharging ? " (charging)" : "");
        }
        else
        {
            lv_label_set_text(btPhone, "Visible as PULSEON");
        }

        if (st.appVersion.length() > 0)
        {
            const String version = asciiOnly(st.appVersion);
            lv_label_set_text_fmt(btApp, "Chronos app %s", version.c_str());
        }
        else
        {
            lv_label_set_text(btApp, "");
        }
    }

    lv_label_set_text(btToggleLabel, on ? "Turn off" : "Turn on");
    lv_obj_center(btToggleLabel);
}

void UISystem::rebuildContacts()
{
    if (contactList == nullptr || chronos == nullptr)
    {
        return;
    }

    lv_obj_clean(contactList);

    int count = chronos->getContactCount();
    if (count <= 0)
    {
        makeLabel(contactList, "No contacts synced yet", 0, 0, 224, 24, font_body, OV_MUTED,
                  LV_TEXT_ALIGN_CENTER);
        return;
    }
    if (count > 40)
    {
        count = 40;
    }

    const int sos = chronos->getSosContactIndex();

    for (int i = 0; i < count; ++i)
    {
        const Contact c = chronos->getContact(i);
        String name = asciiOnly(c.name);
        if (name.length() == 0)
        {
            name = "(no name)";
        }
        const String number = asciiOnly(c.number);

        lv_obj_t* card = makePanel(contactList, 0, 0, 224, 52, OV_CARD, 14);
        makeLabel(card, name.c_str(), 12, 4, i == sos ? 150 : 200, 22, font_h5, OV_TEXT);
        makeLabel(card, number.c_str(), 12, 28, 200, 18, font_body, OV_MUTED);
        if (i == sos)
        {
            makeLabel(card, "SOS", 166, 4, 48, 22, font_h5, OV_ACCENT, LV_TEXT_ALIGN_RIGHT);
        }
    }
}

void UISystem::rebuildQr()
{
    if (appState == nullptr || roots[PAGE_QR] == nullptr)
    {
        return;
    }

    if (qrObj != nullptr)
    {
        lv_obj_delete(qrObj);
        qrObj = nullptr;
    }

    const PulseonAppState& st = appState->getState();

    qrCount = 0;
    for (uint8_t i = 0; i < PULSEON_MAX_QR; ++i)
    {
        if (st.qrCodes[i].length() > 0)
        {
            qrIndices[qrCount++] = i;
        }
    }

    if (qrCount == 0)
    {
        qrPos = 0;
        lv_label_set_text(qrText, "No QR codes yet");
        lv_label_set_text(qrIndex, "");
        return;
    }

    if (qrPos >= qrCount)
    {
        qrPos = 0;
    }

    const String& data = st.qrCodes[qrIndices[qrPos]];

    qrObj = lv_qrcode_create(roots[PAGE_QR]);
    lv_qrcode_set_size(qrObj, 150);
    lv_qrcode_set_dark_color(qrObj, lv_color_black());
    lv_qrcode_set_light_color(qrObj, lv_color_white());
    lv_obj_set_pos(qrObj, 40, 44);
    lv_obj_set_style_border_color(qrObj, lv_color_white(), 0);
    lv_obj_set_style_border_width(qrObj, 5, 0);

    if (lv_qrcode_update(qrObj, data.c_str(), data.length()) != LV_RESULT_OK)
    {
        lv_label_set_text(qrText, "Too long to display");
    }
    else
    {
        const String shown = asciiOnly(data);
        lv_label_set_text(qrText, shown.c_str());
    }
    lv_label_set_text_fmt(qrIndex, "%u / %u",
                          static_cast<unsigned>(qrPos + 1), static_cast<unsigned>(qrCount));
}

// ------------------------------------------------------------------
// Events
// ------------------------------------------------------------------

void UISystem::actionClicked(lv_event_t* event)
{
    Action* action = static_cast<Action*>(lv_event_get_user_data(event));
    if (action != nullptr && action->self != nullptr)
    {
        action->self->handle(action->id);
    }
}

void UISystem::sliderChanged(lv_event_t* event)
{
    UISystem* self = static_cast<UISystem*>(lv_event_get_user_data(event));
    if (self == nullptr || self->brightnessSlider == nullptr)
    {
        return;
    }

    self->brightness = static_cast<uint8_t>(lv_slider_get_value(self->brightnessSlider));
    self->dimmed = false;
    self->applyBrightness(self->brightness);
    lv_label_set_text_fmt(self->brightnessLabel, "Brightness  %u%%",
                          static_cast<unsigned>(self->brightness));
}

void UISystem::sliderReleased(lv_event_t* event)
{
    UISystem* self = static_cast<UISystem*>(lv_event_get_user_data(event));
    if (self != nullptr)
    {
        self->savePrefs();
    }
}

void UISystem::handle(uint8_t id)
{
    switch (static_cast<Act>(id))
    {
        case ACT_BACK:
            showPage(PAGE_NONE);
            if (apps != nullptr)
            {
                apps->show();
            }
            break;

        case ACT_TIMEOUT:
            timeoutIdx = (timeoutIdx + 1) % TIMEOUT_COUNT;
            savePrefs();
            refreshSettingsLabels();
            break;

        case ACT_HOUR:
            // poll() notices the change in AppState, saves it and updates the label
            if (appState != nullptr)
            {
                appState->set24Hour(!h24);
            }
            break;

        case ACT_BT_TOGGLE:
            if (chronos != nullptr)
            {
                chronos->setBluetoothEnabled(!chronos->isBluetoothOn());
                refreshBluetooth();
            }
            break;

        case ACT_QR_PREV:
            if (qrCount > 0)
            {
                qrPos = (qrPos + qrCount - 1) % qrCount;
                rebuildQr();
            }
            break;

        case ACT_QR_NEXT:
            if (qrCount > 0)
            {
                qrPos = (qrPos + 1) % qrCount;
                rebuildQr();
            }
            break;

        case ACT_Q_QUIET:
        {
            if (appState != nullptr)
            {
                const PulseonAppState& st = appState->getState();
                appState->setQuietHours(!st.quietEnabled, st.quietStartHour, st.quietStartMinute,
                                        st.quietEndHour, st.quietEndMinute);
            }
            refreshQuick();
            break;
        }

        case ACT_Q_BT:
            if (chronos != nullptr)
            {
                chronos->setBluetoothEnabled(!chronos->isBluetoothOn());
            }
            refreshQuick();
            break;

        case ACT_Q_FIND:
            if (chronos != nullptr)
            {
                quickFinding = !quickFinding;
                chronos->findPhone(quickFinding);
            }
            refreshQuick();
            break;

        case ACT_Q_THEME:
            if (apps != nullptr)
            {
                apps->cycleTheme();
            }
            refreshQuick();
            break;

        case ACT_Q_ALL:
            showPage(PAGE_SETTINGS);
            break;

        case ACT_Q_CLOSE:
            showPage(PAGE_NONE);
            break;

        default:
            break;
    }
}

// ------------------------------------------------------------------
// Polling: wake on events, idle dimming, refresh the visible page
// ------------------------------------------------------------------

void UISystem::poll()
{
    if (appState == nullptr)
    {
        return;
    }

    const uint32_t now = millis();
    if (now - lastPollMs < 250)
    {
        return;
    }
    lastPollMs = now;

    const PulseonAppState& st = appState->getState();

    const bool event = st.callActive != lastCall ||
                       st.alarmRinging != lastAlarm ||
                       st.notificationHead != lastHead ||
                       st.notificationStored != lastStored ||
                       st.findWatchEventId != lastFind ||
                       st.phoneConnectionEventId != lastConn;
    lastCall = st.callActive;
    lastAlarm = st.alarmRinging;
    lastHead = st.notificationHead;
    lastStored = st.notificationStored;
    lastFind = st.findWatchEventId;
    lastConn = st.phoneConnectionEventId;
    if (event)
    {
        lv_display_trigger_activity(nullptr);
    }

    // The phone's 12/24-hour choice wins and is remembered.
    if (st.is24Hour != h24)
    {
        h24 = st.is24Hour;
        savePrefs();
        if (current == PAGE_SETTINGS)
        {
            refreshSettingsLabels();
        }
    }

    // Idle dimming
    const uint16_t limit = TIMEOUT_SECONDS[timeoutIdx];
    const uint32_t idle = lv_display_get_inactive_time(nullptr);
    const bool keepAwake = st.callActive || st.alarmRinging >= 0 || uiUtilsKeepAwake();
    if (!keepAwake && limit > 0 && idle >= static_cast<uint32_t>(limit) * 1000UL)
    {
        if (!dimmed)
        {
            dimmed = true;
            applyBrightness(brightness > DIM_PERCENT ? DIM_PERCENT : brightness);
        }
    }
    else if (dimmed)
    {
        dimmed = false;
        applyBrightness(brightness);
    }

    if (current == PAGE_BLUETOOTH && now - lastRefreshMs >= 500)
    {
        lastRefreshMs = now;
        refreshBluetooth();
    }
    else if (current == PAGE_QUICK && now - lastRefreshMs >= 500)
    {
        lastRefreshMs = now;
        refreshQuick();
    }
}
