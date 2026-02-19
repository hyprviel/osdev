#include <hw/vga.h>

void kernel_main() {
    vga_init();
    vga_print(vga_mkattr(VGA_COLOR_BLACK, VGA_COLOR_WHITE), "hello world!");
}
