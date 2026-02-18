#include <vga.h>

int cursor_x;
int cursor_y;

void putc(uint8_t attr, char ch, int x, int y) {
     volatile uint16_t *addr = VGA_ADDR + (y * VGA_WIDTH + x);
     *addr = (attr << 8) | ch;
}

/**
 * @param attr: color attributes (refer to the wiki - https://wiki.osdev.org/Text_UI#Colours)
 * @param str: the message you wanna display
 */
void _print(uint8_t attr, char *str) {
    volatile uint16_t *vga = VGA_ADDR;

    while (*str != '\0') {
        if (*str == '\n') {
            cursor_y = cursor_x / VGA_WIDTH;
            cursor_x = (cursor_y + 1) * VGA_WIDTH;
        } else {
            // 0000 1111 0000 0000 uint16_t attr
            // 0000 0000 0100 0001 uint16_t ch
            // ------------------- OR
            // 0000 1111 0100 0001 uint16_t res
            vga[cursor_x] = (uint16_t)((attr << 8) | *str);
            cursor_x++;
        }
        str++;
    }
}

void print(uint8_t attr, char *str) {
    while (*str != '\0') {
        if (*str == '\n') {
            cursor_y++;
            cursor_x = 0;
        } else {
            putc(attr, *str, cursor_x, cursor_y);
            cursor_x++;
        }
        str++;
    }
}
