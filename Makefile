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

C_FLAGS = -m32 -ffreestanding -fno-pie -fno-pic -nostdlib -fno-stack-protector

all: $(OS_IMG)

$(BOOTLOADER_BIN): $(BOOTLOADER_SRC) | $(BUILD_DIR)/bin
	nasm -f bin $< -o $@

$(KERNEL_ENTRY_OBJ): $(KERNEL_ENTRY_SRC) | $(BUILD_DIR)/obj
	nasm -f elf32 $< -o $@

$(KERNEL_C_OBJ): $(KERNEL_C_SRC) | $(BUILD_DIR)/obj
	gcc $(C_FLAGS) -c $< -o $@

$(KERNEL_BIN): $(KERNEL_ENTRY_OBJ) $(KERNEL_C_OBJ) linker.ld | $(BUILD_DIR)/bin
	ld -m elf_i386 -T linker.ld -o $@ $(KERNEL_ENTRY_OBJ) $(KERNEL_C_OBJ) --oformat binary
	truncate -s 8192 $@

$(OS_IMG): $(BOOTLOADER_BIN) $(KERNEL_BIN)
	cat $^ > $@


clean:
	rm -rf $(BUILD_DIR)/bin/*
	rm -rf $(BUILD_DIR)/obj/*

run: $(OS_IMG)
	qemu-system-i386 -drive format=raw,file=$^

.PHONY: all clean run