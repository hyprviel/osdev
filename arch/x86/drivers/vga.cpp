#include <hw/vga.hpp>

namespace vga {

static uint8_t cursor_x     = 0;
static uint8_t cursor_y     = 0;
static uint8_t const WIDTH  = 80;
static uint8_t const HEIGHT = 25;

static uint16_t volatile* const ADDR = 
    reinterpret_cast<uint16_t*>(0xB8000);

void clear() {
    for (int i = 0; i < WIDTH * HEIGHT; i++) {
        ADDR[i] = 0x0000 | ' ';
    }
}

void init() { clear(); }

void putc(Color bg, Color fg, char ch, int x, int y) {
     uint16_t volatile* addr = ADDR + (y * WIDTH + x);
     uint16_t attr = (static_cast<uint16_t>(bg) << 4) |
                    static_cast<uint16_t>(fg);

     *addr = (attr << 8) | ch;
}

/*void init() {
    for (int i = 0; i < WIDTH * HEIGHT; i++) {
        ADDR[i] = 0x0000 | ' ';
    }
}*/

/**
 * @param attr: color attributes
 * @param str: the message you wanna display
 */
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

// SCOTLAND FOREVER

Writer::Writer(Color bg, Color fg) :
    bg_(bg), fg_(fg) {}
                                      
Writer& Writer::operator<<(const char* str) {
    puts(bg_, fg_, str);
    return *this;
}

Writer& Writer::operator<<(const char ch) {
    putc(bg_, fg_, ch, cursor_x, cursor_y);
    return *this;
}

}
