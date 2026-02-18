#include <vga.h>

void kernel_main() {
    print(mk_attr(BLACK, WHITE), "hello world!");
}
