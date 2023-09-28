CFLAGS = -m32 -ffreestanding -falign-jumps -falign-functions -falign-labels -falign-loops -fstrength-reduce -fomit-frame-pointer -finline-functions -Wno-unused-function -fno-builtin -Werror -Wno-unused-label -Wno-cpp -Wno-unused-parameter -nostdlib -nostartfiles -nodefaultlibs -Wall -O0 -Iinc
ASPARAMS = --32
LDPARAMS = -melf_i386

objects = build/loader.o build/kernel.o build/tty.o build/stdio.o build/cpu_info.o build/string.o build/io_port.o ./build/vga_driver.o



build/%.o: kernel/src/%.c
	i686-elf-gcc $(CFLAGS) -c -o $@ $<

build/%.o: kernel/libc/%.c
	i686-elf-gcc $(CFLAGS) -c -o $@ $<

build/%.o: kernel/driver/%.c
	i686-elf-gcc $(CFLAGS) -c -o $@ $<

build/%.o: boot/%.s
	i686-elf-as $(ASPARAMS) -o $@ $<

kernel.bin: linker.ld $(objects)
	i686-elf-ld $(LDPARAMS) -T $< -o $@ $(objects)

all: kernel.bin
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	cp kernel.bin iso/boot/kernel.bin
	echo 'set timeout=10'                      > iso/boot/grub/grub.cfg
	echo 'set default=0'                     >> iso/boot/grub/grub.cfg
	echo ''                                  >> iso/boot/grub/grub.cfg
	echo 'menuentry "Artillery OS" {' >> iso/boot/grub/grub.cfg
	echo '  multiboot /boot/kernel.bin'    >> iso/boot/grub/grub.cfg
	echo '  boot'                            >> iso/boot/grub/grub.cfg
	echo '}'                                 >> iso/boot/grub/grub.cfg
	grub-mkrescue --output=artillery.iso iso
	rm -rf iso

install: kernel.bin
	sudo cp $< /boot/mykernel.bin

clean:
	sudo rm -r ./build/*
	sudo rm -r kernel.bin
	sudo rm -r artillery.iso

