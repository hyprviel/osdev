include scripts/config.mk

BUILD_DIR := build
DIST_DIR := dist
ISO_DIR := iso

C_SRC := $(shell find kernel arch/x86 -name "*.cpp")
C_OBJ := $(addprefix $(BUILD_DIR)/, $(notdir $(C_SRC:.cpp=.o)))

S_SRC := $(shell find arch/x86 -name "*.s")
S_OBJ := $(addprefix $(BUILD_DIR)/, $(notdir $(S_SRC:.s=.o)))

.PHONY: all clean emulate

all: emulate

# assemble
vpath %.s $(sort $(dir $(S_SRC)))
$(BUILD_DIR)/%.o: %.s | $(BUILD_DIR)
	$(AS) $(ASFLAGS) -c $< -o $@

# compile
vpath %.cpp $(sort $(dir $(C_SRC)))
$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# link
$(BUILD_DIR)/kernel.elf: $(C_OBJ) $(S_OBJ) | $(BUILD_DIR)
	$(LD) $(LDFLAGS) $^ -o $@

# build iso
$(DIST_DIR)/kernel.iso: $(BUILD_DIR)/kernel.elf | $(ISO_DIR)/boot/grub $(DIST_DIR)
	@cp $< $(ISO_DIR)/boot/kernel.elf

	@echo 'set timeout=0'                   >  $(ISO_DIR)/boot/grub/grub.cfg
	@echo 'set default=0'                   >> $(ISO_DIR)/boot/grub/grub.cfg
	@echo 'menuentry "VidOS" {'             >> $(ISO_DIR)/boot/grub/grub.cfg
	@echo '  multiboot2 /boot/kernel.elf'	>> $(ISO_DIR)/boot/grub/grub.cfg
	@echo '  boot'                          >> $(ISO_DIR)/boot/grub/grub.cfg
	@echo '}'                               >> $(ISO_DIR)/boot/grub/grub.cfg

	grub-mkrescue $(ISO_DIR) -o $@

# run iso
emulate: $(DIST_DIR)/kernel.iso | $(DIST_DIR)
	qemu-system-i386 -drive format=raw,file=$<

$(BUILD_DIR) $(DIST_DIR) $(ISO_DIR)/boot/grub:
	mkdir -p $@

clean:
	rm -rf $(BUILD_DIR) $(DIST_DIR) $(ISO_DIR)
