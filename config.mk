ARCH := x86

AS := gcc
ASFLAGS := -m32 -ffreestanding

CC := gcc
CFLAGS := -m32 -ffreestanding -O2 -Wall -Iinclude

LD := gcc
LDFLAGS := -m32 -nostdlib -Tscripts/linker.ld
