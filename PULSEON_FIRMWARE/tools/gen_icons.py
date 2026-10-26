#!/usr/bin/env python3
"""Generates src/ui/UIIcons.h: 32x32 A8 icons, recolored at runtime by the theme."""
import math, os, struct, sys, zlib

N, S = 32, 4


def circle(cx, cy, r):
    return lambda x, y: (x - cx) ** 2 + (y - cy) ** 2 <= r * r


def ring(cx, cy, r, w):
    ro, ri = r + w / 2, r - w / 2
    return lambda x, y: ri * ri <= (x - cx) ** 2 + (y - cy) ** 2 <= ro * ro


def rrect(x0, y0, x1, y1, r):
    def f(x, y):
        if x < x0 or x > x1 or y < y0 or y > y1:
            return False
        cx = min(max(x, x0 + r), x1 - r)
        cy = min(max(y, y0 + r), y1 - r)
        return (x - cx) ** 2 + (y - cy) ** 2 <= r * r
    return f


def line(x0, y0, x1, y1, w):
    dx, dy = x1 - x0, y1 - y0
    l2 = dx * dx + dy * dy

    def f(x, y):
        t = 0 if l2 == 0 else max(0, min(1, ((x - x0) * dx + (y - y0) * dy) / l2))
        return (x - (x0 + t * dx)) ** 2 + (y - (y0 + t * dy)) ** 2 <= (w / 2) ** 2
    return f


def poly(pts):
    def f(x, y):
        inside, j = False, len(pts) - 1
        for i in range(len(pts)):
            xi, yi = pts[i]
            xj, yj = pts[j]
            if (yi > y) != (yj > y) and x < (xj - xi) * (y - yi) / (yj - yi) + xi:
                inside = not inside
            j = i
        return inside
    return f


def arc(cx, cy, r, w, a0, a1):
    rg = ring(cx, cy, r, w)

    def f(x, y):
        return rg(x, y) and a0 <= math.degrees(math.atan2(y - cy, x - cx)) <= a1
    return f


def radial(cx, cy, r0, r1, w, count, start=0.0):
    out = []
    for k in range(count):
        a = math.radians(start + k * 360.0 / count)
        out.append(('+', line(cx + r0 * math.cos(a), cy + r0 * math.sin(a),
                              cx + r1 * math.cos(a), cy + r1 * math.sin(a), w)))
    return out


cloud = [circle(11.5, 21.5, 5.5), circle(18, 18.5, 7), circle(23.5, 22, 4.5), rrect(8, 21, 26, 27, 3)]
cloud_gap = [circle(11.5, 21.5, 7.3), circle(18, 18.5, 8.8), circle(23.5, 22, 6.3), rrect(6.2, 19.2, 27.8, 28.8, 4.8)]

ICONS = {
    'MUSIC': [('+', circle(10.5, 23.5, 4.2)), ('+', circle(22, 21.5, 4.2)),
              ('+', line(14, 23, 14, 8.5, 2.6)), ('+', line(25.5, 21, 25.5, 6.5, 2.6)),
              ('+', poly([(12.7, 7), (26.8, 4), (26.8, 9.5), (12.7, 12.5)]))],
    'WEATHER': [('+', circle(21.5, 10.5, 4.6))] + radial(21.5, 10.5, 7.0, 9.4, 1.9, 8) +
               [('-', f) for f in cloud_gap] + [('+', f) for f in cloud],
    'ALARM': [('+', ring(16, 17.5, 9.5, 2.6)), ('+', line(16, 17.5, 16, 11.5, 2.3)),
              ('+', line(16, 17.5, 20.5, 20, 2.3)), ('+', circle(6.2, 8, 3.6)), ('+', circle(25.8, 8, 3.6)),
              ('-', ring(16, 17.5, 9.5, 2.6)), ('+', ring(16, 17.5, 9.5, 2.6))],
    'FIND': [('+', rrect(4.5, 5, 17, 27.5, 3.2)), ('-', rrect(6.8, 8, 14.7, 23, 1.2)),
             ('+', arc(17.5, 16, 6.2, 2.2, -48, 48)), ('+', arc(17.5, 16, 10.8, 2.2, -48, 48))],
    'CAMERA': [('+', rrect(3.5, 9, 28.5, 26.5, 4)), ('+', rrect(10.5, 5, 21.5, 10.5, 2)),
               ('-', circle(16, 17.8, 6.6)), ('+', circle(16, 17.8, 3.6))],
    'ALERTS': [('+', circle(16, 13, 8)), ('+', poly([(8, 13), (24, 13), (26.5, 21), (5.5, 21)])),
               ('+', rrect(4.5, 20, 27.5, 23.5, 1.7)), ('+', circle(16, 26.2, 2.6)), ('+', rrect(14.6, 3.5, 17.4, 6, 1))],
    'NAV': [('+', poly([(16, 3), (26.5, 27.5), (16, 21.5), (5.5, 27.5)]))],
    'THEME': [('+', circle(16, 19, 9)), ('+', poly([(16, 3), (24.4, 16), (7.6, 16)])),
              ('-', circle(12.5, 19.5, 2.4))],
    'SETTINGS': [('+', circle(16, 16, 8.6))] + radial(16, 16, 7, 12.6, 4.4, 8) +
                [('-', circle(16, 16, 3.8))],
    'BLUETOOTH': [('+', line(16, 3.5, 16, 28.5, 2.5)), ('+', line(16, 3.5, 23, 10, 2.5)),
                  ('+', line(23, 10, 9, 22.5, 2.5)), ('+', line(9, 9.5, 23, 22, 2.5)),
                  ('+', line(23, 22, 16, 28.5, 2.5))],
    'CONTACTS': [('+', circle(16, 10.5, 5.8)), ('+', rrect(6, 18.5, 26, 28.5, 6))],
    'QR': [('+', rrect(3.5, 3.5, 14, 14, 1.4)), ('-', rrect(5.9, 5.9, 11.6, 11.6, 0.4)), ('+', rrect(7.6, 7.6, 9.9, 9.9, 0.3)),
           ('+', rrect(18, 3.5, 28.5, 14, 1.4)), ('-', rrect(20.4, 5.9, 26.1, 11.6, 0.4)), ('+', rrect(22.1, 7.6, 24.4, 9.9, 0.3)),
           ('+', rrect(3.5, 18, 14, 28.5, 1.4)), ('-', rrect(5.9, 20.4, 11.6, 26.1, 0.4)), ('+', rrect(7.6, 22.1, 9.9, 24.4, 0.3)),
           ('+', rrect(18, 18, 21.5, 21.5, 0.5)), ('+', rrect(24, 18, 28.5, 21.5, 0.5)),
           ('+', rrect(18, 24, 21.5, 28.5, 0.5)), ('+', rrect(24, 24, 28.5, 28.5, 0.5))],
    'APPS': [('+', circle(9, 9, 4.2)), ('+', circle(23, 9, 4.2)), ('+', circle(9, 23, 4.2)), ('+', circle(23, 23, 4.2))],
}


def render(ops):
    out = bytearray()
    for py in range(N):
        for px in range(N):
            hit = 0
            for sy in range(S):
                for sx in range(S):
                    x, y = px + (sx + 0.5) / S, py + (sy + 0.5) / S
                    on = False
                    for op, f in ops:
                        if f(x, y):
                            on = (op == '+')
                    hit += on
            out.append(round(255 * hit / (S * S)))
    return bytes(out)


def write_png(path, w, h, rows):
    raw = b''.join(b'\x00' + bytes(r) for r in rows)

    def chunk(t, d):
        c = struct.pack('>I', len(d)) + t + d
        return c + struct.pack('>I', zlib.crc32(t + d) & 0xFFFFFFFF)
    png = b'\x89PNG\r\n\x1a\n' + chunk(b'IHDR', struct.pack('>IIBBBBB', w, h, 8, 2, 0, 0, 0)) + \
        chunk(b'IDAT', zlib.compress(raw)) + chunk(b'IEND', b'')
    open(path, 'wb').write(png)


def main():
    names = list(ICONS)
    data = {n: render(ICONS[n]) for n in names}

    if '--preview' in sys.argv:
        path = sys.argv[sys.argv.index('--preview') + 1]
        cols, scale, pad = 6, 4, 6
        rows_n = (len(names) + cols - 1) // cols
        cell = N * scale + pad
        W, H = cols * cell + pad, rows_n * cell + pad
        img = [[(24, 26, 36)] * W for _ in range(H)]
        tint = (255, 93, 108)
        for i, n in enumerate(names):
            ox, oy = pad + (i % cols) * cell, pad + (i // cols) * cell
            for y in range(N * scale):
                for x in range(N * scale):
                    a = data[n][(y // scale) * N + (x // scale)] / 255.0
                    bg = img[oy + y][ox + x]
                    img[oy + y][ox + x] = tuple(int(bg[k] * (1 - a) + tint[k] * a) for k in range(3))
        write_png(path, W, H, [[c for px in row for c in px] for row in img])
        print('preview written to', path)
        return

    out = os.path.join('src', 'ui', 'UIIcons.h')
    L = ['#pragma once', '', '// Generated by tools/gen_icons.py. Do not edit by hand.', '',
         '#include <lvgl.h>', '#include <stdint.h>', '#include <string.h>', '', 'enum UIIconId : uint8_t', '{']
    L += ['    UI_ICON_%s,' % n for n in names] + ['    UI_ICON_COUNT', '};', '']
    for n in names:
        L.append('alignas(4) inline const uint8_t UI_ICON_DATA_%s[%d] = {' % (n, N * N))
        d = data[n]
        for i in range(0, len(d), 32):
            L.append('    ' + ','.join(str(b) for b in d[i:i + 32]) + ',')
        L.append('};')
    L += ['', 'inline const lv_image_dsc_t* uiIcon(uint8_t id)', '{',
          '    static const uint8_t* const DATA[UI_ICON_COUNT] = {']
    L += ['        UI_ICON_DATA_%s,' % n for n in names]
    L += ['    };', '    static lv_image_dsc_t dsc[UI_ICON_COUNT];', '    static bool ready = false;',
          '    if (!ready)', '    {', '        for (uint8_t i = 0; i < UI_ICON_COUNT; ++i)', '        {',
          '            memset(&dsc[i], 0, sizeof(dsc[i]));',
          '            dsc[i].header.magic = LV_IMAGE_HEADER_MAGIC;',
          '            dsc[i].header.cf = LV_COLOR_FORMAT_A8;',
          '            dsc[i].header.w = %d;' % N, '            dsc[i].header.h = %d;' % N,
          '            dsc[i].header.stride = %d;' % N,
          '            dsc[i].data_size = %d;' % (N * N), '            dsc[i].data = DATA[i];',
          '        }', '        ready = true;', '    }',
          '    return &dsc[id < UI_ICON_COUNT ? id : UI_ICON_APPS];', '}', '',
          'inline bool uiIconHas(const char* text, const char* word)', '{',
          '    for (const char* p = text; *p; ++p)', '    {',
          '        const char* a = p;', '        const char* b = word;',
          '        while (*a && *b && ((*a | 32) == *b))', '        {', '            ++a;', '            ++b;', '        }',
          '        if (*b == 0)', '        {', '            return true;', '        }', '    }',
          '    return false;', '}', '',
          'inline uint8_t uiIconForName(const char* text)', '{',
          '    if (text == nullptr) return UI_ICON_APPS;',
          '    if (uiIconHas(text, "music")) return UI_ICON_MUSIC;',
          '    if (uiIconHas(text, "weather")) return UI_ICON_WEATHER;',
          '    if (uiIconHas(text, "alarm")) return UI_ICON_ALARM;',
          '    if (uiIconHas(text, "find")) return UI_ICON_FIND;',
          '    if (uiIconHas(text, "camera")) return UI_ICON_CAMERA;',
          '    if (uiIconHas(text, "alert")) return UI_ICON_ALERTS;',
          '    if (uiIconHas(text, "navig")) return UI_ICON_NAV;',
          '    if (uiIconHas(text, "theme")) return UI_ICON_THEME;',
          '    if (uiIconHas(text, "setting")) return UI_ICON_SETTINGS;',
          '    if (uiIconHas(text, "blue")) return UI_ICON_BLUETOOTH;',
          '    if (uiIconHas(text, "contact")) return UI_ICON_CONTACTS;',
          '    if (uiIconHas(text, "qr")) return UI_ICON_QR;',
          '    return UI_ICON_APPS;', '}', '']
    open(out, 'w').write('\n'.join(L))
    print('wrote', out, '(%d icons, %d bytes of pixel data)' % (len(names), len(names) * N * N))


main()
