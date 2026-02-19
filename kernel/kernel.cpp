/**
 * kernel.cpp
 * Author: Jeffrey E. <jeevacation@gmail.com>
 */

#include <hw/vga.hpp>
#include <kernel/panic.hpp>

using vga::Color;

extern "C" void kernel_main() {
    vga::init();

    vga::Writer out(Color::Black, Color::White);
    out << "Hello, world!\n";
}

