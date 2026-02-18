#pragma once

#include <stdint.h>

extern int cursor_x;
extern int cursor_y;

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_ADDR (volatile uint16_t*)0xb8000

enum Color {
    BLACK,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    LIGHT_GRAY,

    DARK_GRAY,
    LIGHT_BLUE,
    LIGHT_GREEN,
    LIGHT_CYAN,
    LIGHT_RED,
    LIGHT_MAGENTA,
    LIGHT_BROWN,
    WHITE
};

inline uint8_t mk_attr(uint8_t bg, uint8_t fg) {
    // 0000 0000 uint8_t bg
    // 0000 1111 uint8_t fg
    // --------- OR
    // 0000 1111 uint8_t attr
    return (bg << 4) | fg;
}

void puts(uint8_t attr, char* str);
void putc(uint8_t attr, char ch, int x, int y);
void _print(uint8_t attr, char *str); // deprecated
void print(uint8_t attr, char *str);
