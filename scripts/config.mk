ARCH := x86
BITS = 32

AS      := gcc
ASFLAGS := -m$(BITS) -ffreestanding

CXX      := g++
CXXFLAGS := -m$(BITS) -ffreestanding -fno-stack-protector -O2 -Wall -Wextra -Iinclude

LD      := gcc
LDFLAGS := -m$(BITS) -nostdlib -T scripts/linker.ld
