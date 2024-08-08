# Cross-compiler prefix
CROSS = x86_64-elf-

# Directories
ISO_DIR = iso
BOOT_DIR = $(ISO_DIR)/boot
GRUB_DIR = $(BOOT_DIR)/grub

# Files
KERNEL = kernel.bin
ISO = BabOSco.iso
GRUB_CFG = grub.cfg

# Compiler and linker flags
CFLAGS = -ffreestanding -O2 -Wall -Wextra
LDFLAGS = -T linker.ld -ffreestanding -O2 -nostdlib

# Targets
all: build run

build: $(ISO)

$(KERNEL): kernel.c
	$(CROSS)gcc -c $< -o kernel.o $(CFLAGS)
	$(CROSS)gcc $(LDFLAGS) kernel.o -o $@ -lgcc

$(ISO): $(KERNEL) $(GRUB_CFG)
	mkdir -p $(GRUB_DIR)
	cp $(KERNEL) $(BOOT_DIR)/$(KERNEL)
	cp $(GRUB_CFG) $(GRUB_DIR)/$(GRUB_CFG)
	grub-mkrescue -o $@ $(ISO_DIR)

run:
	qemu-system-x86_64 -cdrom $(ISO)

clean:
	rm -rf $(ISO_DIR) $(KERNEL) kernel.o $(ISO)

.PHONY: all build run clean