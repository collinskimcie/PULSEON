#include "UIHome.h"

#include <stdio.h>
#include <string.h>

#if LV_FONT_MONTSERRAT_48
#define HOME_FONT_XL (&lv_font_montserrat_48)
#elif LV_FONT_MONTSERRAT_40
#define HOME_FONT_XL (&lv_font_montserrat_40)
#elif LV_FONT_MONTSERRAT_32
#define HOME_FONT_XL (&lv_font_montserrat_32)
#else
#define HOME_FONT_XL LV_FONT_DEFAULT
#endif

#if LV_FONT_MONTSERRAT_28
#define HOME_FONT_L (&lv_font_montserrat_28)
#elif LV_FONT_MONTSERRAT_24
#define HOME_FONT_L (&lv_font_montserrat_24)
#elif LV_FONT_MONTSERRAT_20
#define HOME_FONT_L (&lv_font_montserrat_20)
#else
#define HOME_FONT_L LV_FONT_DEFAULT
#endif

namespace
{
HomeColors col;
HomeData last;
bool haveData = false;

lv_obj_t* panels[HOME_FACE_KINDS] = {};

struct OrbitUI
{
    lv_obj_t *sec, *bat, *alerts, *time, *date, *batLbl, *alertLbl, *wx, *alarm;
};
struct TodayUI
{
    lv_obj_t *time, *date, *temp, *wx, *alarm, *batVal, *batBar, *alerts;
};
struct StackUI
{
    lv_obj_t *date, *hour, *min, *wx, *alarm, *alerts;
};
OrbitUI orbitUi = {};
TodayUI todayUi = {};
StackUI stackUi = {};

const char* const DAYS[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
const char* const MONTHS[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                                "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

int panelW(lv_obj_t* p)
{
    const int w = lv_obj_get_width(p);
    return w > 0 ? w : 240;
}

int panelH(lv_obj_t* p)
{
    const int h = lv_obj_get_height(p);
    return h > 0 ? h : 320;
}

void setText(lv_obj_t* o, const char* t)
{
    if (o != nullptr)
    {
        lv_label_set_text(o, t);
    }
}

lv_obj_t* mkLabel(lv_obj_t* parent, const lv_font_t* font, lv_color_t color, const char* text)
{
    lv_obj_t* l = lv_label_create(parent);
    lv_obj_set_style_text_font(l, font, 0);
    lv_obj_set_style_text_color(l, color, 0);
    lv_label_set_text(l, text);
    return l;
}

lv_obj_t* mkPanel(lv_obj_t* parent, int w, int h, lv_color_t bg, int radius)
{
    lv_obj_t* o = lv_obj_create(parent);
    lv_obj_remove_style_all(o);
    lv_obj_set_size(o, w, h);
    lv_obj_set_style_bg_color(o, bg, 0);
    lv_obj_set_style_bg_opa(o, LV_OPA_COVER, 0);
    lv_obj_set_style_radius(o, radius, 0);
    lv_obj_clear_flag(o, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_clear_flag(o, LV_OBJ_FLAG_CLICKABLE);
    return o;
}

lv_obj_t* mkArc(lv_obj_t* parent, int diameter, int width, lv_color_t color, int maxValue)
{
    lv_obj_t* a = lv_arc_create(parent);
    lv_obj_remove_style(a, nullptr, LV_PART_KNOB);
    lv_obj_clear_flag(a, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_size(a, diameter, diameter);
    lv_obj_center(a);
    lv_arc_set_rotation(a, 270);
    lv_arc_set_bg_angles(a, 0, 360);
    lv_arc_set_range(a, 0, maxValue);
    lv_arc_set_value(a, 0);
    lv_obj_set_style_arc_width(a, width, LV_PART_MAIN);
    lv_obj_set_style_arc_width(a, width, LV_PART_INDICATOR);
    lv_obj_set_style_arc_color(a, col.card, LV_PART_MAIN);
    lv_obj_set_style_arc_color(a, color, LV_PART_INDICATOR);
    lv_obj_set_style_arc_rounded(a, true, LV_PART_MAIN);
    lv_obj_set_style_arc_rounded(a, true, LV_PART_INDICATOR);
    return a;
}

lv_obj_t* mkCard(lv_obj_t* parent, int x, int y, int w, int h, lv_color_t accent,
                 const char* caption, lv_obj_t** value, const char* initial)
{
    lv_obj_t* c = mkPanel(parent, w, h, col.card, 16);
    lv_obj_set_pos(c, x, y);
    lv_obj_set_style_border_width(c, 2, 0);
    lv_obj_set_style_border_color(c, accent, 0);
    lv_obj_set_style_border_opa(c, LV_OPA_40, 0);

    lv_obj_t* k = mkLabel(c, LV_FONT_DEFAULT, accent, caption);
    lv_obj_align(k, LV_ALIGN_TOP_LEFT, 10, 8);

    *value = mkLabel(c, HOME_FONT_L, col.text, initial);
    lv_obj_align(*value, LV_ALIGN_LEFT_MID, 10, 4);
    return c;
}

lv_obj_t* mkChipRow(lv_obj_t* parent, int w, int h, int bottomGap)
{
    lv_obj_t* row = lv_obj_create(parent);
    lv_obj_remove_style_all(row);
    lv_obj_set_size(row, w, h);
    lv_obj_set_flex_flow(row, LV_FLEX_FLOW_ROW_WRAP);
    lv_obj_set_flex_align(row, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_style_pad_column(row, 6, 0);
    lv_obj_set_style_pad_row(row, 6, 0);
    lv_obj_clear_flag(row, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_clear_flag(row, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_align(row, LV_ALIGN_BOTTOM_MID, 0, -bottomGap);
    return row;
}

lv_obj_t* mkChip(lv_obj_t* row, lv_color_t accent, lv_obj_t** label)
{
    lv_obj_t* chip = lv_obj_create(row);
    lv_obj_remove_style_all(chip);
    lv_obj_set_size(chip, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_style_bg_color(chip, col.card, 0);
    lv_obj_set_style_bg_opa(chip, LV_OPA_COVER, 0);
    lv_obj_set_style_radius(chip, 14, 0);
    lv_obj_set_style_pad_hor(chip, 10, 0);
    lv_obj_set_style_pad_ver(chip, 5, 0);
    lv_obj_clear_flag(chip, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_clear_flag(chip, LV_OBJ_FLAG_CLICKABLE);
    *label = mkLabel(chip, LV_FONT_DEFAULT, accent, "--");
    return chip;
}

void buildOrbit(lv_obj_t* p)
{
    const int W = panelW(p);
    const int H = panelH(p);
    const int d = W - 24;
    int aw = d / 26;
    if (aw < 5)
    {
        aw = 5;
    }

    OrbitUI& u = orbitUi;
    u.sec = mkArc(p, d, aw, col.a1, 59);
    u.bat = mkArc(p, d - 4 * aw, aw, col.a2, 100);
    u.alerts = mkArc(p, d - 8 * aw, aw, col.a3, 10);

    u.date = mkLabel(p, LV_FONT_DEFAULT, col.a1, "");
    lv_obj_align(u.date, LV_ALIGN_TOP_MID, 0, (H - d) / 4);

    u.time = mkLabel(p, HOME_FONT_XL, col.text, "--:--");
    lv_obj_align(u.time, LV_ALIGN_CENTER, 0, -14);

    u.batLbl = mkLabel(p, LV_FONT_DEFAULT, col.a2, LV_SYMBOL_BATTERY_3 " --");
    lv_obj_align(u.batLbl, LV_ALIGN_CENTER, -32, 26);
    u.alertLbl = mkLabel(p, LV_FONT_DEFAULT, col.a3, LV_SYMBOL_ENVELOPE " 0");
    lv_obj_align(u.alertLbl, LV_ALIGN_CENTER, 32, 26);

    lv_obj_t* row = mkChipRow(p, W - 16, 36, 12);
    mkChip(row, col.a1, &u.wx);
    mkChip(row, col.a4, &u.alarm);
}

void buildToday(lv_obj_t* p)
{
    const int W = panelW(p);
    const int H = panelH(p);
    const int pad = W / 16;
    const int hdr = H / 6;
    const int cw = (W - 3 * pad) / 2;
    const int ch = (H - hdr - 2 * pad) / 2;
    const int x0 = pad, x1 = 2 * pad + cw;
    const int y0 = hdr, y1 = hdr + ch + pad;

    TodayUI& u = todayUi;
    u.time = mkLabel(p, HOME_FONT_L, col.text, "--:--");
    lv_obj_align(u.time, LV_ALIGN_TOP_LEFT, pad, pad);
    u.date = mkLabel(p, LV_FONT_DEFAULT, col.dim, "");
    lv_obj_align(u.date, LV_ALIGN_TOP_RIGHT, -pad, pad + 8);

    lv_obj_t* weather = mkCard(p, x0, y0, cw, ch, col.a1, "WEATHER", &u.temp, "--");
    u.wx = mkLabel(weather, LV_FONT_DEFAULT, col.dim, "");
    lv_obj_align(u.wx, LV_ALIGN_BOTTOM_LEFT, 10, -8);

    mkCard(p, x1, y0, cw, ch, col.a2, "ALARM", &u.alarm, "--:--");

    lv_obj_t* battery = mkCard(p, x0, y1, cw, ch, col.a3, "PHONE", &u.batVal, "--");
    u.batBar = lv_bar_create(battery);
    lv_obj_set_size(u.batBar, cw - 24, 6);
    lv_bar_set_range(u.batBar, 0, 100);
    lv_bar_set_value(u.batBar, 0, LV_ANIM_OFF);
    lv_obj_clear_flag(u.batBar, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_bg_color(u.batBar, col.bg, LV_PART_MAIN);
    lv_obj_set_style_bg_color(u.batBar, col.a3, LV_PART_INDICATOR);
    lv_obj_set_style_radius(u.batBar, 3, LV_PART_MAIN);
    lv_obj_set_style_radius(u.batBar, 3, LV_PART_INDICATOR);
    lv_obj_align(u.batBar, LV_ALIGN_BOTTOM_MID, 0, -12);

    mkCard(p, x1, y1, cw, ch, col.a4, "ALERTS", &u.alerts, "0");
}

void buildStack(lv_obj_t* p)
{
    const int W = panelW(p);
    const int H = panelH(p);
    const int fh = lv_font_get_line_height(HOME_FONT_XL);

    StackUI& u = stackUi;
    u.date = mkLabel(p, LV_FONT_DEFAULT, col.dim, "");
    lv_obj_align(u.date, LV_ALIGN_TOP_MID, 0, H / 14);

    u.hour = mkLabel(p, HOME_FONT_XL, col.a1, "--");
    lv_obj_align(u.hour, LV_ALIGN_CENTER, 0, -fh / 2 - H / 14);
    u.min = mkLabel(p, HOME_FONT_XL, col.a2, "--");
    lv_obj_align(u.min, LV_ALIGN_CENTER, 0, fh / 2 - H / 14);

    lv_obj_t* row = mkChipRow(p, W - 16, 64, 14);
    mkChip(row, col.a1, &u.wx);
    mkChip(row, col.a2, &u.alarm);
    mkChip(row, col.a4, &u.alerts);
}

void rebuild(uint8_t kind)
{
    lv_obj_t* p = panels[kind];
    if (p == nullptr)
    {
        return;
    }
    lv_obj_clean(p);
    lv_obj_set_style_bg_color(p, col.bg, 0);
    lv_obj_set_style_bg_opa(p, LV_OPA_COVER, 0);
    lv_obj_clear_flag(p, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_update_layout(p);

    if (kind == HOME_FACE_ORBIT)
    {
        buildOrbit(p);
    }
    else if (kind == HOME_FACE_TODAY)
    {
        buildToday(p);
    }
    else
    {
        buildStack(p);
    }
}
}  // namespace

void uiHomeBuildFace(lv_obj_t* panel, uint8_t kind, const HomeColors& colors)
{
    if (kind >= HOME_FACE_KINDS)
    {
        uiHomeExtBuild(panel, kind, colors);
        return;
    }
    if (panel == nullptr)
    {
        return;
    }
    col = colors;
    panels[kind] = panel;
    rebuild(kind);
    if (haveData)
    {
        uiHomeUpdate(last);
    }
}

void uiHomeRecolor(const HomeColors& colors)
{
    col = colors;
    uiHomeExtRecolor(colors);
    for (uint8_t k = 0; k < HOME_FACE_KINDS; ++k)
    {
        rebuild(k);
    }
    if (haveData)
    {
        uiHomeUpdate(last);
    }
}

void uiHomeUpdate(const HomeData& d)
{
    last = d;
    haveData = true;
    uiHomeExtUpdate(d);

    char tm[8], date[24], temp[12], bat[8], num[8], line[40];
    snprintf(tm, sizeof(tm), "%02d:%02d", (int)d.hour, (int)d.minute);
    snprintf(date, sizeof(date), "%s %d %s", DAYS[d.weekday % 7], (int)d.day,
             MONTHS[(d.month >= 1 && d.month <= 12) ? d.month - 1 : 0]);
    if (d.hasTemp)
    {
        snprintf(temp, sizeof(temp), "%d\xC2\xB0", (int)d.tempC);
    }
    else
    {
        strcpy(temp, "--");
    }
    if (d.battery >= 0)
    {
        snprintf(bat, sizeof(bat), "%d%%", (int)d.battery);
    }
    else
    {
        strcpy(bat, "--");
    }
    if (!d.timeValid)
    {
        strcpy(tm, "--:--");
        strcpy(date, "-- -- --");
    }
    snprintf(num, sizeof(num), "%d", (int)d.notifCount);
    const int batVal = d.battery >= 0 ? d.battery : 0;
    const int notVal = d.notifCount > 10 ? 10 : d.notifCount;

    char wxLine[40], alarmLine[24], alertLine[16];
    snprintf(wxLine, sizeof(wxLine), "%s %s", temp, d.weather);
    snprintf(alarmLine, sizeof(alarmLine), LV_SYMBOL_BELL " %s", d.nextAlarm);
    snprintf(alertLine, sizeof(alertLine), LV_SYMBOL_ENVELOPE " %s", num);

    OrbitUI& o = orbitUi;
    if (panels[HOME_FACE_ORBIT] != nullptr)
    {
        setText(o.time, tm);
        setText(o.date, date);
        snprintf(line, sizeof(line), LV_SYMBOL_BATTERY_3 " %s", bat);
        setText(o.batLbl, line);
        setText(o.alertLbl, alertLine);
        setText(o.wx, wxLine);
        setText(o.alarm, alarmLine);
        lv_arc_set_value(o.sec, d.second > 59 ? 59 : d.second);
        lv_arc_set_value(o.bat, batVal);
        lv_arc_set_value(o.alerts, notVal);
    }

    TodayUI& t = todayUi;
    if (panels[HOME_FACE_TODAY] != nullptr)
    {
        setText(t.time, tm);
        setText(t.date, date);
        setText(t.temp, temp);
        setText(t.wx, d.weather);
        setText(t.alarm, d.nextAlarm);
        setText(t.batVal, bat);
        setText(t.alerts, num);
        lv_bar_set_value(t.batBar, batVal, LV_ANIM_OFF);
    }

    StackUI& s = stackUi;
    if (panels[HOME_FACE_STACK] != nullptr)
    {
        char hh[4], mm[4];
        snprintf(hh, sizeof(hh), "%02d", (int)d.hour);
        snprintf(mm, sizeof(mm), "%02d", (int)d.minute);
        if (!d.timeValid)
        {
            strcpy(hh, "--");
            strcpy(mm, "--");
        }
        setText(s.date, date);
        setText(s.hour, hh);
        setText(s.min, mm);
        setText(s.wx, wxLine);
        setText(s.alarm, alarmLine);
        setText(s.alerts, alertLine);
    }
}
