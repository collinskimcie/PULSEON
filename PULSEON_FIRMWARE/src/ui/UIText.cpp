#include "UIText.h"

#include "PULSEON_WATCH_UI.h"
#include "PulseonEmoji.h"

#include <string.h>

namespace
{
// Vertical nudge for the emoji images relative to the text baseline.
constexpr int32_t EMOJI_OFFSET_Y = 0;

struct FontSlot
{
    const lv_font_t* base;
    lv_font_t* font;
};
FontSlot slots[6] = {};

const void* emojiPath(const lv_font_t*, uint32_t unicode, uint32_t, int32_t* offsetY, void*)
{
    const lv_image_dsc_t* dsc = pulseonEmojiFind(unicode);
    if (dsc != nullptr && offsetY != nullptr)
    {
        *offsetY = EMOJI_OFFSET_Y;
    }
    return dsc;
}

size_t decode(const uint8_t* p, size_t remaining, uint32_t& cp)
{
    const uint8_t c = p[0];
    if (c < 0x80)
    {
        cp = c;
        return 1;
    }
    if ((c & 0xE0) == 0xC0 && remaining >= 2)
    {
        cp = ((c & 0x1F) << 6) | (p[1] & 0x3F);
        return 2;
    }
    if ((c & 0xF0) == 0xE0 && remaining >= 3)
    {
        cp = ((c & 0x0F) << 12) | ((p[1] & 0x3F) << 6) | (p[2] & 0x3F);
        return 3;
    }
    if ((c & 0xF8) == 0xF0 && remaining >= 4)
    {
        cp = ((c & 0x07) << 18) | ((p[1] & 0x3F) << 12) | ((p[2] & 0x3F) << 6) | (p[3] & 0x3F);
        return 4;
    }
    cp = 0xFFFD;
    return 1;
}
struct NameMap
{
    const char* name;
    uint32_t cp;
};

// Some SMS apps send "(Name)" text instead of the emoji. Add more names here.
constexpr NameMap NAMES[] = {
    {"Wave", 0x1F44B},
};

size_t matchName(const uint8_t* p, size_t remaining, uint32_t& cp)
{
    if (p[0] != '(')
    {
        return 0;
    }
    for (const NameMap& m : NAMES)
    {
        const size_t len = strlen(m.name);
        if (remaining >= len + 2 && memcmp(p + 1, m.name, len) == 0 && p[len + 1] == ')')
        {
            cp = m.cp;
            return len + 2;
        }
    }
    return 0;
}

void appendUtf8(String& out, uint32_t cp)
{
    if (cp < 0x80)
    {
        out += static_cast<char>(cp);
    }
    else if (cp < 0x800)
    {
        out += static_cast<char>(0xC0 | (cp >> 6));
        out += static_cast<char>(0x80 | (cp & 0x3F));
    }
    else if (cp < 0x10000)
    {
        out += static_cast<char>(0xE0 | (cp >> 12));
        out += static_cast<char>(0x80 | ((cp >> 6) & 0x3F));
        out += static_cast<char>(0x80 | (cp & 0x3F));
    }
    else
    {
        out += static_cast<char>(0xF0 | (cp >> 18));
        out += static_cast<char>(0x80 | ((cp >> 12) & 0x3F));
        out += static_cast<char>(0x80 | ((cp >> 6) & 0x3F));
        out += static_cast<char>(0x80 | (cp & 0x3F));
    }
}
} // namespace

String uiText(const String& in)
{
    String out;
    out.reserve(in.length());

    const uint8_t* data = reinterpret_cast<const uint8_t*>(in.c_str());
    const size_t length = in.length();

    for (size_t i = 0; i < length;)
    {
        uint32_t named = 0;
        const size_t used = matchName(data + i, length - i, named);
        if (used > 0 && pulseonEmojiFind(named) != nullptr)
        {
            appendUtf8(out, named);
            i += used;
            continue;
        }

        uint32_t cp = 0;
        const size_t n = decode(data + i, length - i, cp);

        if (cp == '\n' || cp == '\r' || cp == '\t')
        {
            out += ' ';
        }
        else if (cp >= 0x20 && cp < 0x7F)
        {
            out += static_cast<char>(cp);
        }
        else if (cp >= 0x80 && pulseonEmojiFind(cp) != nullptr)
        {
            for (size_t k = 0; k < n; ++k)
            {
                out += static_cast<char>(data[i + k]);
            }
        }
        // anything else (other emoji, variation selectors, accents) is dropped

        i += n;
    }

    out.trim();
    return out;
}

const lv_font_t* uiEmojiFont(const lv_font_t* base)
{
    if (base == nullptr)
    {
        return base;
    }

    for (FontSlot& slot : slots)
    {
        if (slot.base == base)
        {
            return slot.font;
        }
    }

    for (FontSlot& slot : slots)
    {
        if (slot.base == nullptr)
        {
            lv_font_t* font = lv_imgfont_create(
                static_cast<uint16_t>(lv_font_get_line_height(base)), emojiPath, nullptr);
            if (font == nullptr)
            {
                return base;
            }
            font->fallback = base;
            slot.base = base;
            slot.font = font;
            return font;
        }
    }

    return base;
}

void uiTextWarmup()
{
    const lv_font_t* faces[3] = {font_body, font_h5, font_h3};
    for (const lv_font_t* face : faces)
    {
        uiEmojiFont(face);
    }

    auto height = [](const lv_font_t* f) { return f != nullptr ? static_cast<int>(lv_font_get_line_height(f)) : -1; };
    Serial.printf("[UI] line heights: body=%d h5=%d h3=%d | emoji images %d px\n",
                  height(font_body), height(font_h5), height(font_h3), PULSEON_EMOJI_SIZE);
}
