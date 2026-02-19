#pragma once

#include <lib/stdint.h>

namespace vga {
    enum class Color : uint8_t {
        Black           = 0,
        Blue            = 1,
        Green           = 2,
        Cyan            = 3,
        Red             = 4,
        Magenta         = 5,
        Brown           = 6,
        LightGray       = 7,
        DarkGray        = 8,
        LightBlue       = 9,
        LightGreen      = 10,
        LightCyan       = 11,
        LightRed        = 12,
        LightMagenta    = 13,
        LightBrown      = 14,
        White           = 15
    };

    void init();
    void putc(Color bg, Color fg, char ch, int x, int y);
    void print(Color bg, Color fg, const char* str);
}
