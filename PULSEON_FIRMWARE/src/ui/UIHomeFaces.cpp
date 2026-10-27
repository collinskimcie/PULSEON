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

namespace
{
constexpr uint8_t FACES = 6;
HomeColors col;
HomeData cur;
bool haveCur = false;
lv_obj_t* panels[FACES] = {};

struct BrutUI
{
    lv_obj_t *date, *link, *hour, *minute, *hr, *steps, *stepsFill, *bat, *batFill, *wx, *alarm;
};
struct DotUI
{
    lv_obj_t* dots[4][7][5];
    lv_obj_t* colon[2];
    int8_t shown[4];
    lv_obj_t *date, *wx, *hr, *steps, *o2, *bat;
    lv_obj_t* stepSq[20];
    lv_obj_t* batSq[10];
};
struct TopoUI
{
    lv_obj_t *arc, *time, *date, *hr, *wx, *link, *bat, *o2, *alarm;
};
struct GlassUI
{
    lv_obj_t *time, *date, *hr, *steps, *bat, *o2, *strip;
};
struct CircuitUI
{
    lv_obj_t *time, *date, *link, *hr, *steps, *bat, *o2, *wx, *alarm;
};
struct PrismUI
{
    lv_obj_t *t0, *t1, *t2, *date, *hr, *o2, *steps, *strip;
};
BrutUI brut = {};
DotUI dotUi = {};
TopoUI topoUi = {};
GlassUI glassUi = {};
CircuitUI circuitUi = {};
PrismUI prismUi = {};

const char* const DAYS[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
const char* const MONTHS[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                                "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

struct Strs
{
    char tm[8], hh[4], mm[4], date[24], temp[12], wx[40], hr[8], steps[8];
    char o2[8], bat[8], alarm[8], link[10], notif[8];
    int stepsPct, batPct;
};

void makeStrs(const HomeData& d, Strs& s)
{
    if (d.timeValid)
    {
        snprintf(s.tm, sizeof(s.tm), "%02d:%02d", (int)d.hour, (int)d.minute);
        snprintf(s.hh, sizeof(s.hh), "%02d", (int)d.hour);
        snprintf(s.mm, sizeof(s.mm), "%02d", (int)d.minute);
        snprintf(s.date, sizeof(s.date), "%s %d %s", DAYS[d.weekday % 7], (int)d.day,
                 MONTHS[(d.month >= 1 && d.month <= 12) ? d.month - 1 : 0]);
    }
    else
    {
        strcpy(s.tm, "--:--");
        strcpy(s.hh, "--");
        strcpy(s.mm, "--");
        strcpy(s.date, "-- -- --");
    }
    if (d.hasTemp)
    {
        snprintf(s.temp, sizeof(s.temp), "%d\xC2\xB0", (int)d.tempC);
    }
    else
    {
        strcpy(s.temp, "--");
    }
    snprintf(s.wx, sizeof(s.wx), "%s %s", s.temp, d.weather);
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
    s.stepsPct = d.steps >= 10000 ? 100 : d.steps / 100;
    s.batPct = d.battery >= 0 ? d.battery : 0;
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

// ------------------------------------------------------------ Brutalist
void brutRow(lv_obj_t* p, int y, const char* tag, lv_color_t accent, lv_obj_t** fill, lv_obj_t** value)
{
    lv_obj_t* row = mkBox(p, 6, y, 228, 40, col.card, LV_OPA_COVER, 0);
    outline(row, 3, accent, LV_OPA_COVER);
    if (fill != nullptr)
    {
        *fill = mkBox(row, 52, 0, 1, 34, accent, LV_OPA_50, 0);
    }
    mkBox(row, 0, 0, 52, 34, accent, LV_OPA_COVER, 0);
    mkText(row, LV_FONT_DEFAULT, col.bg, tag, LV_ALIGN_LEFT_MID, 6, 0);
    *value = mkText(row, HOME_FONT_L, col.text, "--", LV_ALIGN_LEFT_MID, 62, 0);
}

void buildBrutal(lv_obj_t* p)
{
    BrutUI& u = brut;
    mkBox(p, 0, 0, 240, 34, col.a1, LV_OPA_COVER, 0);
    u.date = mkText(p, LV_FONT_DEFAULT, col.bg, "", LV_ALIGN_TOP_LEFT, 10, 10);
    u.link = mkText(p, LV_FONT_DEFAULT, col.bg, "", LV_ALIGN_TOP_RIGHT, -10, 10);

    lv_obj_t* hb = mkBox(p, 6, 44, 112, 96, col.a1, LV_OPA_COVER, 0);
    lv_obj_t* mb = mkBox(p, 122, 44, 112, 96, col.card, LV_OPA_COVER, 0);
    outline(mb, 3, col.a1, LV_OPA_COVER);
    u.hour = mkText(hb, HOME_FONT_XL, col.bg, "--", LV_ALIGN_CENTER, 0, 0);
    u.minute = mkText(mb, HOME_FONT_XL, col.text, "--", LV_ALIGN_CENTER, 0, 0);

    brutRow(p, 150, "HR", col.a3, nullptr, &u.hr);
    brutRow(p, 196, "STEPS", col.a2, &u.stepsFill, &u.steps);
    brutRow(p, 242, "PHONE", col.a4, &u.batFill, &u.bat);

    u.wx = mkText(p, LV_FONT_DEFAULT, col.dim, "", LV_ALIGN_BOTTOM_LEFT, 8, -10);
    u.alarm = mkText(p, LV_FONT_DEFAULT, col.a1, "", LV_ALIGN_BOTTOM_RIGHT, -8, -10);
}

// ------------------------------------------------------------ Dot matrix
const uint8_t DOT_FONT[11][7] = {
    {0x0E, 0x11, 0x13, 0x15, 0x19, 0x11, 0x0E},  // 0
    {0x04, 0x0C, 0x04, 0x04, 0x04, 0x04, 0x0E},  // 1
    {0x0E, 0x11, 0x01, 0x02, 0x04, 0x08, 0x1F},  // 2
    {0x1F, 0x02, 0x04, 0x02, 0x01, 0x11, 0x0E},  // 3
    {0x02, 0x06, 0x0A, 0x12, 0x1F, 0x02, 0x02},  // 4
    {0x1F, 0x10, 0x1E, 0x01, 0x01, 0x11, 0x0E},  // 5
    {0x06, 0x08, 0x10, 0x1E, 0x11, 0x11, 0x0E},  // 6
    {0x1F, 0x01, 0x02, 0x04, 0x08, 0x08, 0x08},  // 7
    {0x0E, 0x11, 0x11, 0x0E, 0x11, 0x11, 0x0E},  // 8
    {0x0E, 0x11, 0x11, 0x0F, 0x01, 0x02, 0x0C},  // 9
    {0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00}   // dash (clock not synced)
};
const int DOT_X[4] = {8, 62, 134, 188};

void dotRow(lv_obj_t* p, int y, const char* tag, lv_obj_t** value, lv_color_t dim)
{
    mkText(p, LV_FONT_DEFAULT, dim, tag, LV_ALIGN_TOP_LEFT, 12, y + 8);
    *value = mkText(p, HOME_FONT_L, col.a3, "--", LV_ALIGN_TOP_RIGHT, -12, y);
}

void buildDot(lv_obj_t* p)
{
    DotUI& u = dotUi;
    memset(&u, 0, sizeof(u));
    const lv_color_t dim = lv_color_mix(col.a3, col.bg, 150);

    for (int d = 0; d < 4; ++d)
    {
        u.shown[d] = -2;
        for (int r = 0; r < 7; ++r)
        {
            for (int c = 0; c < 5; ++c)
            {
                u.dots[d][r][c] = mkBox(p, DOT_X[d] + c * 9, 44 + r * 9, 7, 7, col.a3,
                                        LV_OPA_10, LV_RADIUS_CIRCLE);
            }
        }
    }
    u.colon[0] = mkBox(p, 116, 44 + 2 * 9, 7, 7, col.a3, LV_OPA_COVER, LV_RADIUS_CIRCLE);
    u.colon[1] = mkBox(p, 116, 44 + 4 * 9, 7, 7, col.a3, LV_OPA_COVER, LV_RADIUS_CIRCLE);

    u.date = mkText(p, LV_FONT_DEFAULT, dim, "", LV_ALIGN_TOP_LEFT, 12, 122);
    u.wx = mkText(p, LV_FONT_DEFAULT, dim, "", LV_ALIGN_TOP_RIGHT, -12, 122);

    dotRow(p, 148, "HEART", &u.hr, dim);
    dotRow(p, 180, "STEPS", &u.steps, dim);
    for (int i = 0; i < 20; ++i)
    {
        u.stepSq[i] = mkBox(p, 12 + i * 11, 214, 8, 6, col.a3, LV_OPA_20, 1);
    }
    dotRow(p, 234, "SPO2", &u.o2, dim);
    dotRow(p, 266, "PHONE", &u.bat, dim);
    for (int i = 0; i < 10; ++i)
    {
        u.batSq[i] = mkBox(p, 12 + i * 22, 300, 19, 6, col.a3, LV_OPA_20, 1);
    }
}

// ------------------------------------------------------------ Topo
void buildTopo(lv_obj_t* p)
{
    TopoUI& u = topoUi;
    static const int CW[5] = {232, 206, 178, 150, 124};
    static const int CH[5] = {232, 218, 184, 160, 128};
    static const int OX[5] = {0, 5, -6, 4, -3};
    static const int OY[5] = {0, -4, 5, -3, 4};
    for (int i = 0; i < 5; ++i)
    {
        lv_obj_t* ring = mkBox(p, 0, 0, CW[i], CH[i], col.bg, LV_OPA_TRANSP, LV_RADIUS_CIRCLE);
        outline(ring, 1, col.dim, LV_OPA_60);
        lv_obj_align(ring, LV_ALIGN_CENTER, OX[i], OY[i]);
    }
    u.arc = mkArc(p, 226, 7, col.a1, 100);
    u.time = mkText(p, HOME_FONT_XL, col.text, "--:--", LV_ALIGN_CENTER, 0, -20);
    u.date = mkText(p, LV_FONT_DEFAULT, col.dim, "", LV_ALIGN_CENTER, 0, 14);
    u.hr = mkText(p, HOME_FONT_M, col.a2, "-- bpm", LV_ALIGN_CENTER, 0, 40);
    u.wx = mkText(p, LV_FONT_DEFAULT, col.a1, "", LV_ALIGN_TOP_LEFT, 14, 14);
    u.link = mkText(p, LV_FONT_DEFAULT, col.a3, "", LV_ALIGN_TOP_RIGHT, -14, 14);
    u.bat = mkText(p, LV_FONT_DEFAULT, col.a4, "", LV_ALIGN_BOTTOM_LEFT, 14, -14);
    u.o2 = mkText(p, LV_FONT_DEFAULT, col.a2, "", LV_ALIGN_BOTTOM_MID, 0, -14);
    u.alarm = mkText(p, LV_FONT_DEFAULT, col.a3, "", LV_ALIGN_BOTTOM_RIGHT, -14, -14);
}

// ------------------------------------------------------------ Glassmorph
void glassCard(lv_obj_t* p, int x, int y, int w, int h, int radius)
{
    lv_obj_t* c = mkBox(p, x, y, w, h, col.text, LV_OPA_20, radius);
    outline(c, 1, col.text, LV_OPA_40);
}

void glassMetric(lv_obj_t* p, int x, int y, const char* cap, lv_color_t accent, lv_obj_t** value)
{
    glassCard(p, x, y, 104, 64, 20);
    mkText(p, LV_FONT_DEFAULT, accent, cap, LV_ALIGN_TOP_LEFT, x + 14, y + 10);
    *value = mkText(p, HOME_FONT_L, col.text, "--", LV_ALIGN_TOP_LEFT, x + 14, y + 28);
}

void buildGlass(lv_obj_t* p)
{
    GlassUI& u = glassUi;
    mkBox(p, -40, 10, 170, 170, col.a1, 90, LV_RADIUS_CIRCLE);
    mkBox(p, 110, 120, 150, 150, col.a2, 90, LV_RADIUS_CIRCLE);
    mkBox(p, -10, 190, 140, 140, col.a3, 80, LV_RADIUS_CIRCLE);
    mkBox(p, 150, -30, 120, 120, col.a4, 70, LV_RADIUS_CIRCLE);

    glassCard(p, 12, 22, 216, 104, 24);
    u.time = mkText(p, HOME_FONT_XL, col.text, "--:--", LV_ALIGN_TOP_MID, 0, 36);
    u.date = mkText(p, LV_FONT_DEFAULT, col.text, "", LV_ALIGN_TOP_MID, 0, 98);

    glassMetric(p, 12, 138, "HEART RATE", col.a4, &u.hr);
    glassMetric(p, 124, 138, "STEPS", col.a3, &u.steps);
    glassMetric(p, 12, 210, "PHONE", col.a2, &u.bat);
    glassMetric(p, 124, 210, "SPO2", col.a1, &u.o2);

    glassCard(p, 12, 282, 216, 30, 15);
    u.strip = mkText(p, LV_FONT_DEFAULT, col.text, "", LV_ALIGN_TOP_MID, 0, 289);
}

// ------------------------------------------------------------ Circuit blueprint
void circuitModule(lv_obj_t* p, int x, const char* cap, lv_color_t accent, lv_obj_t** value)
{
    lv_obj_t* m = mkBox(p, x, 204, 68, 64, col.card, LV_OPA_COVER, 6);
    outline(m, 1, accent, LV_OPA_COVER);
    mkBox(p, x + 33, 144, 2, 60, accent, LV_OPA_COVER, 0);
    mkBox(p, x + 29, 140, 10, 10, accent, LV_OPA_COVER, LV_RADIUS_CIRCLE);
    mkText(m, LV_FONT_DEFAULT, accent, cap, LV_ALIGN_TOP_LEFT, 6, 6);
    *value = mkText(m, HOME_FONT_M, col.text, "--", LV_ALIGN_BOTTOM_LEFT, 6, -8);
}

void buildCircuit(lv_obj_t* p)
{
    CircuitUI& u = circuitUi;
    for (int k = 1; k < 10; ++k)
    {
        mkBox(p, 24 * k, 0, 1, 320, col.dim, LV_OPA_20, 0);
    }
    for (int k = 1; k < 14; ++k)
    {
        mkBox(p, 0, 24 * k, 240, 1, col.dim, LV_OPA_20, 0);
    }
    mkText(p, LV_FONT_DEFAULT, col.a1, "PULSEON // SYS", LV_ALIGN_TOP_LEFT, 12, 12);
    u.link = mkText(p, LV_FONT_DEFAULT, col.a3, "", LV_ALIGN_TOP_RIGHT, -12, 12);

    for (int i = 0; i < 6; ++i)
    {
        mkBox(p, 32 + i * 32, 34, 8, 8, col.a1, LV_OPA_COVER, 1);
    }
    lv_obj_t* cpu = mkBox(p, 16, 40, 208, 100, col.card, LV_OPA_COVER, 6);
    outline(cpu, 2, col.a1, LV_OPA_COVER);
    u.time = mkText(cpu, HOME_FONT_XL, col.text, "--:--", LV_ALIGN_CENTER, 0, -10);
    u.date = mkText(cpu, LV_FONT_DEFAULT, col.dim, "", LV_ALIGN_BOTTOM_MID, 0, -6);

    circuitModule(p, 14, "HR", col.a2, &u.hr);
    circuitModule(p, 88, "STEPS", col.a3, &u.steps);
    circuitModule(p, 162, "PHONE", col.a4, &u.bat);

    lv_obj_t* bar = mkBox(p, 14, 278, 212, 30, col.card, LV_OPA_COVER, 6);
    outline(bar, 1, col.dim, LV_OPA_COVER);
    u.o2 = mkText(bar, LV_FONT_DEFAULT, col.a1, "", LV_ALIGN_LEFT_MID, 8, 0);
    u.wx = mkText(bar, LV_FONT_DEFAULT, col.text, "", LV_ALIGN_CENTER, 0, 0);
    u.alarm = mkText(bar, LV_FONT_DEFAULT, col.a3, "", LV_ALIGN_RIGHT_MID, -8, 0);
}

// ------------------------------------------------------------ Holographic prism
void prismPill(lv_obj_t* p, int y, const char* tag, lv_color_t accent, lv_obj_t** value)
{
    lv_obj_t* pill = mkBox(p, 12, y, 216, 34, col.card, 170, 17);
    outline(pill, 1, accent, LV_OPA_COVER);
    mkText(pill, LV_FONT_DEFAULT, accent, tag, LV_ALIGN_LEFT_MID, 12, 0);
    *value = mkText(pill, HOME_FONT_M, col.text, "--", LV_ALIGN_RIGHT_MID, -14, 0);
}

void buildPrism(lv_obj_t* p)
{
    PrismUI& u = prismUi;
    lv_obj_set_style_bg_color(p, col.bg, 0);
    lv_obj_set_style_bg_grad_color(p, lv_color_mix(col.a1, col.bg, 90), 0);
    lv_obj_set_style_bg_grad_dir(p, LV_GRAD_DIR_VER, 0);

    const lv_color_t band[4] = {col.a1, col.a2, col.a3, col.a4};
    for (int i = 0; i < 8; ++i)
    {
        mkBox(p, i * 30, 0, 30, 320, band[i % 4], 26, 0);
    }
    u.t0 = mkText(p, HOME_FONT_XL, col.a4, "--:--", LV_ALIGN_TOP_MID, 3, 62);
    u.t1 = mkText(p, HOME_FONT_XL, col.a2, "--:--", LV_ALIGN_TOP_MID, -3, 62);
    u.t2 = mkText(p, HOME_FONT_XL, col.text, "--:--", LV_ALIGN_TOP_MID, 0, 62);
    u.date = mkText(p, LV_FONT_DEFAULT, col.dim, "", LV_ALIGN_TOP_MID, 0, 126);

    prismPill(p, 158, "HEART", col.a4, &u.hr);
    prismPill(p, 198, "SPO2", col.a2, &u.o2);
    prismPill(p, 238, "STEPS", col.a1, &u.steps);

    lv_obj_t* strip = mkBox(p, 12, 282, 216, 30, col.card, 170, 15);
    outline(strip, 1, col.dim, LV_OPA_COVER);
    u.strip = mkText(strip, LV_FONT_DEFAULT, col.text, "", LV_ALIGN_CENTER, 0, 0);
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
        case 0: buildBrutal(p); break;
        case 1: buildDot(p); break;
        case 2: buildTopo(p); break;
        case 3: buildGlass(p); break;
        case 4: buildCircuit(p); break;
        default: buildPrism(p); break;
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
void updBrut(const Strs& s)
{
    BrutUI& u = brut;
    char b[28];
    setText(u.date, s.date);
    setText(u.link, s.link);
    setText(u.hour, s.hh);
    setText(u.minute, s.mm);
    snprintf(b, sizeof(b), "%s BPM", s.hr);
    setText(u.hr, b);
    setText(u.steps, s.steps);
    setText(u.bat, s.bat);
    if (u.stepsFill != nullptr)
    {
        lv_obj_set_width(u.stepsFill, 1 + s.stepsPct * 169 / 100);
    }
    if (u.batFill != nullptr)
    {
        lv_obj_set_width(u.batFill, 1 + s.batPct * 169 / 100);
    }
    setText(u.wx, s.wx);
    snprintf(b, sizeof(b), LV_SYMBOL_BELL " %s", s.alarm);
    setText(u.alarm, b);
}

void updDot(const HomeData& d, const Strs& s)
{
    DotUI& u = dotUi;
    int digit[4];
    if (d.timeValid)
    {
        digit[0] = d.hour / 10;
        digit[1] = d.hour % 10;
        digit[2] = d.minute / 10;
        digit[3] = d.minute % 10;
    }
    else
    {
        digit[0] = digit[1] = digit[2] = digit[3] = 10;
    }
    for (int i = 0; i < 4; ++i)
    {
        if (u.shown[i] == digit[i])
        {
            continue;
        }
        u.shown[i] = (int8_t)digit[i];
        for (int r = 0; r < 7; ++r)
        {
            for (int c = 0; c < 5; ++c)
            {
                const bool lit = ((DOT_FONT[digit[i]][r] >> (4 - c)) & 1) != 0;
                if (u.dots[i][r][c] != nullptr)
                {
                    lv_obj_set_style_bg_opa(u.dots[i][r][c], lit ? LV_OPA_COVER : LV_OPA_10, 0);
                }
            }
        }
    }
    const bool colonOn = !d.timeValid || (d.second % 2 == 0);
    for (int i = 0; i < 2; ++i)
    {
        if (u.colon[i] != nullptr)
        {
            lv_obj_set_style_bg_opa(u.colon[i], colonOn ? LV_OPA_COVER : LV_OPA_20, 0);
        }
    }
    setText(u.date, s.date);
    setText(u.wx, s.wx);
    setText(u.hr, s.hr);
    setText(u.steps, s.steps);
    setText(u.o2, s.o2);
    setText(u.bat, s.bat);
    const int stepsLit = s.stepsPct * 20 / 100;
    const int batLit = (s.batPct + 5) / 10;
    for (int i = 0; i < 20; ++i)
    {
        if (u.stepSq[i] != nullptr)
        {
            lv_obj_set_style_bg_opa(u.stepSq[i], i < stepsLit ? LV_OPA_COVER : LV_OPA_20, 0);
        }
    }
    for (int i = 0; i < 10; ++i)
    {
        if (u.batSq[i] != nullptr)
        {
            lv_obj_set_style_bg_opa(u.batSq[i], i < batLit ? LV_OPA_COVER : LV_OPA_20, 0);
        }
    }
}

void updTopo(const Strs& s)
{
    TopoUI& u = topoUi;
    char b[28];
    if (u.arc != nullptr)
    {
        lv_arc_set_value(u.arc, s.stepsPct);
    }
    setText(u.time, s.tm);
    setText(u.date, s.date);
    snprintf(b, sizeof(b), "%s bpm", s.hr);
    setText(u.hr, b);
    setText(u.wx, s.wx);
    setText(u.link, s.link);
    snprintf(b, sizeof(b), LV_SYMBOL_BATTERY_3 " %s", s.bat);
    setText(u.bat, b);
    snprintf(b, sizeof(b), "O2 %s", s.o2);
    setText(u.o2, b);
    snprintf(b, sizeof(b), LV_SYMBOL_BELL " %s", s.alarm);
    setText(u.alarm, b);
}

void updGlass(const Strs& s)
{
    GlassUI& u = glassUi;
    char b[96];
    setText(u.time, s.tm);
    setText(u.date, s.date);
    setText(u.hr, s.hr);
    setText(u.steps, s.steps);
    setText(u.bat, s.bat);
    setText(u.o2, s.o2);
    snprintf(b, sizeof(b), "%s   " LV_SYMBOL_BELL " %s   " LV_SYMBOL_ENVELOPE " %s",
             s.wx, s.alarm, s.notif);
    setText(u.strip, b);
}

void updCircuit(const Strs& s)
{
    CircuitUI& u = circuitUi;
    char b[24];
    setText(u.time, s.tm);
    setText(u.date, s.date);
    setText(u.link, s.link);
    setText(u.hr, s.hr);
    setText(u.steps, s.steps);
    setText(u.bat, s.bat);
    snprintf(b, sizeof(b), "O2 %s", s.o2);
    setText(u.o2, b);
    setText(u.wx, s.temp);
    snprintf(b, sizeof(b), LV_SYMBOL_BELL " %s", s.alarm);
    setText(u.alarm, b);
}

void updPrism(const Strs& s)
{
    PrismUI& u = prismUi;
    char b[96];
    setText(u.t0, s.tm);
    setText(u.t1, s.tm);
    setText(u.t2, s.tm);
    snprintf(b, sizeof(b), "%s  |  %s", s.date, s.link);
    setText(u.date, b);
    snprintf(b, sizeof(b), "%s bpm", s.hr);
    setText(u.hr, b);
    setText(u.o2, s.o2);
    snprintf(b, sizeof(b), "%s steps", s.steps);
    setText(u.steps, b);
    snprintf(b, sizeof(b), "%s   " LV_SYMBOL_BELL " %s   " LV_SYMBOL_ENVELOPE " %s",
             s.wx, s.alarm, s.notif);
    setText(u.strip, b);
}
}  // namespace

void uiHomeExtUpdate(const HomeData& d)
{
    cur = d;
    haveCur = true;
    Strs s;
    makeStrs(d, s);
    if (panels[0] != nullptr) updBrut(s);
    if (panels[1] != nullptr) updDot(d, s);
    if (panels[2] != nullptr) updTopo(s);
    if (panels[3] != nullptr) updGlass(s);
    if (panels[4] != nullptr) updCircuit(s);
    if (panels[5] != nullptr) updPrism(s);
}
