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

#if LV_FONT_MONTSERRAT_20
#define HOME_FONT_M (&lv_font_montserrat_20)
#elif LV_FONT_MONTSERRAT_18
#define HOME_FONT_M (&lv_font_montserrat_18)
#elif LV_FONT_MONTSERRAT_16
#define HOME_FONT_M (&lv_font_montserrat_16)
#else
#define HOME_FONT_M LV_FONT_DEFAULT
#endif

#define HEX(v) lv_color_hex(v)

namespace
{
constexpr uint8_t FACES = 6;
HomeColors col;
HomeData cur;
bool haveCur = false;
lv_obj_t* panels[FACES] = {};

struct Seg
{
    lv_obj_t* s[7];
    int8_t shown;
};
struct EditUI
{
    Seg h0, h1, m0, m1;
    lv_obj_t *date, *link, *wd, *dd, *mon, *hr, *steps, *bat;
};
struct BentoUI
{
    lv_obj_t *date, *time, *hr, *steps, *bat, *o2, *wx, *alarm, *alerts;
};
struct AuraUI
{
    lv_obj_t *time, *date, *wx, *hr, *steps, *bat;
};
struct RegUI
{
    lv_obj_t *date, *hour, *minute, *sec, *secArc, *strip;
};
struct SwissUI
{
    Seg h0, h1, m0, m1;
    lv_obj_t *stepsLbl, *stepsFill, *batLbl, *batFill, *foot;
};
struct GlassUI
{
    lv_obj_t *wx, *time, *date, *r1, *r2, *r3, *hr, *o2, *alerts;
};
EditUI edit = {};
BentoUI bento = {};
AuraUI aura = {};
RegUI reg = {};
SwissUI swiss = {};
GlassUI glass = {};

const char* const DAYS[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
const char* const MONTHS[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                                "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

struct Strs
{
    char tm[8], hh[4], mm[4], ss[4], date[24], dateUp[24], wd[4], dd[4], mon[4];
    char temp[12], wx[40], hr[8], steps[8], o2[8], bat[8], alarm[8], link[10], notif[8];
    int stepsPct, batPct, secPct, o2Pct;
};

void upper(char* t)
{
    for (; *t; ++t)
    {
        if (*t >= 'a' && *t <= 'z')
        {
            *t = (char)(*t - 32);
        }
    }
}

void makeStrs(const HomeData& d, Strs& s)
{
    if (d.timeValid)
    {
        const char* mo = MONTHS[(d.month >= 1 && d.month <= 12) ? d.month - 1 : 0];
        snprintf(s.tm, sizeof(s.tm), "%02d:%02d", (int)d.hour, (int)d.minute);
        snprintf(s.hh, sizeof(s.hh), "%02d", (int)d.hour);
        snprintf(s.mm, sizeof(s.mm), "%02d", (int)d.minute);
        snprintf(s.ss, sizeof(s.ss), "%02d", (int)d.second);
        snprintf(s.date, sizeof(s.date), "%s %d %s", DAYS[d.weekday % 7], (int)d.day, mo);
        snprintf(s.wd, sizeof(s.wd), "%s", DAYS[d.weekday % 7]);
        snprintf(s.dd, sizeof(s.dd), "%d", (int)d.day);
        snprintf(s.mon, sizeof(s.mon), "%s", mo);
    }
    else
    {
        strcpy(s.tm, "--:--");
        strcpy(s.hh, "--");
        strcpy(s.mm, "--");
        strcpy(s.ss, "--");
        strcpy(s.date, "-- -- --");
        strcpy(s.wd, "---");
        strcpy(s.dd, "--");
        strcpy(s.mon, "---");
    }
    snprintf(s.dateUp, sizeof(s.dateUp), "%s", s.date);
    upper(s.dateUp);
    upper(s.wd);
    upper(s.mon);
    if (d.hasTemp)
    {
        snprintf(s.temp, sizeof(s.temp), "%d\xC2\xB0", (int)d.tempC);
    }
    else
    {
        strcpy(s.temp, "--");
    }
    snprintf(s.wx, sizeof(s.wx), "%s %s", s.temp, d.weather);
    upper(s.wx);
    if (d.heartRate > 0)
    {
        snprintf(s.hr, sizeof(s.hr), "%u", (unsigned)d.heartRate);
    }
    else
    {
        strcpy(s.hr, "--");
    }
    snprintf(s.steps, sizeof(s.steps), "%u", (unsigned)d.steps);
    if (d.oxygen > 0)
    {
        snprintf(s.o2, sizeof(s.o2), "%u%%", (unsigned)d.oxygen);
    }
    else
    {
        strcpy(s.o2, "--");
    }
    if (d.battery >= 0)
    {
        snprintf(s.bat, sizeof(s.bat), "%d%%", (int)d.battery);
    }
    else
    {
        strcpy(s.bat, "--");
    }
    snprintf(s.alarm, sizeof(s.alarm), "%s", d.nextAlarm);
    strcpy(s.link, d.connected ? "LINK OK" : "NO LINK");
    snprintf(s.notif, sizeof(s.notif), "%u", (unsigned)d.notifCount);
    const uint32_t goal = d.stepGoal >= 1000 ? d.stepGoal : 10000;
    s.stepsPct = d.steps >= goal ? 100 : (int)((uint32_t)d.steps * 100 / goal);
    s.batPct = d.battery >= 0 ? d.battery : 0;
    s.secPct = (d.second > 59 ? 59 : d.second) * 100 / 59;
    s.o2Pct = d.oxygen > 100 ? 100 : d.oxygen;
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

lv_obj_t* mkText(lv_obj_t* parent, const lv_font_t* font, lv_color_t color, const char* text,
                 lv_align_t align, int x, int y)
{
    lv_obj_t* l = mkLabel(parent, font, color, text);
    lv_obj_align(l, align, x, y);
    return l;
}

lv_obj_t* tracked(lv_obj_t* label, int space)
{
    lv_obj_set_style_text_letter_space(label, space, 0);
    return label;
}

lv_obj_t* mkBox(lv_obj_t* parent, int x, int y, int w, int h, lv_color_t color, lv_opa_t opa, int radius)
{
    lv_obj_t* o = lv_obj_create(parent);
    lv_obj_remove_style_all(o);
    lv_obj_set_pos(o, x, y);
    lv_obj_set_size(o, w, h);
    lv_obj_set_style_bg_color(o, color, 0);
    lv_obj_set_style_bg_opa(o, opa, 0);
    lv_obj_set_style_radius(o, radius, 0);
    lv_obj_clear_flag(o, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_clear_flag(o, LV_OBJ_FLAG_CLICKABLE);
    return o;
}

void outline(lv_obj_t* o, int w, lv_color_t c, lv_opa_t opa)
{
    lv_obj_set_style_border_width(o, w, 0);
    lv_obj_set_style_border_color(o, c, 0);
    lv_obj_set_style_border_opa(o, opa, 0);
}

lv_obj_t* mkRing(lv_obj_t* p, int cx, int cy, int d, int w, lv_color_t c, lv_color_t track, lv_opa_t trackOpa)
{
    lv_obj_t* a = lv_arc_create(p);
    lv_obj_remove_style(a, nullptr, LV_PART_KNOB);
    lv_obj_clear_flag(a, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_size(a, d, d);
    lv_obj_set_pos(a, cx - d / 2, cy - d / 2);
    lv_arc_set_rotation(a, 270);
    lv_arc_set_bg_angles(a, 0, 360);
    lv_arc_set_range(a, 0, 100);
    lv_arc_set_value(a, 0);
    lv_obj_set_style_arc_width(a, w, LV_PART_MAIN);
    lv_obj_set_style_arc_width(a, w, LV_PART_INDICATOR);
    lv_obj_set_style_arc_color(a, track, LV_PART_MAIN);
    lv_obj_set_style_arc_opa(a, trackOpa, LV_PART_MAIN);
    lv_obj_set_style_arc_color(a, c, LV_PART_INDICATOR);
    lv_obj_set_style_arc_rounded(a, true, LV_PART_MAIN);
    lv_obj_set_style_arc_rounded(a, true, LV_PART_INDICATOR);
    return a;
}

// Bar digits: 7 rounded bars per digit, scalable to any size.
const uint8_t SEG_MASK[11] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x40};

void segBuild(Seg& g, lv_obj_t* p, int x, int y, int w, int h, int t, lv_color_t c)
{
    const int hh = (h - t) / 2;
    const int r = t / 2;
    g.s[0] = mkBox(p, x + t, y, w - 2 * t, t, c, LV_OPA_COVER, r);
    g.s[1] = mkBox(p, x + w - t, y + t / 2, t, hh, c, LV_OPA_COVER, r);
    g.s[2] = mkBox(p, x + w - t, y + hh + t / 2, t, hh, c, LV_OPA_COVER, r);
    g.s[3] = mkBox(p, x + t, y + h - t, w - 2 * t, t, c, LV_OPA_COVER, r);
    g.s[4] = mkBox(p, x, y + hh + t / 2, t, hh, c, LV_OPA_COVER, r);
    g.s[5] = mkBox(p, x, y + t / 2, t, hh, c, LV_OPA_COVER, r);
    g.s[6] = mkBox(p, x + t, y + hh, w - 2 * t, t, c, LV_OPA_COVER, r);
    g.shown = -2;
}

void segSet(Seg& g, int digit)
{
    if (g.shown == digit)
    {
        return;
    }
    g.shown = (int8_t)digit;
    const uint8_t m = SEG_MASK[(digit >= 0 && digit <= 9) ? digit : 10];
    for (int i = 0; i < 7; ++i)
    {
        if (g.s[i] != nullptr)
        {
            lv_obj_set_style_bg_opa(g.s[i], ((m >> i) & 1) ? LV_OPA_COVER : LV_OPA_TRANSP, 0);
        }
    }
}

// ------------------------------------------------------------ 1 Editorial
void editCol(lv_obj_t* p, int x, const char* cap, lv_obj_t** value, lv_color_t ink)
{
    tracked(mkText(p, LV_FONT_DEFAULT, ink, cap, LV_ALIGN_TOP_LEFT, x, 268), 1);
    *value = mkText(p, HOME_FONT_M, ink, "--", LV_ALIGN_TOP_LEFT, x, 286);
}

void buildEditorial(lv_obj_t* p)
{
    EditUI& u = edit;
    const lv_color_t ink = HEX(0x15130F), red = col.a1;
    lv_obj_set_style_bg_color(p, HEX(0xECE6DA), 0);

    u.date = tracked(mkText(p, LV_FONT_DEFAULT, ink, "", LV_ALIGN_TOP_LEFT, 20, 14), 2);
    u.link = tracked(mkText(p, LV_FONT_DEFAULT, ink, "", LV_ALIGN_TOP_RIGHT, -20, 14), 2);
    mkBox(p, 20, 36, 200, 1, ink, LV_OPA_COVER, 0);

    segBuild(u.h0, p, 20, 50, 56, 96, 12, ink);
    segBuild(u.h1, p, 88, 50, 56, 96, 12, ink);
    segBuild(u.m0, p, 20, 156, 56, 96, 12, red);
    segBuild(u.m1, p, 88, 156, 56, 96, 12, red);

    u.wd = tracked(mkText(p, HOME_FONT_M, ink, "", LV_ALIGN_TOP_LEFT, 164, 56), 2);
    u.dd = mkText(p, HOME_FONT_XL, ink, "", LV_ALIGN_TOP_LEFT, 164, 80);
    u.mon = tracked(mkText(p, HOME_FONT_M, red, "", LV_ALIGN_TOP_LEFT, 164, 140), 2);

    mkBox(p, 20, 262, 200, 1, ink, LV_OPA_COVER, 0);
    editCol(p, 20, "HEART", &u.hr, ink);
    editCol(p, 90, "STEPS", &u.steps, ink);
    editCol(p, 160, "PHONE", &u.bat, ink);
}

// ------------------------------------------------------------ 2 Bento
void bentoTile(lv_obj_t* p, int x, int y, int w, int h, lv_color_t bg, uint32_t fg, const char* cap,
               const lv_font_t* font, lv_obj_t** capLabel, lv_obj_t** value)
{
    mkBox(p, x, y, w, h, bg, LV_OPA_COVER, 20);
    lv_obj_t* c = tracked(mkText(p, LV_FONT_DEFAULT, HEX(fg), cap, LV_ALIGN_TOP_LEFT, x + 12, y + 8), 1);
    if (capLabel != nullptr)
    {
        *capLabel = c;
    }
    *value = mkText(p, font, HEX(fg), "--", LV_ALIGN_TOP_LEFT, x + 12, y + (h > 80 ? 30 : 26));
}

void buildBento(lv_obj_t* p)
{
    BentoUI& u = bento;
    lv_obj_set_style_bg_color(p, HEX(0x0E0E12), 0);
    bentoTile(p, 8, 8, 224, 96, col.a1, 0x101014, "", HOME_FONT_XL, &u.date, &u.time);
    bentoTile(p, 8, 112, 108, 70, col.a2, 0x101014, "HEART", HOME_FONT_L, nullptr, &u.hr);
    bentoTile(p, 124, 112, 108, 70, col.a3, 0x101014, "STEPS", HOME_FONT_L, nullptr, &u.steps);
    bentoTile(p, 8, 190, 108, 56, col.a4, 0x101014, "PHONE", HOME_FONT_M, nullptr, &u.bat);
    bentoTile(p, 124, 190, 108, 56, lv_color_mix(col.a1, col.a3, 128), 0x101014, "SPO2", HOME_FONT_M, nullptr, &u.o2);

    mkBox(p, 8, 254, 224, 58, HEX(0x1E1E26), LV_OPA_COVER, 20);
    u.wx = mkText(p, LV_FONT_DEFAULT, HEX(0xFFFFFF), "", LV_ALIGN_TOP_LEFT, 20, 264);
    u.alarm = mkText(p, LV_FONT_DEFAULT, HEX(0xB8B8C4), "", LV_ALIGN_TOP_LEFT, 20, 284);
    u.alerts = mkText(p, HOME_FONT_L, HEX(0xFFFFFF), "", LV_ALIGN_TOP_RIGHT, -20, 272);
}

// ------------------------------------------------------------ 3 Aura
void orb(lv_obj_t* p, int cx, int cy, int r, lv_color_t color)
{
    static const int PCT[4] = {100, 78, 56, 34};
    static const lv_opa_t OPA[4] = {18, 30, 44, 60};
    for (int i = 0; i < 4; ++i)
    {
        const int rr = r * PCT[i] / 100;
        mkBox(p, cx - rr, cy - rr, 2 * rr, 2 * rr, color, OPA[i], LV_RADIUS_CIRCLE);
    }
}

void buildAura(lv_obj_t* p)
{
    AuraUI& u = aura;
    const lv_color_t white = HEX(0xFFFFFF);
    lv_obj_set_style_bg_color(p, HEX(0x0B0A12), 0);
    orb(p, 60, 40, 105, col.a1);
    orb(p, 190, 180, 110, col.a2);
    orb(p, 70, 300, 110, col.a4);

    u.time = mkText(p, HOME_FONT_XL, white, "--:--", LV_ALIGN_TOP_MID, 0, 74);
    u.date = tracked(mkText(p, LV_FONT_DEFAULT, white, "", LV_ALIGN_TOP_MID, 0, 138), 3);
    u.wx = tracked(mkText(p, LV_FONT_DEFAULT, white, "", LV_ALIGN_TOP_MID, 0, 214), 2);

    lv_obj_t* pill = mkBox(p, 16, 252, 208, 52, white, 36, 26);
    outline(pill, 1, white, 90);
    u.hr = mkText(p, HOME_FONT_M, white, "--", LV_ALIGN_TOP_LEFT, 32, 267);
    u.steps = mkText(p, HOME_FONT_M, white, "--", LV_ALIGN_TOP_MID, 0, 267);
    u.bat = mkText(p, HOME_FONT_M, white, "--", LV_ALIGN_TOP_RIGHT, -32, 267);
}

// ------------------------------------------------------------ 4 Regulator
lv_obj_t* subDial(lv_obj_t* p, int x, int y, int d, const char* cap, const lv_font_t* font,
                  lv_obj_t** value, lv_color_t gold)
{
    lv_obj_t* ring = mkBox(p, x, y, d, d, gold, LV_OPA_TRANSP, LV_RADIUS_CIRCLE);
    outline(ring, 2, gold, LV_OPA_COVER);
    *value = mkText(ring, font, gold, "--", LV_ALIGN_CENTER, 0, -6);
    tracked(mkText(ring, LV_FONT_DEFAULT, gold, cap, LV_ALIGN_BOTTOM_MID, 0, -(d / 8)), 2);
    return ring;
}

void buildRegulator(lv_obj_t* p)
{
    RegUI& u = reg;
    const lv_color_t gold = col.a3;
    lv_obj_set_style_bg_color(p, lv_color_mix(col.a1, col.bg, 90), 0);
    lv_obj_set_style_bg_grad_color(p, lv_color_mix(col.a1, col.bg, 30), 0);
    lv_obj_set_style_bg_grad_dir(p, LV_GRAD_DIR_VER, 0);

    u.date = tracked(mkText(p, LV_FONT_DEFAULT, gold, "", LV_ALIGN_TOP_MID, 0, 14), 4);
    subDial(p, 60, 34, 120, "HOURS", HOME_FONT_XL, &u.hour, gold);
    subDial(p, 20, 170, 100, "MIN", HOME_FONT_L, &u.minute, gold);
    u.secArc = mkRing(p, 175, 215, 90, 4, gold, gold, 60);
    u.sec = mkText(p, HOME_FONT_M, gold, "--", LV_ALIGN_TOP_LEFT, 163, 200);
    tracked(mkText(p, LV_FONT_DEFAULT, gold, "SEC", LV_ALIGN_TOP_LEFT, 160, 226), 2);
    u.strip = tracked(mkText(p, LV_FONT_DEFAULT, gold, "", LV_ALIGN_BOTTOM_MID, 0, -18), 1);
}

// ------------------------------------------------------------ 5 Swiss
void buildSwiss(lv_obj_t* p)
{
    SwissUI& u = swiss;
    const lv_color_t ink = HEX(0x0A0A0A), red = col.a1, track = HEX(0xD6D6D0);
    lv_obj_set_style_bg_color(p, HEX(0xF4F4F0), 0);

    segBuild(u.h0, p, 14, 12, 100, 170, 26, ink);
    segBuild(u.h1, p, 126, 12, 100, 170, 26, ink);
    segBuild(u.m0, p, 16, 194, 20, 34, 7, ink);
    segBuild(u.m1, p, 46, 194, 20, 34, 7, ink);
    mkBox(p, 80, 208, 126, 6, ink, LV_OPA_COVER, 0);
    mkBox(p, 214, 206, 10, 10, red, LV_OPA_COVER, LV_RADIUS_CIRCLE);

    u.stepsLbl = tracked(mkText(p, LV_FONT_DEFAULT, ink, "", LV_ALIGN_TOP_LEFT, 16, 238), 2);
    mkBox(p, 16, 258, 208, 4, track, LV_OPA_COVER, 0);
    u.stepsFill = mkBox(p, 16, 258, 1, 4, red, LV_OPA_COVER, 0);
    u.batLbl = tracked(mkText(p, LV_FONT_DEFAULT, ink, "", LV_ALIGN_TOP_LEFT, 16, 268), 2);
    mkBox(p, 16, 288, 208, 4, track, LV_OPA_COVER, 0);
    u.batFill = mkBox(p, 16, 288, 1, 4, ink, LV_OPA_COVER, 0);
    u.foot = tracked(mkText(p, LV_FONT_DEFAULT, ink, "", LV_ALIGN_BOTTOM_LEFT, 16, -6), 2);
}

// ------------------------------------------------------------ 6 Liquid glass
void buildGlass(lv_obj_t* p)
{
    GlassUI& u = glass;
    const lv_color_t white = HEX(0xFFFFFF);
    lv_obj_set_style_bg_color(p, lv_color_mix(col.a1, col.bg, 60), 0);
    lv_obj_set_style_bg_grad_color(p, lv_color_mix(col.a2, col.bg, 60), 0);
    lv_obj_set_style_bg_grad_dir(p, LV_GRAD_DIR_VER, 0);

    u.wx = tracked(mkText(p, LV_FONT_DEFAULT, white, "", LV_ALIGN_TOP_MID, 0, 12), 2);
    u.r1 = mkRing(p, 120, 150, 210, 10, col.a1, white, 28);
    u.r2 = mkRing(p, 120, 150, 164, 10, col.a2, white, 28);
    u.r3 = mkRing(p, 120, 150, 118, 10, col.a4, white, 28);
    u.time = mkText(p, HOME_FONT_L, white, "--:--", LV_ALIGN_TOP_MID, 0, 132);
    u.date = tracked(mkText(p, LV_FONT_DEFAULT, white, "", LV_ALIGN_TOP_MID, 0, 168), 2);

    lv_obj_t* pill = mkBox(p, 14, 268, 212, 38, white, 40, 19);
    outline(pill, 1, white, 100);
    u.hr = mkText(p, LV_FONT_DEFAULT, white, "", LV_ALIGN_TOP_LEFT, 28, 279);
    u.o2 = mkText(p, LV_FONT_DEFAULT, white, "", LV_ALIGN_TOP_MID, 0, 279);
    u.alerts = mkText(p, LV_FONT_DEFAULT, white, "", LV_ALIGN_TOP_RIGHT, -28, 279);
}

void rebuild(uint8_t i)
{
    lv_obj_t* p = panels[i];
    if (p == nullptr)
    {
        return;
    }
    lv_obj_clean(p);
    lv_obj_set_style_bg_color(p, col.bg, 0);
    lv_obj_set_style_bg_opa(p, LV_OPA_COVER, 0);
    lv_obj_set_style_bg_grad_dir(p, LV_GRAD_DIR_NONE, 0);
    lv_obj_set_style_border_width(p, 0, 0);
    lv_obj_clear_flag(p, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_update_layout(p);

    switch (i)
    {
        case 0: buildEditorial(p); break;
        case 1: buildBento(p); break;
        case 2: buildAura(p); break;
        case 3: buildRegulator(p); break;
        case 4: buildSwiss(p); break;
        default: buildGlass(p); break;
    }
}
}  // namespace

void uiHomeExtBuild(lv_obj_t* panel, uint8_t kind, const HomeColors& colors)
{
    if (panel == nullptr || kind < HOME_FACE_BRUTALIST || kind >= HOME_FACE_TOTAL)
    {
        return;
    }
    col = colors;
    const uint8_t i = kind - HOME_FACE_BRUTALIST;
    panels[i] = panel;
    rebuild(i);
    if (haveCur)
    {
        uiHomeExtUpdate(cur);
    }
}

void uiHomeExtRecolor(const HomeColors& colors)
{
    col = colors;
    for (uint8_t i = 0; i < FACES; ++i)
    {
        rebuild(i);
    }
    if (haveCur)
    {
        uiHomeExtUpdate(cur);
    }
}

namespace
{
int dig(const HomeData& d, bool hour, bool tens)
{
    if (!d.timeValid)
    {
        return -1;
    }
    const int v = hour ? d.hour : d.minute;
    return tens ? v / 10 : v % 10;
}

void updEditorial(const HomeData& d, const Strs& s)
{
    EditUI& u = edit;
    segSet(u.h0, dig(d, true, true));
    segSet(u.h1, dig(d, true, false));
    segSet(u.m0, dig(d, false, true));
    segSet(u.m1, dig(d, false, false));
    setText(u.date, s.dateUp);
    setText(u.link, s.link);
    setText(u.wd, s.wd);
    setText(u.dd, s.dd);
    setText(u.mon, s.mon);
    setText(u.hr, s.hr);
    setText(u.steps, s.steps);
    setText(u.bat, s.bat);
}

void updBento(const Strs& s)
{
    BentoUI& u = bento;
    char b[48];
    setText(u.date, s.dateUp);
    setText(u.time, s.tm);
    setText(u.hr, s.hr);
    setText(u.steps, s.steps);
    setText(u.bat, s.bat);
    setText(u.o2, s.o2);
    setText(u.wx, s.wx);
    snprintf(b, sizeof(b), LV_SYMBOL_BELL " %s", s.alarm);
    setText(u.alarm, b);
    setText(u.alerts, s.notif);
}

void updAura(const Strs& s)
{
    AuraUI& u = aura;
    char b[24];
    setText(u.time, s.tm);
    setText(u.date, s.dateUp);
    setText(u.wx, s.wx);
    snprintf(b, sizeof(b), "%s bpm", s.hr);
    setText(u.hr, b);
    setText(u.steps, s.steps);
    setText(u.bat, s.bat);
}

void updRegulator(const Strs& s)
{
    RegUI& u = reg;
    char b[64];
    setText(u.date, s.dateUp);
    setText(u.hour, s.hh);
    setText(u.minute, s.mm);
    setText(u.sec, s.ss);
    if (u.secArc != nullptr)
    {
        lv_arc_set_value(u.secArc, s.secPct);
    }
    snprintf(b, sizeof(b), "%s BPM  /  %s STEPS  /  %s", s.hr, s.steps, s.bat);
    setText(u.strip, b);
}

void updSwiss(const HomeData& d, const Strs& s)
{
    SwissUI& u = swiss;
    char b[48];
    segSet(u.h0, dig(d, true, true));
    segSet(u.h1, dig(d, true, false));
    segSet(u.m0, dig(d, false, true));
    segSet(u.m1, dig(d, false, false));
    snprintf(b, sizeof(b), "STEPS %d%%", s.stepsPct);
    setText(u.stepsLbl, b);
    snprintf(b, sizeof(b), "PHONE %s", s.bat);
    setText(u.batLbl, b);
    if (u.stepsFill != nullptr)
    {
        lv_obj_set_width(u.stepsFill, 1 + s.stepsPct * 207 / 100);
    }
    if (u.batFill != nullptr)
    {
        lv_obj_set_width(u.batFill, 1 + s.batPct * 207 / 100);
    }
    snprintf(b, sizeof(b), "%s   %s BPM", s.dateUp, s.hr);
    setText(u.foot, b);
}

void updGlass(const Strs& s)
{
    GlassUI& u = glass;
    char b[40];
    setText(u.wx, s.wx);
    setText(u.time, s.tm);
    setText(u.date, s.dateUp);
    if (u.r1 != nullptr)
    {
        lv_arc_set_value(u.r1, s.stepsPct);
    }
    if (u.r2 != nullptr)
    {
        lv_arc_set_value(u.r2, s.batPct);
    }
    if (u.r3 != nullptr)
    {
        lv_arc_set_value(u.r3, s.o2Pct);
    }
    snprintf(b, sizeof(b), "%s bpm", s.hr);
    setText(u.hr, b);
    snprintf(b, sizeof(b), "%s O2", s.o2);
    setText(u.o2, b);
    snprintf(b, sizeof(b), LV_SYMBOL_ENVELOPE " %s", s.notif);
    setText(u.alerts, b);
}
}  // namespace

void uiHomeExtUpdate(const HomeData& d)
{
    cur = d;
    haveCur = true;
    Strs s;
    makeStrs(d, s);
    if (panels[0] != nullptr) updEditorial(d, s);
    if (panels[1] != nullptr) updBento(s);
    if (panels[2] != nullptr) updAura(s);
    if (panels[3] != nullptr) updRegulator(s);
    if (panels[4] != nullptr) updSwiss(d, s);
    if (panels[5] != nullptr) updGlass(s);
}
