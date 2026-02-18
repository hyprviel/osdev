include config.mk

BUILD_DIR = build

C_SRC := $(shell find kernel arch/x86 -name "*.c")
C_OBJ := $(addprefix $(BUILD_DIR)/, $(notdir $(C_SRC:.c=.o)))

ASM_SRC := $(shell find arch/x86 -name "*.s")
ASM_OBJ := $(addprefix $(BUILD_DIR)/, $(notdir $(ASM_SRC:.s=.o)))

.PHONY: all clean

# Rule utama
all: emulate

# assemble
vpath %.s $(sort $(dir $(ASM_SRC)))
$(BUILD_DIR)/%.o: %.s
	$(AS) $(ASFLAGS) -c $< -o $@

# compile
vpath %.c $(sort $(dir $(C_SRC)))
$(BUILD_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# link
iso/boot/kernel.elf: $(C_OBJ) $(ASM_OBJ)
	$(LD) $(LDFLAGS) $^ -o $@

kernel.iso: iso/boot/kernel.elf
	grub-mkrescue iso -o $@

emulate: kernel.iso
	qemu-system-i386 -drive format=raw,file=$<

clean:
	rm -rf $(BUILD_DIR)/*
