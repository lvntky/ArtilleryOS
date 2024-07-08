#!/bin/bash

TARGET="i686-elf"
PREFIX="$HOME/.artillery-compiler/opt/cross"
CUSTOM_NAME="artillery-compiler"
PATH="$PREFIX/bin:$PATH"

# Exit on error
set -e

# Install prerequisites
sudo apt-get install build-essential bison flex libgmp3-dev libmpc-dev libmpfr-dev texinfo wget

# Create a directory for the build and navigate into it
mkdir -p $HOME/src
cd $HOME/src

# Download the source packages
wget https://ftp.gnu.org/gnu/binutils/binutils-2.36.tar.gz
wget https://ftp.gnu.org/gnu/gcc/gcc-11.2.0/gcc-11.2.0.tar.gz

# Extract the source packages
tar -xf binutils-2.36.tar.gz
tar -xf gcc-11.2.0.tar.gz

# Build binutils
mkdir build-binutils
cd build-binutils
../binutils-2.36/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
make
make install
cd ..

# Build GCC
mkdir build-gcc
cd build-gcc
../gcc-11.2.0/configure --target=$TARGET --prefix="$PREFIX" --program-prefix=$CUSTOM_NAME --disable-nls --enable-languages=c,c++ --without-headers
make all-gcc
make all-target-libgcc
make install-gcc
make install-target-libgcc
cd ..

echo "Cross compiler ($CUSTOM_NAME) has been built and installed to $PREFIX"
echo "Add $PREFIX/bin to your PATH to use it"

