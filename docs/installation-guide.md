# Artillery OS Installation Guide

Artillery OS uses GNUMakefile as a build system. 
If you want to create a bootable ISO for experiencing Artillery OS. There is couple of Dependencies you need.

1. A Cross-Compiler (i686-elf-gcc)
2. nasm
2. make 
3. mtools
4. xorriso

After obtaining the requirements creating a bootable ISO is preatty easy.
All you have to do is compiling the source code with make.

1. `make clean`
2. `make iso`

the `make iso` command will compile the all source code and provide a bootable ISO.

## Releases
If you don't want to compile from source code, you can always download the release from
[releases](https://github.com/lvntky/ArtilleryOS/tags) section.

Just pick up a version you want to use and download the ISO file. 

## Running Artillery OS

While developing Artillery OS, we are mostly using QEMU. you can run the Artillery OS on QEMU after building or 
downloading the ISO with:
`qemu-system-x86_64 -serial stdio -cdrom ./artillery.iso`

You can also try Artillery OS on real hardware but for this you need to build a bootable disk/usb.

