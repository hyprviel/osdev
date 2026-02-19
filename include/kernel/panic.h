#pragma once

#include <hw/vga.hpp>

namespace kernel {
    void panic(const char* msg) {
        vga::print(vga::Color::Black, vga::Color::Red, "Kernel panic: ");
        vga::print(vga::Color::Black, vga::Color::Red, msg);
    };
}
