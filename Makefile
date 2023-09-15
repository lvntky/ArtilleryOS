# List of C source files in the kernel/src directory
kernel_source_files := $(shell find kernel/src -name *.c)

# List of assembly source files in the kernel/boot/x86_64 directory
x86_64_asm_source_files := $(shell find kernel/boot/x86_64 -name *.asm)

# List of object files for C source files
kernel_object_files := $(patsubst kernel/src/%.c, build/kernel/%.o, $(kernel_source_files))

# List of object files for assembly source files
x86_64_asm_object_files := $(patsubst kernel/boot/x86_64/%.asm, build/x86_64/%.o, $(x86_64_asm_source_files))

# Combine C and assembly object files for the x86_64 architecture
x86_64_object_files := $(kernel_object_files) $(x86_64_asm_object_files)

# Rule to build object files from C source files
build/kernel/%.o : kernel/src/%.c
	mkdir -p $(dir $@) && \
	x86_64-elf-gcc -c -I src/include -ffreestanding $< -o $@

# Rule to build object files from assembly source files
build/x86_64/%.o : kernel/boot/x86_64/%.asm
	mkdir -p $(dir $@) && \
	nasm -f elf64 $< -o $@

# Rule to build the final kernel image
.PHONY: build-x86_64
build-x86_64: $(x86_64_object_files)
	mkdir -p dist/x86_64 && \
	x86_64-elf-ld -n -o dist/x86_64/kernel.bin -T targets/x86_64/linker.ld $(x86_64_object_files) && \
	cp dist/x86_64/kernel.bin targets/x86_64/iso/boot/kernel.bin && \
	grub-mkrescue /usr/lib/grub/i386-pc -o dist/x86_64/kernel.iso targets/x86_64/iso
