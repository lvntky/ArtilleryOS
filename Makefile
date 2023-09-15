FILES = ./build/kernel.asm.o ./build/kernel.o ./build/tty.o ./build/idt.asm.o ./build/idt.o ./build/memory_util.o ./build/ll_io.o
INCLUDES = -I./kernel/include -I./kernel/libc
FLAGS = -g -ffreestanding -falign-jumps -falign-functions -falign-labels -falign-loops -fstrength-reduce -fomit-frame-pointer -finline-functions -Wno-unused-function -fno-builtin -Werror -Wno-unused-label -Wno-cpp -Wno-unused-parameter -nostdlib -nostartfiles -nodefaultlibs -Wall -O0 -Iinc
all: ./bin/boot.bin ./bin/kernel.bin
	rm -rf ./bin/artillery.bin
	dd if=./bin/boot.bin >> ./bin/artillery.bin
	dd if=./bin/kernel.bin >> ./bin/artillery.bin
	dd if=/dev/zero bs=512 count=100 >> ./bin/artillery.bin

./bin/kernel.bin: $(FILES)
	i686-elf-ld -g -relocatable $(FILES) -o ./build/kernelfull.o
	i686-elf-gcc $(FLAGS) -T ./toolchain/linker.ld -o ./bin/kernel.bin -ffreestanding -O0 -nostdlib ./build/kernelfull.o

./bin/boot.bin: ./kernel/arch/x86_64/bootloader.asm
	nasm -f bin ./kernel/arch/x86_64/bootloader.asm -o ./bin/boot.bin

./build/kernel.asm.o: ./kernel/arch/x86_64/kernel.asm
	nasm -f elf -g ./kernel/arch/x86_64/kernel.asm -o ./build/kernel.asm.o

./build/kernel.o: ./kernel/src/kernel.c
	i686-elf-gcc $(INCLUDES) $(FLAGS) -std=gnu99 -c ./kernel/src/kernel.c -o ./build/kernel.o

./build/tty.o : ./kernel/src/tty.c
	i686-elf-gcc $(INCLUDES) $(FLAGS) -std=gnu99 -c ./kernel/src/tty.c -o ./build/tty.o

./build/idt.asm.o: ./kernel/arch/x86_64/idt.asm
	nasm -f elf -g ./kernel/arch/x86_64/idt.asm -o ./build/idt.asm.o

 ./build/idt.o: ./kernel/src/idt.c
	i686-elf-gcc $(INCLUDES) $(FLAGS) -std=gnu99 -c ./kernel/src/idt.c -o ./build/idt.o
 
./build/memory_util.o: ./kernel/src/memory_util.c
	i686-elf-gcc $(INCLUDES) $(FLAGS) -std=gnu99 -c ./kernel/src/memory_util.c -o ./build/memory_util.o

./build/ll_io.o: ./kernel/src/ll_io.c
	i686-elf-gcc $(INCLUDES) $(FLAGS) -std=gnu99 -c ./kernel/src/ll_io.c -o ./build/ll_io.o

clean:
	rm -rf ./bin/boot.bin
	rm -rf ./bin/kernel.bin
	rm -rf ./artillery.bin
	rm -rf $(FILES)
	rm -rf ./build/kernelfull.o