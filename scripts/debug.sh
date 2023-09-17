#!/bin/bash

# Start QEMU with the kernel image and wait for GDB connection
qemu-system-x86_64 -hda ./bin/artillery.bin -gdb tcp::12345 -S &

# Start GDB and load symbols, then continue execution
gdb -ex "target remote localhost:1234" \
    -ex "add-symbol-file ./build/kernel_and_bootloader_combined.o 0x100000" \
