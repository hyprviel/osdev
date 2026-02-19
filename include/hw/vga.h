#pragma once

#include <stdint.h>

extern int vga_cursor_x;
extern int vga_cursor_y;

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_ADDR (volatile uint16_t*)0xb8000

/*
 * https://wiki.osdev.org/Text_UI#Colours
 */
typedef enum {
    VGA_COLOR_BLACK,
    VGA_COLOR_BLUE,
    VGA_COLOR_GREEN,
    VGA_COLOR_CYAN,
    VGA_COLOR_RED,
    VGA_COLOR_MAGENTA,
    VGA_COLOR_BROWN,
    VGA_COLOR_LIGHT_GRAY,
    VGA_COLOR_DARK_GRAY,
    VGA_COLOR_LIGHT_BLUE,
    VGA_COLOR_LIGHT_GREEN,
    VGA_COLOR_LIGHT_CYAN,
    VGA_COLOR_LIGHT_RED,
    VGA_COLOR_LIGHT_MAGENTA,
    VGA_COLOR_LIGHT_BROWN,
    VGA_COLOR_WHITE
} color_t;

void vga_init();
void vga_putc(uint8_t attr, char ch, int x, int y);
void vga_print(uint8_t attr, char *str);

inline uint8_t vga_mkattr(uint8_t bg, uint8_t fg) {
    // 0000 0000 uint8_t bg
    // 0000 1111 uint8_t fg
    // --------- OR
    // 0000 1111 uint8_t attr
    return (bg << 4) | fg;
}
