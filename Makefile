# Toolchain prefix
CC_PREFIX = i686-elf-
NASM_PREFIX = nasm

# Compiler and linker options
CC = $(CC_PREFIX)gcc
LD = $(CC_PREFIX)ld
GAS = $(CC_PREFIX)as
CFLAGS = -std=c11 -g -ffreestanding -O2 -Wall -Wextra -I./kernel/include
LDFLAGS = -nostdlib -T linker.ld

# NASM assembler options
NASM = $(NASM_PREFIX)
NASMFLAGS = -f elf32

# Source files
KERNEL_SRCS = $(wildcard kernel/src/*.c)
LIBC_SRCS = $(wildcard kernel/libc/*.c)
SRCS = $(KERNEL_SRCS) $(LIBC_SRCS)

OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))
LOADER_ASM = bootloader/loader.asm
LOADER_OBJ = $(OBJ_DIR)/loader.o

# Output directories
OBJ_DIR = build
BIN_DIR = bin
ISO_DIR = isodir

# Target executables
KERNEL = $(BIN_DIR)/artilleryos.bin
ISO = $(BIN_DIR)/artilleryos.iso

.PHONY: all clean

all: $(ISO)

$(KERNEL): $(OBJS) $(LOADER_OBJ)
	$(LD) $(LDFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: kernel/src/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: kernel/libc/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LOADER_OBJ): $(LOADER_ASM) | $(OBJ_DIR)
	$(GAS) -march=i386 $< -o $@

$(ISO): $(KERNEL)
	mkdir -p $(ISO_DIR)/boot/grub
	cp $< $(ISO_DIR)/boot/artilleryos.bin
	cp ./boot/grub.cfg $(ISO_DIR)/boot/grub
	grub-mkrescue -o $@ $(ISO_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)/* $(BIN_DIR)/* $(ISO)
	rm -rf /isodir/boot/artilleryos.bin
