.code32
.globl _start

.section .multiboot_header,"",@progbits
.align 8

header_start:
    # magic number
    .long 0xe85250d6 # multiboot2

    # architecture
    .long 0 # protected mode

    # header length
    .long header_end - header_start

    # checksum -(magic + arch + size)
    .long -(0xe85250d6 + 0 + (header_end - header_start))

    # end tag
    .long 0 # type
    .long 8 # size
header_end:

.section .note.GNU-stack,"",@progbits

.section .text,"",@progbits
.extern kernel_main

_start:
    call kernel_main
    cli
.halt:
    hlt
    jmp .halt
