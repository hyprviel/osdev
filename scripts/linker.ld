ENTRY(_start)

PHDRS
{
    text PT_LOAD FLAGS(5);   /* r-x */
}

SECTIONS
{
    . = 1M;
    .text :
    {
        KEEP(*(.multiboot2_header))
        *(.text)
    } :text
}
