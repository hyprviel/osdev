ENTRY(_start)

PHDRS
{
  text PT_LOAD FLAGS(5);   /* r-x */
  data PT_LOAD FLAGS(6);   /* rw- */
}

SECTIONS
{
    . = 1M;

    .text :
    {
        KEEP(*(.multiboot_header))
        *(.text)
    } : text
}

