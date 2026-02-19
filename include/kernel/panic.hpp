#pragma once

#include <hw/vga.hpp>

namespace kernel {
    using vga::Color;
        
    void panic(const char* msg) {
        asm volatile ("cli");
        vga::Writer err(Color::Black, Color::Red);
        err << "Kernel panic: " << msg;
        for (;;)
            asm volatile ("hlt");
    };
}
