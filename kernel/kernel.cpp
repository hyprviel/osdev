#include <hw/vga.hpp>

extern "C" void kernel_main() {
    vga::init();
    vga::print(vga::Color::Black, vga::Color::White, "Hello, World!");
}
