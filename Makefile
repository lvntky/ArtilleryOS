CFLAGS = -std=gnu99 \
        -ffreestanding \
        -O2 \
        -Wall \
        -Wextra \
        -I src/include \
        -I src/include/kernel \
        -m64

BUILD = build/

default: build

.PHONY: default build run clean debug

build: build/os.iso

clean:
	rm -rf build

run: build/os.iso
	qemu-system-x86_64 -cdrom build/ArtilleryOs.iso

debug: build/os.iso
	qemu-system-x86_64 -cdrom build/ArtilleryOs.iso -serial file:ArtilleryOs.log

build/os.iso: build/kernel.bin grub.cfg
	mkdir -p build/isofiles/boot/grub
	cp grub.cfg build/isofiles/boot/grub/
	cp build/kernel.bin build/isofiles/boot/
	grub-mkrescue -o build/ArtilleryOs.iso build/isofiles

build/multiboot_header.o: src/asm/multiboot_header.asm
	mkdir -p build
	nasm -f elf64 src/asm/multiboot_header.asm -o build/multiboot_header.o

build/boot.o: src/asm/boot.asm
	mkdir -p build
	nasm -f elf64 src/asm/boot.asm -o build/boot.o

build/long_mode_start.o: src/asm/long_mode_start.asm
	mkdir -p build
	nasm -f elf64 src/asm/long_mode_start.asm -o build/long_mode_start.o

build/%.o: src/%.c
	mkdir -p $(@D)
	x86_64-elf-gcc ${CFLAGS} -c $< -o $@

build/kernel.bin: build/multiboot_header.o build/boot.o build/long_mode_start.o build/kernel/kmain.o src/linker.ld
	ld -n -o build/kernel.bin -T src/linker.ld build/multiboot_header.o build/boot.o build/long_mode_start.o build/kernel/kmain.o -Map build/kernel.map
