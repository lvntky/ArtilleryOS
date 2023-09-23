FILES = ./build/kernel.asm.o ./build/kernel.o ./build/tty.o ./build/stdio.o ./build/string.o ./build/idt.asm.o ./build/idt.o ./build/cpu_info.o
INCLUDES = -I./src
FLAGS = -g -ffreestanding -falign-jumps -falign-functions -falign-labels -falign-loops -fstrength-reduce -fomit-frame-pointer -finline-functions -Wno-unused-function -fno-builtin -Werror -Wno-unused-label -Wno-cpp -Wno-unused-parameter -nostdlib -nostartfiles -nodefaultlibs -Wall -O0 -Iinc

all: ./bin/boot.bin ./bin/kernel.bin
	rm -rf ./bin/artilleryos.bin
	dd if=./bin/boot.bin >> ./bin/artilleryos.bin
	dd if=./bin/kernel.bin >> ./bin/artilleryos.bin
	dd if=/dev/zero bs=512 count=100 >> ./bin/artilleryos.bin

./bin/kernel.bin: $(FILES)
	i686-elf-ld -g -relocatable $(FILES) -o ./build/kernel_bootloader_combined.o
	i686-elf-gcc $(FLAGS) -T ./kernel/linker.ld -o ./bin/kernel.bin -ffreestanding -O0 -nostdlib ./build/kernel_bootloader_combined.o

./bin/boot.bin: ./boot/boot.asm
	nasm -f bin ./boot/boot.asm -o ./bin/boot.bin

./build/kernel.asm.o: ./boot/kernel_entry.asm
	nasm -f elf -g ./boot/kernel_entry.asm -o ./build/kernel.asm.o

./build/kernel.o: ./kernel/src/kernel.c
	i686-elf-gcc $(INCLUDES) $(FLAGS) -std=gnu99 -c ./kernel/src/kernel.c -o ./build/kernel.o

./build/tty.o: ./kernel/src/tty.c
	i686-elf-gcc $(INCLUDES) $(FLAGS) -std=gnu99 -c ./kernel/src/tty.c -o ./build/tty.o

./build/stdio.o: ./kernel/libc/stdio.c
	i686-elf-gcc $(INCLUDES) $(FLAGS) -std=gnu99 -c ./kernel/libc/stdio.c -o ./build/stdio.o

./build/string.o: ./kernel/libc/string.c
	i686-elf-gcc $(INCLUDES) $(FLAGS) -std=gnu99 -c ./kernel/libc/string.c -o ./build/string.o

./build/idt.asm.o: ./kernel/idt/idt.asm
	nasm -f elf -g ./kernel/idt/idt.asm -o ./build/idt.asm.o

./build/idt.o: ./kernel/idt/idt.c
	i686-elf-gcc $(INCLUDES) $(FLAGS) -std=gnu99 -c ./kernel/idt/idt.c -o ./build/idt.o

./build/cpu_info.o: ./kernel/src/cpu_info.c
	i686-elf-gcc $(INCLUDES) $(FLAGS) -std=gnu99 -c ./kernel/src/cpu_info.c -o ./build/cpu_info.o

clean:
	rm -rf ./bin/boot.bin
	rm -rf ./bin/kernel.bin
	rm -rf ./bin/artilleryos.bin
	rm -rf ${FILES}
	rm -rf ./build/kernel_bootloader_combined.o