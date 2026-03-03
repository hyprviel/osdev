#ifndef DRIVERS_VGA_HPP_
#define DRIVERS_VGA_HPP_

#include <stdint.hpp>

namespace vga {
    constexpr uint8_t width = 80;
    constexpr uint8_t height = 25;
    extern volatile uint16_t* memory;
    
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

    void clear();
    void putc(Color bg, Color fg, char ch, int x, int y);
    void puts(Color bg, Color fg, const char* str);
}

#endif // DRIVERS_VGA_HPP_DRIVERS_VGA_HPP_
