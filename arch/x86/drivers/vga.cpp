#include <drivers/vga.hpp>

namespace vga {

static uint8_t cursor_x = 0;
static uint8_t cursor_y = 0;
volatile uint16_t* memory =
    reinterpret_cast<volatile uint16_t*>(0xb8000);

void clear() {
    for (uint16_t i = 0; i < width * height; i++) {
        memory[i] = 0x0020;
    }
}

void putc(Color bg, Color fg, char ch, int x, int y) {
     uint16_t volatile* addr = memory + (y * width + x);
     uint16_t attr = (static_cast<uint16_t>(bg) << 4) |
                    static_cast<uint16_t>(fg);

     *addr = (attr << 8) | ch;
}

void puts(Color bg, Color fg, const char* str) {
    while (*str != '\0') {
        if (*str == '\n') {
            cursor_y++;
            cursor_x = 0;
        } else {
            putc(bg, fg, *str, cursor_x, cursor_y);
            cursor_x++;
        }
        str++;
    }
}

}

