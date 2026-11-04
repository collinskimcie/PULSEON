#include "UIHomeNew.h"

#include <math.h>
#include <stdio.h>
#include <string.h>

#if LV_FONT_MONTSERRAT_48
#define NF_XL (&lv_font_montserrat_48)
#elif LV_FONT_MONTSERRAT_40
#define NF_XL (&lv_font_montserrat_40)
#elif LV_FONT_MONTSERRAT_32
#define NF_XL (&lv_font_montserrat_32)
#else
#define NF_XL LV_FONT_DEFAULT
#endif

#if LV_FONT_MONTSERRAT_20
#define NF_M (&lv_font_montserrat_20)
#elif LV_FONT_MONTSERRAT_18
#define NF_M (&lv_font_montserrat_18)
#elif LV_FONT_MONTSERRAT_16
#define NF_M (&lv_font_montserrat_16)
#else
#define NF_M LV_FONT_DEFAULT
#endif

#if LV_FONT_MONTSERRAT_14
#define NF_S (&lv_font_montserrat_14)
#elif LV_FONT_MONTSERRAT_12
#define NF_S (&lv_font_montserrat_12)
#else
#define NF_S LV_FONT_DEFAULT
#endif

#define HEX(v) lv_color_hex(v)

namespace
{
const float PI_F = 3.14159265f;

HomeColors col;
HomeData cur;
bool haveCur = false;
lv_obj_t* panels[NEW_FACE_COUNT] = {};

const char* const DAYS[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
const char* const DAYSU[7] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};
const char* const MONTHS[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                                "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

int clampi(int v, int lo, int hi)
{
    return v < lo ? lo : (v > hi ? hi : v);
}

void setPt(lv_point_precise_t& p, float x, float y)
{
    p.x = (lv_value_precise_t)x;
    p.y = (lv_value_precise_t)y;
}

void prep(lv_obj_t* p, lv_color_t bg)
{
    lv_obj_set_style_pad_all(p, 0, 0);
    lv_obj_set_style_bg_color(p, bg, 0);
    lv_obj_set_style_bg_opa(p, LV_OPA_COVER, 0);
    lv_obj_remove_flag(p, LV_OBJ_FLAG_SCROLLABLE);
}

lv_obj_t* box(lv_obj_t* p, int x, int y, int w, int h, int r, lv_color_t c)
{
    lv_obj_t* o = lv_obj_create(p);
    lv_obj_remove_style_all(o);
    lv_obj_set_pos(o, x, y);
    lv_obj_set_size(o, w, h);
    lv_obj_set_style_radius(o, r, 0);
    lv_obj_set_style_bg_color(o, c, 0);
    lv_obj_set_style_bg_opa(o, LV_OPA_COVER, 0);
    lv_obj_remove_flag(o, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_remove_flag(o, LV_OBJ_FLAG_CLICKABLE);
    return o;
}

lv_obj_t* lbl(lv_obj_t* p, const lv_font_t* f, lv_color_t c, int cx, int y, int w, const char* t)
{
    lv_obj_t* l = lv_label_create(p);
    lv_obj_set_width(l, w);
    lv_obj_set_pos(l, cx - w / 2, y);
    lv_obj_set_style_text_font(l, f, 0);
    lv_obj_set_style_text_color(l, c, 0);
    lv_obj_set_style_text_align(l, LV_TEXT_ALIGN_CENTER, 0);
    lv_label_set_text(l, t);
    return l;
}

lv_obj_t* line(lv_obj_t* p, lv_point_precise_t* pts, int w, lv_color_t c, bool round)
{
    lv_obj_t* l = lv_line_create(p);
    lv_line_set_points(l, pts, 2);
    lv_obj_set_style_line_width(l, w, 0);
    lv_obj_set_style_line_color(l, c, 0);
    lv_obj_set_style_line_rounded(l, round, 0);
    return l;
}

void styleArc(lv_obj_t* a, int w, lv_color_t c, lv_color_t track)
{
    lv_obj_remove_style(a, nullptr, LV_PART_KNOB);
    lv_obj_remove_flag(a, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_bg_opa(a, LV_OPA_TRANSP, LV_PART_MAIN);
    lv_obj_set_style_pad_all(a, 0, 0);
    lv_obj_set_style_arc_width(a, w, LV_PART_MAIN);
    lv_obj_set_style_arc_color(a, track, LV_PART_MAIN);
    lv_obj_set_style_arc_rounded(a, true, LV_PART_MAIN);
    lv_obj_set_style_arc_width(a, w, LV_PART_INDICATOR);
    lv_obj_set_style_arc_color(a, c, LV_PART_INDICATOR);
    lv_obj_set_style_arc_rounded(a, true, LV_PART_INDICATOR);
}

void fmtTime(const HomeData& d, char* out, size_t n)
{
    if (d.timeValid)
    {
        snprintf(out, n, "%02d:%02d", (int)d.hour, (int)d.minute);
    }
    else
    {
        snprintf(out, n, "--:--");
    }
}

// ============================ ANALOG ============================
struct AnalogUI
{
    lv_obj_t *hour, *min, *sec, *wd, *dm, *steps;
    lv_point_precise_t hp[2], mp[2], sp[2];
    lv_point_precise_t tk[60][2];
};
AnalogUI an = {};

const int AN_CX = 120;
const int AN_CY = 128;

void hand(lv_point_precise_t* pts, float deg, float len, float tail)
{
    const float a = deg * PI_F / 180.0f;
    const float sx = sinf(a);
    const float cx = cosf(a);
    setPt(pts[0], AN_CX - tail * sx, AN_CY + tail * cx);
    setPt(pts[1], AN_CX + len * sx, AN_CY - len * cx);
}

void analogUpdate(const HomeData& d)
{
    if (!an.hour)
    {
        return;
    }
    const float s = d.timeValid ? (float)d.second : 0.0f;
    const float m = (d.timeValid ? (float)d.minute : 0.0f) + s / 60.0f;
    const float h = (d.timeValid ? (float)(d.hour % 12) : 0.0f) + m / 60.0f;
    hand(an.hp, h * 30.0f, 52, 0);
    hand(an.mp, m * 6.0f, 84, 0);
    hand(an.sp, s * 6.0f, 92, 20);
    lv_line_set_points(an.hour, an.hp, 2);
    lv_line_set_points(an.min, an.mp, 2);
    lv_line_set_points(an.sec, an.sp, 2);

    char b[24];
    if (d.timeValid)
    {
        lv_label_set_text(an.wd, DAYSU[d.weekday % 7]);
        snprintf(b, sizeof(b), "%d %s", (int)d.day, MONTHS[(d.month >= 1 && d.month <= 12) ? d.month - 1 : 0]);
        lv_label_set_text(an.dm, b);
    }
    else
    {
        lv_label_set_text(an.wd, "---");
        lv_label_set_text(an.dm, "--");
    }
    snprintf(b, sizeof(b), "%u", (unsigned)d.steps);
    lv_label_set_text(an.steps, b);
}

void analogBuild(lv_obj_t* panel)
{
    an = AnalogUI{};
    prep(panel, col.bg);

    for (int i = 0; i < 60; ++i)
    {
        const float a = (float)i * 6.0f * PI_F / 180.0f;
        const bool hr = (i % 5 == 0);
        const float r1 = hr ? 94.0f : 102.0f;
        const float r2 = 108.0f;
        setPt(an.tk[i][0], AN_CX + r1 * sinf(a), AN_CY - r1 * cosf(a));
        setPt(an.tk[i][1], AN_CX + r2 * sinf(a), AN_CY - r2 * cosf(a));
        line(panel, an.tk[i], hr ? 3 : 1, hr ? col.text : col.dim, false);
    }

    lbl(panel, NF_M, col.text, AN_CX, AN_CY - 82, 30, "12");
    lbl(panel, NF_M, col.text, AN_CX + 72, AN_CY - 12, 30, "3");
    lbl(panel, NF_M, col.text, AN_CX, AN_CY + 58, 30, "6");
    lbl(panel, NF_M, col.text, AN_CX - 72, AN_CY - 12, 30, "9");

    hand(an.hp, 0, 52, 0);
    hand(an.mp, 0, 84, 0);
    hand(an.sp, 0, 92, 20);
    an.hour = line(panel, an.hp, 6, col.text, true);
    an.min = line(panel, an.mp, 4, col.text, true);
    an.sec = line(panel, an.sp, 2, col.a1, true);
    box(panel, AN_CX - 6, AN_CY - 6, 12, 12, 6, col.a1);

    box(panel, 14, 252, 102, 52, 16, col.card);
    lbl(panel, NF_S, col.dim, 65, 258, 100, "DATE");
    box(panel, 124, 252, 102, 52, 16, col.card);
    lbl(panel, NF_S, col.dim, 175, 258, 100, "STEPS");
    an.wd = lbl(panel, NF_S, col.dim, 65, 258, 100, "---");
    an.dm = lbl(panel, NF_M, col.text, 65, 276, 100, "--");
    an.steps = lbl(panel, NF_M, col.a1, 175, 276, 100, "0");
}

// ============================ EMBER EYES ============================
struct EmberUI
{
    lv_obj_t *time, *pl, *pr, *cl, *cr;
    lv_timer_t* tm;
};
EmberUI em = {};

const int EM_PL_X = 73;
const int EM_PR_X = 153;
const int EM_COVER_H = 56;

void animX(void* o, int32_t v)
{
    lv_obj_set_x((lv_obj_t*)o, v);
}

void animH(void* o, int32_t v)
{
    lv_obj_set_height((lv_obj_t*)o, v);
}

void blinkBack(lv_anim_t* a)
{
    lv_anim_t b;
    lv_anim_init(&b);
    lv_anim_set_var(&b, a->var);
    lv_anim_set_exec_cb(&b, animH);
    lv_anim_set_values(&b, EM_COVER_H, 0);
    lv_anim_set_duration(&b, 110);
    lv_anim_start(&b);
}

void blinkOne(lv_obj_t* cover)
{
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, cover);
    lv_anim_set_exec_cb(&a, animH);
    lv_anim_set_values(&a, 0, EM_COVER_H);
    lv_anim_set_duration(&a, 80);
    lv_anim_set_ready_cb(&a, blinkBack);
    lv_anim_start(&a);
}

void glanceOne(lv_obj_t* pupil, int target)
{
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, pupil);
    lv_anim_set_exec_cb(&a, animX);
    lv_anim_set_values(&a, lv_obj_get_x(pupil), target);
    lv_anim_set_duration(&a, 260);
    lv_anim_start(&a);
}

void emberTick(lv_timer_t*)
{
    if (!em.cl)
    {
        return;
    }
    const int r = (int)lv_rand(0, 99);
    if (r < 40)
    {
        blinkOne(em.cl);
        blinkOne(em.cr);
    }
    else if (r < 85)
    {
        const int t[3] = {-8, 0, 8};
        const int o = t[lv_rand(0, 2)];
        glanceOne(em.pl, EM_PL_X + o);
        glanceOne(em.pr, EM_PR_X + o);
    }
}

void emberTeardown()
{
    if (em.tm)
    {
        lv_timer_delete(em.tm);
    }
    if (em.pl) lv_anim_delete(em.pl, nullptr);
    if (em.pr) lv_anim_delete(em.pr, nullptr);
    if (em.cl) lv_anim_delete(em.cl, nullptr);
    if (em.cr) lv_anim_delete(em.cr, nullptr);
    em = EmberUI{};
}

void emberUpdate(const HomeData& d)
{
    if (!em.time)
    {
        return;
    }
    char b[8];
    fmtTime(d, b, sizeof(b));
    lv_label_set_text(em.time, b);
}

void eye(lv_obj_t* p, int cx, int pupilX, lv_obj_t** pupil, lv_obj_t** cover, int lidRot)
{
    const lv_color_t red = HEX(0xE01616);
    box(p, cx - 28, 114, 56, 56, 28, red);
    box(p, cx - 19, 123, 38, 38, 19, HEX(0xF2F2F2));
    *pupil = box(p, pupilX, 138, 14, 14, 7, HEX(0x111111));
    *cover = box(p, cx - 28, 114, 56, 0, 0, HEX(0x000000));

    lv_obj_t* lid = box(p, cx - 42, 90, 84, 44, 0, HEX(0x000000));
    lv_obj_set_style_transform_pivot_x(lid, 42, 0);
    lv_obj_set_style_transform_pivot_y(lid, 22, 0);
    lv_obj_set_style_transform_rotation(lid, lidRot, 0);
}

void emberBuild(lv_obj_t* panel)
{
    emberTeardown();
    prep(panel, HEX(0x000000));

    eye(panel, 78, EM_PL_X, &em.pl, &em.cl, 180);
    eye(panel, 162, EM_PR_X, &em.pr, &em.cr, -180);

    static lv_point_precise_t mouth[2];
    setPt(mouth[0], 106, 202);
    setPt(mouth[1], 134, 196);
    line(panel, mouth, 2, HEX(0xD8D8D8), true);

    em.time = lbl(panel, NF_XL, HEX(0xE01616), 120, 236, 240, "--:--");
    em.tm = lv_timer_create(emberTick, 1700, nullptr);
}

// ============================ WAYFINDER RED ============================
struct Gauge
{
    lv_obj_t *arc, *val, *sub;
};

struct WfUI
{
    Gauge hr, o2, tmp, bat;
    lv_obj_t *time, *date, *dPrev, *dCur, *dNext;
    lv_obj_t *stepArc, *stepLbl, *alarm;
};
WfUI wf = {};

const uint32_t WF_RED = 0xFF2A2A;
const uint32_t WF_TRACK = 0x4A0B0B;

Gauge mkGauge(lv_obj_t* p, int cx, int cy, int d, int mn, int mx, int w, const char* sub)
{
    Gauge g = {};
    g.arc = lv_arc_create(p);
    lv_obj_set_size(g.arc, d, d);
    lv_obj_set_pos(g.arc, cx - d / 2, cy - d / 2);
    lv_arc_set_rotation(g.arc, 0);
    lv_arc_set_bg_angles(g.arc, 135, 45);
    lv_arc_set_range(g.arc, mn, mx);
    lv_arc_set_value(g.arc, mn);
    styleArc(g.arc, w, HEX(WF_RED), HEX(WF_TRACK));
    g.val = lbl(p, NF_M, HEX(WF_RED), cx, cy - 13, d, "--");
    g.sub = lbl(p, NF_S, HEX(WF_RED), cx, cy + 7, d, sub);
    return g;
}

void setGauge(const Gauge& g, int mn, int mx, int v, bool valid, const char* text)
{
    lv_arc_set_value(g.arc, valid ? clampi(v, mn, mx) : mn);
    lv_label_set_text(g.val, valid ? text : "--");
}

void wfUpdate(const HomeData& d)
{
    if (!wf.time)
    {
        return;
    }
    char b[24];
    fmtTime(d, b, sizeof(b));
    lv_label_set_text(wf.time, b);

    if (d.timeValid)
    {
        snprintf(b, sizeof(b), "%s %d %s", DAYS[d.weekday % 7], (int)d.day,
                 MONTHS[(d.month >= 1 && d.month <= 12) ? d.month - 1 : 0]);
        lv_label_set_text(wf.date, b);
        lv_label_set_text(wf.dPrev, DAYS[(d.weekday + 6) % 7]);
        lv_label_set_text(wf.dCur, DAYS[d.weekday % 7]);
        lv_label_set_text(wf.dNext, DAYS[(d.weekday + 1) % 7]);
    }
    else
    {
        lv_label_set_text(wf.date, "--");
    }

    snprintf(b, sizeof(b), "%u", (unsigned)d.heartRate);
    setGauge(wf.hr, 40, 180, d.heartRate, d.heartRate > 0, b);
    snprintf(b, sizeof(b), "%u", (unsigned)d.oxygen);
    setGauge(wf.o2, 80, 100, d.oxygen, d.oxygen > 0, b);
    snprintf(b, sizeof(b), "%d", (int)d.tempC);
    setGauge(wf.tmp, 0, 40, d.tempC, d.hasTemp, b);
    snprintf(b, sizeof(b), "%d", (int)d.battery);
    setGauge(wf.bat, 0, 100, d.battery, d.battery >= 0, b);

    const int goal = d.stepGoal > 0 ? d.stepGoal : 10000;
    lv_arc_set_value(wf.stepArc, clampi((int)((uint32_t)d.steps * 100u / (uint32_t)goal), 0, 100));
    if (d.steps >= 1000)
    {
        snprintf(b, sizeof(b), "%u.%uk", (unsigned)(d.steps / 1000), (unsigned)((d.steps % 1000) / 100));
    }
    else
    {
        snprintf(b, sizeof(b), "%u", (unsigned)d.steps);
    }
    lv_label_set_text(wf.stepLbl, b);
    lv_label_set_text(wf.alarm, d.nextAlarm);
}

void wfBuild(lv_obj_t* panel)
{
    wf = WfUI{};
    prep(panel, HEX(0x050000));
    const lv_color_t red = HEX(WF_RED);

    for (int i = 0; i < 24; ++i)
    {
        const bool big = (i % 6 == 0);
        const int w = big ? 14 : 7;
        const int y = 42 + i * 10;
        box(panel, 8, y, w, 2, 0, red);
        box(panel, 232 - w, y, w, 2, 0, red);
    }

    wf.hr = mkGauge(panel, 62, 58, 56, 40, 180, 5, "bpm");
    wf.o2 = mkGauge(panel, 120, 58, 56, 80, 100, 5, "SpO2");
    wf.tmp = mkGauge(panel, 178, 58, 56, 0, 40, 5, "temp C");

    wf.time = lbl(panel, NF_XL, red, 120, 92, 200, "--:--");
    wf.date = lbl(panel, NF_S, red, 120, 150, 200, "--");

    for (int i = 0; i < 29; ++i)
    {
        const bool big = (i % 5 == 0);
        const bool mid = (i == 14);
        const int h = mid ? 22 : (big ? 14 : 8);
        box(panel, 34 + i * 6, 184 - h / 2, 2, h, 0, red);
    }

    wf.dPrev = lbl(panel, NF_S, red, 52, 204, 50, "---");
    wf.dCur = lbl(panel, NF_M, red, 120, 201, 60, "---");
    wf.dNext = lbl(panel, NF_S, red, 188, 204, 50, "---");

    wf.stepArc = lv_arc_create(panel);
    lv_obj_set_size(wf.stepArc, 56, 56);
    lv_obj_set_pos(wf.stepArc, 62 - 28, 262 - 28);
    lv_arc_set_rotation(wf.stepArc, 270);
    lv_arc_set_bg_angles(wf.stepArc, 0, 360);
    lv_arc_set_range(wf.stepArc, 0, 100);
    lv_arc_set_value(wf.stepArc, 0);
    styleArc(wf.stepArc, 7, red, HEX(WF_TRACK));
    wf.stepLbl = lbl(panel, NF_S, red, 62, 254, 40, "0");

    box(panel, 92, 234, 56, 56, 28, HEX(0x2A0606));
    lbl(panel, NF_S, red, 120, 244, 56, "ALARM");
    wf.alarm = lbl(panel, NF_S, red, 120, 264, 56, "--:--");

    wf.bat = mkGauge(panel, 178, 262, 56, 0, 100, 5, "bat");
}


#if LV_FONT_MONTSERRAT_28
#define NF_L (&lv_font_montserrat_28)
#elif LV_FONT_MONTSERRAT_24
#define NF_L (&lv_font_montserrat_24)
#else
#define NF_L NF_M
#endif

const char* const DAYF[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

NewMusicHandler musicCb = nullptr;

lv_obj_t* lblL(lv_obj_t* p, const lv_font_t* f, lv_color_t c, int x, int y, int w, const char* t)
{
    lv_obj_t* l = lbl(p, f, c, x + w / 2, y, w, t);
    lv_obj_set_style_text_align(l, LV_TEXT_ALIGN_LEFT, 0);
    return l;
}

lv_obj_t* lblR(lv_obj_t* p, const lv_font_t* f, lv_color_t c, int x, int y, int w, const char* t)
{
    lv_obj_t* l = lbl(p, f, c, x + w / 2, y, w, t);
    lv_obj_set_style_text_align(l, LV_TEXT_ALIGN_RIGHT, 0);
    return l;
}

// ---- seven-segment digit made of rounded bars (crisp at any size) ----
struct Dig
{
    lv_obj_t* s[7];
    int8_t shown;
};
const uint8_t SEGMASK[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

void digSet(Dig& d, int n)
{
    if (n == d.shown)
    {
        return;
    }
    d.shown = (int8_t)n;
    const uint8_t m = (n >= 0 && n <= 9) ? SEGMASK[n] : 0x40;
    for (int i = 0; i < 7; ++i)
    {
        lv_obj_set_style_bg_opa(d.s[i], ((m >> i) & 1) ? LV_OPA_COVER : LV_OPA_TRANSP, 0);
    }
}

void digBuild(lv_obj_t* p, Dig& d, int x, int y, int w, int h, int t, lv_color_t c)
{
    const int L = (h - 3 * t) / 2;
    const int r = t / 2;
    d.s[0] = box(p, x + t, y, w - 2 * t, t, r, c);
    d.s[1] = box(p, x + w - t, y + t, t, L, r, c);
    d.s[2] = box(p, x + w - t, y + 2 * t + L, t, L, r, c);
    d.s[3] = box(p, x + t, y + h - t, w - 2 * t, t, r, c);
    d.s[4] = box(p, x, y + 2 * t + L, t, L, r, c);
    d.s[5] = box(p, x, y + t, t, L, r, c);
    d.s[6] = box(p, x + t, y + t + L, w - 2 * t, t, r, c);
    d.shown = -2;
    digSet(d, -1);
}

// ============================ STACK ============================
struct StackUI
{
    Dig h0, h1, m0, m1;
    lv_obj_t *date, *bat, *steps, *hr, *tmp, *wx;
};
StackUI sk = {};

void stackUpdate(const HomeData& d)
{
    if (!sk.date)
    {
        return;
    }
    const int hh = d.timeValid ? d.hour : -1;
    const int mm = d.timeValid ? d.minute : -1;
    digSet(sk.h0, hh < 0 ? -1 : hh / 10);
    digSet(sk.h1, hh < 0 ? -1 : hh % 10);
    digSet(sk.m0, mm < 0 ? -1 : mm / 10);
    digSet(sk.m1, mm < 0 ? -1 : mm % 10);

    char b[32];
    if (d.timeValid)
    {
        snprintf(b, sizeof(b), "%s %d %s", DAYS[d.weekday % 7], (int)d.day,
                 MONTHS[(d.month >= 1 && d.month <= 12) ? d.month - 1 : 0]);
    }
    else
    {
        snprintf(b, sizeof(b), "--");
    }
    lv_label_set_text(sk.date, b);

    if (d.battery >= 0) snprintf(b, sizeof(b), "%d%%", (int)d.battery);
    else snprintf(b, sizeof(b), "--");
    lv_label_set_text(sk.bat, b);

    snprintf(b, sizeof(b), "%u", (unsigned)d.steps);
    lv_label_set_text(sk.steps, b);
    if (d.heartRate > 0) snprintf(b, sizeof(b), "%u", (unsigned)d.heartRate);
    else snprintf(b, sizeof(b), "--");
    lv_label_set_text(sk.hr, b);
    if (d.hasTemp) snprintf(b, sizeof(b), "%dC", (int)d.tempC);
    else snprintf(b, sizeof(b), "--");
    lv_label_set_text(sk.tmp, b);
    snprintf(b, sizeof(b), "%.9s", d.weather);
    lv_label_set_text(sk.wx, b[0] ? b : "weather");
}

void stackBuild(lv_obj_t* panel)
{
    sk = StackUI{};
    prep(panel, col.bg);
    sk.date = lblL(panel, NF_S, col.dim, 24, 20, 130, "--");
    sk.bat = lblR(panel, NF_S, col.a1, 136, 20, 80, "--");
    digBuild(panel, sk.h0, 24, 48, 68, 100, 14, col.text);
    digBuild(panel, sk.h1, 104, 48, 68, 100, 14, col.text);
    digBuild(panel, sk.m0, 24, 158, 68, 100, 14, col.a1);
    digBuild(panel, sk.m1, 104, 158, 68, 100, 14, col.a1);
    box(panel, 24, 266, 192, 1, 0, col.card);

    sk.steps = lbl(panel, NF_M, col.text, 52, 270, 72, "0");
    lbl(panel, NF_S, col.dim, 52, 293, 72, "steps");
    sk.hr = lbl(panel, NF_M, col.text, 120, 270, 72, "--");
    lbl(panel, NF_S, col.dim, 120, 293, 72, "bpm");
    sk.tmp = lbl(panel, NF_M, col.text, 188, 270, 72, "--");
    sk.wx = lbl(panel, NF_S, col.dim, 188, 293, 72, "weather");
}

// ============================ GLANCE ============================
struct GlanceUI
{
    lv_obj_t *time, *date, *bat, *temp, *wx, *stepsVal, *stepsFill, *hr, *msg;
};
GlanceUI gl = {};

void glanceUpdate(const HomeData& d)
{
    if (!gl.time)
    {
        return;
    }
    char b[32];
    fmtTime(d, b, sizeof(b));
    lv_label_set_text(gl.time, b);
    if (d.timeValid)
    {
        snprintf(b, sizeof(b), "%s %d %s", DAYS[d.weekday % 7], (int)d.day,
                 MONTHS[(d.month >= 1 && d.month <= 12) ? d.month - 1 : 0]);
    }
    else
    {
        snprintf(b, sizeof(b), "--");
    }
    lv_label_set_text(gl.date, b);
    if (d.battery >= 0) snprintf(b, sizeof(b), "%d%%", (int)d.battery);
    else snprintf(b, sizeof(b), "--");
    lv_label_set_text(gl.bat, b);

    if (d.hasTemp) snprintf(b, sizeof(b), "%dC", (int)d.tempC);
    else snprintf(b, sizeof(b), "--");
    lv_label_set_text(gl.temp, b);
    lv_label_set_text(gl.wx, d.weather[0] ? d.weather : "No weather yet");

    const int goal = d.stepGoal > 0 ? d.stepGoal : 10000;
    snprintf(b, sizeof(b), "%u / %d", (unsigned)d.steps, goal);
    lv_label_set_text(gl.stepsVal, b);
    lv_obj_set_width(gl.stepsFill, clampi((int)((uint32_t)d.steps * 184u / (uint32_t)goal), 0, 184));

    if (d.heartRate > 0) snprintf(b, sizeof(b), "%u bpm", (unsigned)d.heartRate);
    else snprintf(b, sizeof(b), "-- bpm");
    lv_label_set_text(gl.hr, b);
    snprintf(b, sizeof(b), "%u new", (unsigned)d.notifCount);
    lv_label_set_text(gl.msg, b);
}

void glanceBuild(lv_obj_t* panel)
{
    gl = GlanceUI{};
    prep(panel, col.bg);
    gl.time = lblL(panel, NF_XL, col.text, 16, 14, 170, "--:--");
    gl.date = lblL(panel, NF_S, col.dim, 18, 68, 150, "--");
    box(panel, 176, 28, 52, 22, 11, col.card);
    gl.bat = lbl(panel, NF_S, col.a1, 202, 31, 52, "--");

    box(panel, 14, 96, 212, 62, 16, col.card);
    gl.temp = lblL(panel, NF_L, col.text, 28, 112, 70, "--");
    gl.wx = lblR(panel, NF_S, col.dim, 100, 118, 112, "--");

    box(panel, 14, 166, 212, 56, 16, col.card);
    lblL(panel, NF_S, col.dim, 28, 176, 60, "Steps");
    gl.stepsVal = lblR(panel, NF_S, col.text, 88, 176, 124, "0");
    box(panel, 28, 203, 184, 6, 3, lv_color_mix(col.dim, col.card, 120));
    gl.stepsFill = box(panel, 28, 203, 0, 6, 3, col.a1);

    box(panel, 14, 230, 102, 64, 16, col.card);
    lblL(panel, NF_S, col.dim, 28, 238, 80, "Heart");
    gl.hr = lblL(panel, NF_M, col.text, 28, 260, 84, "-- bpm");

    box(panel, 124, 230, 102, 64, 16, col.card);
    lblL(panel, NF_S, col.dim, 138, 238, 80, "Messages");
    gl.msg = lblL(panel, NF_M, col.text, 138, 260, 84, "0 new");
}

// ============================ NOW ============================
struct NowUI
{
    lv_obj_t *time, *date, *notifHead, *notifSub, *bat, *steps, *tmp;
};
NowUI nw = {};

void musicEv(lv_event_t* e)
{
    if (musicCb)
    {
        musicCb((uint8_t)(uintptr_t)lv_event_get_user_data(e));
    }
}

lv_obj_t* musicBtn(lv_obj_t* p, int cx, const char* sym, uint8_t action, lv_color_t c)
{
    lv_obj_t* l = lbl(p, NF_M, c, cx, 162, 56, sym);
    lv_obj_add_flag(l, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(l, musicEv, LV_EVENT_CLICKED, (void*)(uintptr_t)action);
    return l;
}

void nowUpdate(const HomeData& d)
{
    if (!nw.time)
    {
        return;
    }
    char b[48];
    fmtTime(d, b, sizeof(b));
    lv_label_set_text(nw.time, b);
    if (d.timeValid)
    {
        snprintf(b, sizeof(b), "%s %d %s", DAYF[d.weekday % 7], (int)d.day,
                 MONTHS[(d.month >= 1 && d.month <= 12) ? d.month - 1 : 0]);
    }
    else
    {
        snprintf(b, sizeof(b), "--");
    }
    lv_label_set_text(nw.date, b);

    if (d.notifCount > 0) snprintf(b, sizeof(b), "%u new messages", (unsigned)d.notifCount);
    else snprintf(b, sizeof(b), "No new messages");
    lv_label_set_text(nw.notifHead, b);
    if (d.notifApp[0] && d.notifTitle[0]) snprintf(b, sizeof(b), "%.12s: %.16s", d.notifApp, d.notifTitle);
    else if (d.notifApp[0]) snprintf(b, sizeof(b), "%.28s", d.notifApp);
    else snprintf(b, sizeof(b), "Nothing to show");
    lv_label_set_text(nw.notifSub, b);

    if (d.battery >= 0) snprintf(b, sizeof(b), "%d%%", (int)d.battery);
    else snprintf(b, sizeof(b), "--");
    lv_label_set_text(nw.bat, b);
    snprintf(b, sizeof(b), "%u", (unsigned)d.steps);
    lv_label_set_text(nw.steps, b);
    if (d.hasTemp) snprintf(b, sizeof(b), "%dC", (int)d.tempC);
    else snprintf(b, sizeof(b), "--");
    lv_label_set_text(nw.tmp, b);
}

void nowBuild(lv_obj_t* panel)
{
    nw = NowUI{};
    prep(panel, col.bg);
    nw.time = lbl(panel, NF_XL, col.text, 120, 14, 240, "--:--");
    nw.date = lbl(panel, NF_M, col.dim, 120, 68, 240, "--");

    box(panel, 14, 100, 212, 92, 18, col.card);
    lblL(panel, NF_M, col.text, 28, 108, 184, "Music");
    lblL(panel, NF_S, col.dim, 28, 132, 184, "Phone controls");
    musicBtn(panel, 68, LV_SYMBOL_PREV, 0, col.text);
    musicBtn(panel, 120, LV_SYMBOL_PLAY, 1, col.a1);
    musicBtn(panel, 172, LV_SYMBOL_NEXT, 2, col.text);

    box(panel, 14, 200, 212, 46, 16, col.card);
    box(panel, 26, 219, 8, 8, 4, col.a1);
    nw.notifHead = lblL(panel, NF_S, col.text, 42, 205, 176, "--");
    nw.notifSub = lblL(panel, NF_S, col.dim, 42, 224, 176, "--");

    nw.bat = lbl(panel, NF_M, col.text, 48, 260, 80, "--");
    lbl(panel, NF_S, col.dim, 48, 284, 80, "battery");
    nw.steps = lbl(panel, NF_M, col.text, 120, 260, 80, "0");
    lbl(panel, NF_S, col.dim, 120, 284, 80, "steps");
    nw.tmp = lbl(panel, NF_M, col.text, 192, 260, 80, "--");
    lbl(panel, NF_S, col.dim, 192, 284, 80, "temp");
}

void buildKind(lv_obj_t* panel, uint8_t kind)
{
    switch (kind)
    {
    case NEW_FACE_ANALOG:
        analogBuild(panel);
        break;
    case NEW_FACE_EMBER:
        emberBuild(panel);
        break;
    case NEW_FACE_WAYFINDER:
        wfBuild(panel);
        break;
    case NEW_FACE_STACK:
        stackBuild(panel);
        break;
    case NEW_FACE_GLANCE:
        glanceBuild(panel);
        break;
    case NEW_FACE_NOW:
        nowBuild(panel);
        break;
    default:
        return;
    }
    if (haveCur)
    {
        uiNewUpdate(cur);
    }
}
} // namespace

void uiNewBuildFace(lv_obj_t* panel, uint8_t kind, const HomeColors& colors)
{
    if (panel == nullptr || kind >= NEW_FACE_COUNT)
    {
        return;
    }
    col = colors;
    panels[kind] = panel;
    buildKind(panel, kind);
}

void uiNewUpdate(const HomeData& data)
{
    cur = data;
    haveCur = true;
    if (panels[NEW_FACE_ANALOG]) analogUpdate(data);
    if (panels[NEW_FACE_EMBER]) emberUpdate(data);
    if (panels[NEW_FACE_WAYFINDER]) wfUpdate(data);
    if (panels[NEW_FACE_STACK]) stackUpdate(data);
    if (panels[NEW_FACE_GLANCE]) glanceUpdate(data);
    if (panels[NEW_FACE_NOW]) nowUpdate(data);
}

void uiNewRecolor(const HomeColors& colors)
{
    col = colors;
    for (uint8_t k = 0; k < NEW_FACE_COUNT; ++k)
    {
        if (panels[k] != nullptr)
        {
            if (k == NEW_FACE_EMBER)
            {
                emberTeardown();
            }
            lv_obj_clean(panels[k]);
            buildKind(panels[k], k);
        }
    }
}

void uiNewSetMusicHandler(NewMusicHandler handler)
{
    musicCb = handler;
}
