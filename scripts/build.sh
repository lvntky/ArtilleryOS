export PREFIX="$HOME/opt/cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"
make all
cd bin/
qemu-system-x86_64 -hda artillery.bin