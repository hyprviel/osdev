include config.mk

BUILD_DIR := build
DIST_DIR := dist
ISO_DIR := iso

C_SRC := $(shell find kernel arch/x86 -name "*.c")
C_OBJ := $(addprefix $(BUILD_DIR)/, $(notdir $(C_SRC:.c=.o)))

S_SRC := $(shell find arch/x86 -name "*.s")
S_OBJ := $(addprefix $(BUILD_DIR)/, $(notdir $(S_SRC:.s=.o)))

.PHONY: all clean

all: emulate
	mkdir -p $(BUILD_DIR) $(ISO_DIR)/grub $(DIST_DIR)

# assemble
vpath %.s $(sort $(dir $(S_SRC)))
$(BUILD_DIR)/%.o: %.s
	$(AS) $(ASFLAGS) -c $< -o $@

# compile
vpath %.c $(sort $(dir $(C_SRC)))
$(BUILD_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# link
$(BUILD_DIR)/kernel.elf: $(C_OBJ) $(S_OBJ)
	$(LD) $(LDFLAGS) $^ -o $@

# build iso
$(DIST_DIR)/kernel.iso: $(BUILD_DIR)/kernel.elf
	cp $< $(ISO_DIR)/boot/kernel.elf

	@echo 'set timeout=0'                      >> $(ISO_DIR)/boot/grub/grub.cfg
	@echo 'set default=0'                      >> $(ISO_DIR)/boot/grub/grub.cfg
	@echo 'menuentry "My OS" {'                >> $(ISO_DIR)/boot/grub/grub.cfg
	@echo '  multiboot /boot/kernel.elf'       >> $(ISO_DIR)/boot/grub/grub.cfg
	@echo '  boot'                             >> $(ISO_DIR)/boot/grub/grub.cfg
	@echo '}'                                  >> $(ISO_DIR)/boot/grub/grub.cfg

	grub-mkrescue iso -o $@

# run iso
emulate: $(DIST_DIR)/kernel.iso
	qemu-system-i386 -drive format=raw,file=$<

clean:
	rm -rf $(BUILD_DIR) $(DIST_DIR) $(ISO_DIR)
