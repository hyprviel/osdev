#include <hw/vga.h>

int vga_cursor_x;
int vga_cursor_y;

void vga_putc(uint8_t attr, char ch, int x, int y) {
     volatile uint16_t *addr = VGA_ADDR + (y * VGA_WIDTH + x);
     *addr = (attr << 8) | ch;
}

void vga_init() {
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
        vga_cursor_x = i % VGA_WIDTH;
        vga_cursor_y = i / VGA_WIDTH;

        vga_putc(vga_mkattr(VGA_COLOR_BLACK, VGA_COLOR_BLACK), ' ', vga_cursor_x, vga_cursor_y);
    }

    vga_cursor_x = 0;
    vga_cursor_y = 0;
}

/**
 * @param attr: color attributes
 * @param str: the message you wanna display
 */
void vga_print(uint8_t attr, char *str) {
    while (*str != '\0') {
        if (*str == '\n') {
            vga_cursor_y++;
            vga_cursor_x = 0;
        } else {
            vga_putc(attr, *str, vga_cursor_x, vga_cursor_y);
            vga_cursor_x++;
        }
        str++;
    }
}
