#include <drivers/vga.hpp>

extern "C" void kernel_main() {
    vga::clear();
    vga::puts(vga::Color::Black, vga::Color::White, "Kernel v0.1.1-dev\nBuilt on: ");
    vga::puts(vga::Color::Black, vga::Color::White, __DATE__);
    vga::puts(vga::Color::Black, vga::Color::White, " at ");
    vga::puts(vga::Color::Black, vga::Color::White, __TIME__);
}
