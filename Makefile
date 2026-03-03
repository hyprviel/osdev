include scripts/vars.mk

.PHONY: all
all: emulate

# compile
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# link
$(ISO_DIR)/boot/kernel.elf: $(OBJ) | $(ISO_DIR)/boot/grub
	$(LD) $(LDFLAGS) $^ -o $@

$(DIST_DIR)/kernel.iso: $(ISO_DIR)/boot/kernel.elf | $(DIST_DIR)
	@echo 'set timeout=0'                   >  $(ISO_DIR)/boot/grub/grub.cfg
	@echo 'set default=0'                   >> $(ISO_DIR)/boot/grub/grub.cfg
	@echo 'menuentry "VidOS" {'             >> $(ISO_DIR)/boot/grub/grub.cfg
	@echo '  multiboot2 /boot/kernel.elf'	>> $(ISO_DIR)/boot/grub/grub.cfg
	@echo '  boot'                          >> $(ISO_DIR)/boot/grub/grub.cfg
	@echo '}'                               >> $(ISO_DIR)/boot/grub/grub.cfg

	grub-mkrescue $(ISO_DIR) -o $@

emulate: $(DIST_DIR)/kernel.iso
	qemu-system-i386 -drive format=raw,file=$<

$(BUILD_DIR) $(DIST_DIR) $(ISO_DIR)/boot/grub:
	mkdir -p $@

clean:
	rm -rf $(BUILD_DIR) $(DIST_DIR) $(ISO_DIR)
