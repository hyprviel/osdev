#include <hw/vga.hpp>

namespace vga {

static uint8_t cursor_x_     = 0;
static uint8_t cursor_y_     = 0;
static uint8_t const WIDTH_  = 80;
static uint8_t const HEIGHT_ = 25;

static uint16_t volatile* const ADDR_ = 
    reinterpret_cast<uint16_t*>(0xB8000);

void putc(Color bg, Color fg, char ch, int x, int y) {
     uint16_t volatile* addr = ADDR_ + (y * WIDTH_ + x);
     uint16_t attr = (static_cast<uint16_t>(bg) << 4) | static_cast<uint16_t>(fg);

     *addr = (attr << 8) | ch;
}

void init() {
    for (int i = 0; i < WIDTH_ * HEIGHT_; i++) {
        cursor_x_ = i % WIDTH_;
        cursor_y_ = i / WIDTH_;
        putc(Color::Black, Color::Black, ' ', cursor_x_, cursor_y_);
    }

    cursor_x_ = 0;
    cursor_y_ = 0;
}

/**
 * @param attr: color attributes
 * @param str: the message you wanna display
 */
void print(Color bg, Color fg, const char* str) {
    while (*str != '\0') {
        if (*str == '\n') {
            cursor_y_++;
            cursor_x_ = 0;
        } else {
            putc(bg, fg, *str, cursor_x_, cursor_y_);
            cursor_x_++;
        }
        str++;
    }
}

}
