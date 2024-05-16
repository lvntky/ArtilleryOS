CFLAGS = -m32 -ggdb -ffreestanding -falign-jumps -falign-functions -falign-labels -falign-loops -fstrength-reduce -fomit-frame-pointer -finline-functions -Wno-unused-function -fno-builtin -Werror -Wno-unused-label -Wno-cpp -Wno-unused-parameter -nostdlib -nostartfiles -nodefaultlibs -Wall -O0 -Iinc
TESTING_CFLAGS = -m32 -ggdb -ffreestanding -falign-jumps -falign-functions -falign-labels -falign-loops -fstrength-reduce -fomit-frame-pointer -finline-functions -Wno-unused-function -fno-builtin -Werror -Wno-unused-label -Wno-cpp -Wno-unused-parameter -Wall -O0 -Iinc
ASPARAMS = --32
LDPARAMS = -melf_i386 -g

objects = ./build/loader.o \
          ./build/kernel.o \
          ./build/tty.o \
		  ./build/multiboot_util.o \
          ./build/stdio.o \
		  ./build/qemu_debug.o \
          ./build/cpu_info.o \
          ./build/string.o \
          ./build/io_port.o \
          ./build/vga_driver.o \
          ./build/pic.o \
		  ./build/gdt_flush.o \
          ./build/gdt.o \
		  ./build/idt_flush.o \
		  ./build/idt.o \
		  ./build/exception_helper.o \
		  ./build/exception.o \
		  ./build/interrupt_helper.o \
		  ./build/interrupt.o \
		  ./build/tss_flush.o \
		  ./build/tss.o \
		  ./build/timer.o \
		  ./build/keyboard.o \
		  ./build/paging_enable.o \
		  ./build/paging.o \
		  ./build/kernel_heap.o \
          ./build/render_font.o \
          ./build/panic.o \
		  ./build/options.o \
          ./build/render_image.o \
		  ./build/tty_cursor.o \
		  ./build/multiboot_module.o \
		  ./build/art_linked_list.o \
		  ./build/cmos.o \
		  ./build/math.o \
		  ./build/stdlib.o \
		  ./build/bresenham.o \
		  ./build/tempfs.o \
		  ./build/tempfs_initrd.o \

_mkdir := $(shell mkdir -p build)

# LIBC TESTING 
testing:
	gcc -o libc_testing kernel/libc/stdlib.c tests/libc/stdlib_test.c

# BASE KERNEL SOURCE
build/%.o: kernel/src/%.c
	i686-elf-gcc $(CFLAGS) -c -o $@ $<

# LIBC
build/%.o: kernel/libc/%.c
	i686-elf-gcc $(CFLAGS) -c -o $@ $<

# Driver
build/%.o: kernel/driver/%.c
	i686-elf-gcc $(CFLAGS) -c -o $@ $<

# Descriptor tables
build/%.o: kernel/descriptor_tables/asm/%.asm
	nasm -f elf32 -o $@ $<

build/%.o: kernel/descriptor_tables/src/%.c
	i686-elf-gcc $(CFLAGS) -c -o $@ $<

# GUI
build/%.o: gui/%.c
	i686-elf-gcc $(CFLAGS) -c -o $@ $<
	
# MEMORY
build/%.o: kernel/memory/asm/%.asm
	nasm -f elf32 -o $@ $<

# FILE SYSTEM
build/%.o: kernel/fs/tempfs/%.c
	i686-elf-gcc $(CFLAGS) -c -o $@ $<

# UTIL
build/%.o: util/%.c
	i686-elf-gcc $(CFLAGS) -c -o $@ $<

build/%.o: kernel/memory/src/%.c
	i686-elf-gcc $(CFLAGS) -c -o $@ $<

# LOADER ASM
build/%.o: boot/%.asm
	nasm -f elf32 -o $@ $<

kernel.elf: linker.ld $(objects)
	i686-elf-ld $(LDPARAMS) -T $< -o $@ $(objects)

all: kernel.elf

install: kernel.elf
	sudo cp $< /boot/mykernel.elf

iso: kernel.elf
	./scripts/create_iso.sh

clean:
	rm -rf ./iso/
	rm -rf ./build/
	rm -f kernel.elf
	rm -f artillery.iso
