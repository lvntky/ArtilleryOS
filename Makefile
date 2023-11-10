CFLAGS = -m32 -g -ffreestanding -falign-jumps -falign-functions -falign-labels -falign-loops -fstrength-reduce -fomit-frame-pointer -finline-functions -Wno-unused-function -fno-builtin -Werror -Wno-unused-label -Wno-cpp -Wno-unused-parameter -nostdlib -nostartfiles -nodefaultlibs -Wall -O0 -Iinc
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
          ./build/render_font.o \
          ./build/panic.o \
          ./build/render_image.o \

_mkdir := $(shell mkdir -p build)

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

build/%.o: kernel/memory/src/%.c
	i686-elf-gcc $(CFLAGS) -c -o $@ $<

# LOADER ASM
build/%.o: boot/%.asm
	nasm -f elf32 -o $@ $<

kernel.elf: linker.ld $(objects)
	i686-elf-ld $(LDPARAMS) -T $< -o $@ $(objects)

all: kernel.elf
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	cp kernel.elf iso/boot/kernel.elf
	echo 'set timeout=10'                      > iso/boot/grub/grub.cfg
	echo 'set default=0'                     >> iso/boot/grub/grub.cfg
	echo ''                                  >> iso/boot/grub/grub.cfg
	echo 'menuentry "Artillery OS" {' >> iso/boot/grub/grub.cfg
	echo '  multiboot /boot/kernel.elf'    >> iso/boot/grub/grub.cfg
	echo '  boot'                            >> iso/boot/grub/grub.cfg
	echo '}'                                 >> iso/boot/grub/grub.cfg
	grub-mkrescue --output=artillery.iso iso
	rm -rf iso

install: kernel.elf
	sudo cp $< /boot/mykernel.elf

clean:
	rm -rf ./iso/
	rm -rf ./build/
	rm -f kernel.elf
	rm -f artillery.iso
