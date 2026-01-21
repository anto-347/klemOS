BOOT_DIR = boot
KERNEL_DIR = kernel
BUILD_DIR = build
BUILD_BIN_DIR = $(BUILD_DIR)/bin
BUILD_OBJ_DIR = $(BUILD_DIR)/obj


BOOTLOADER_SRC = $(BOOT_DIR)/bootloader.asm
KERNEL_ENTRY_SRC = $(KERNEL_DIR)/kernel_entry.asm
KERNEL_C_SRCS = $(shell find $(KERNEL_DIR) -name '*.c')
KERNEL_ASM_SRCS = $(filter-out $(KERNEL_ENTRY_SRC), $(shell find $(KERNEL_DIR) -name '*.asm'))
KERNEL_ASM_OBJS = $(patsubst $(KERNEL_DIR)/%.asm, $(BUILD_OBJ_DIR)/%.o, $(KERNEL_ASM_SRCS))


KERNEL_ENTRY_OBJ = $(BUILD_OBJ_DIR)/kernel_entry.o
KERNEL_C_OBJS = $(patsubst $(KERNEL_DIR)/%.c, $(BUILD_OBJ_DIR)/%.o, $(KERNEL_C_SRCS))


CFLAGS = -m32 -ffreestanding -fno-pie -fno-pic -nostdlib -fno-stack-protector -I$(KERNEL_DIR) -Iinclude


all: $(BUILD_BIN_DIR)/os.img


$(BUILD_BIN_DIR)/bootloader.bin: $(BOOTLOADER_SRC) | $(BUILD_BIN_DIR)
	nasm -f bin $< -o $@


$(KERNEL_ENTRY_OBJ): $(KERNEL_ENTRY_SRC) | $(BUILD_OBJ_DIR)
	nasm -f elf32 $< -o $@


$(BUILD_OBJ_DIR)/%.o: $(KERNEL_DIR)/%.c | $(BUILD_OBJ_DIR)
	@mkdir -p $(dir $@)
	gcc $(CFLAGS) -c $< -o $@


$(BUILD_BIN_DIR)/kernel.bin: $(KERNEL_ENTRY_OBJ) $(KERNEL_C_OBJS) $(KERNEL_ASM_OBJS) linker.ld | $(BUILD_BIN_DIR)
	ld -m elf_i386 -T linker.ld -o $@ $(KERNEL_ENTRY_OBJ) $(KERNEL_C_OBJS) $(KERNEL_ASM_OBJS) --oformat binary
	truncate -s 8192 $@

$(BUILD_OBJ_DIR)/%.o: $(KERNEL_DIR)/%.asm | $(BUILD_OBJ_DIR)
	@mkdir -p $(dir $@)
	nasm -f elf32 $< -o $@

$(BUILD_BIN_DIR)/os.img: $(BUILD_BIN_DIR)/bootloader.bin $(BUILD_BIN_DIR)/kernel.bin
	cat $^ > $@

clean:
	rm -rf $(BUILD_BIN_DIR)/*
	rm -rf $(BUILD_OBJ_DIR)/*

run: $(BUILD_BIN_DIR)/os.img
	qemu-system-i386 -drive file=$<,format=raw

# Debug
debug-files:
	@echo "Sources C trouvés :"
	@echo $(KERNEL_C_SRCS)
	@echo ""
	@echo "Sources ASM trouvés : "
	@echo $(KERNEL_ASM_SRCS)
	@echo ""
	@echo "Objets C qui seront créés :"
	@echo $(KERNEL_C_OBJS)
	@echo ""
	@echo "Objets ASM qui seront créés : "
	@echo $(KERNEL_ASM_OBJS)

.PHONY: all clean run debug-files