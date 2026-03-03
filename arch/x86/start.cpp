using uint32_t = __UINT32_TYPE__;

struct __attribute__((packed)) Header {
    uint32_t magic;
    uint32_t arch;
    uint32_t length;
    uint32_t checksum;
    uint32_t end_tag_type;
    uint32_t end_tag_size;
};

__attribute__((section(".multiboot2_header"),aligned(8)))
Header header = {
    .magic = 0xe85250d6,
    .arch = 0, // x86 protected mode
    .length = sizeof(Header),
    // -(magic + arch + length)
    .checksum = -(0xe85250d6 + 0 + sizeof(Header)),
    .end_tag_type = 0,
    .end_tag_size = 8
};

extern "C" {
    void kernel_main();
 
    __attribute((noreturn))
    void _start() {
        kernel_main();
        __asm__ volatile ("cli");
        for (;;)
            __asm__ volatile ("hlt");
    }
}
