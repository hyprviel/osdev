ARCH := x86
BITS = 32

AS      := gcc
ASFLAGS := -m$(BITS) -ffreestanding

CXX      := g++
CXXFLAGS := -m$(BITS) -ffreestanding -O2 -Wall -Iinclude

LD      := gcc
LDFLAGS := -m$(BITS) -nostdlib -no-pie -T scripts/linker.ld
