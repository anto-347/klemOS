BOOT_DIR = boot
KERNEL_DIR = kernel
BUILD_DIR = build

BOOTLOADER_SRC = $(BOOT_DIR)/bootloader.asm
KERNEL_ENTRY_SRC = $(KERNEL_DIR)/kernel_entry.asm
KERNEL_C_SRC = $(KERNEL_DIR)/main.c

BOOTLOADER_BIN = $(BUILD_DIR)/bin/bootloader.bin
KERNEL_ENTRY_OBJ = $(BUILD_DIR)/obj/kernel_entry.o
KERNEL_C_OBJ = $(BUILD_DIR)/obj/main.o
KERNEL_BIN = $(BUILD_DIR)/bin/kernel.bin
OS_IMG = $(BUILD_DIR)/bin/os.img

all: $(OS_IMG)

$(BOOTLOADER_BIN): $(BOOTLOADER_SRC) | $(BUILD_DIR)
	nasm -f bin $< -o $@

$(KERNEL_ENTRY_OBJ): $(KERNEL_ENTRY_SRC) | $(BUILD_DIR)
	nasm -f elf32 $< -o $@

$(KERNEL_C_OBJ): $(KERNEL_C_SRC) | $(BUILD_DIR)
	gcc -m32 -ffreestanding -c $< -o $@

$(KERNEL_BIN): $(KERNEL_ENTRY_OBJ) $(KERNEL_C_OBJ) linker.ld | $(BUILD_DIR)
	ld -m elf_i386 -T linker.ld -o $@ $(KERNEL_ENTRY_OBJ) $(KERNEL_C_OBJ) --oformat binary

$(OS_IMG): $(BOOTLOADER_BIN) $(KERNEL_BIN)
	cat $(BOOTLOADER_BIN) $(KERNEL_BIN) > $@


clean:
	rm -rf $(BUILD_DIR)

run: $(OS_IMG)
	qemu-system-i386 -drive format=raw, file=$(OS_IMG)

.PHONY: all clean run