#!/bin/bash

# Specify the installation directory for the cross-compiler
INSTALL_DIR=$HOME/.artillery-compiler
TARGET=x86_64-elf
BINUTILS_VERSION=2.37
GCC_VERSION=11.2.0

# Ensure development essentials are installed
sudo pacman -S base-devel bison flex gmp libmpc mpfr texinfo wget

# Create a directory for storing the source and build files
mkdir -p $INSTALL_DIR/src
cd $INSTALL_DIR/src

# Download Binutils source
wget https://ftp.gnu.org/gnu/binutils/binutils-$BINUTILS_VERSION.tar.gz
tar -xf binutils-$BINUTILS_VERSION.tar.gz

# Download GCC source
wget https://ftp.gnu.org/gnu/gcc/gcc-$GCC_VERSION/gcc-$GCC_VERSION.tar.gz
tar -xf gcc-$GCC_VERSION.tar.gz

# Build and install Binutils
mkdir -p build-binutils
cd build-binutils
../binutils-$BINUTILS_VERSION/configure --target=$TARGET --prefix=$INSTALL_DIR --with-sysroot --disable-nls --disable-werror
make -j$(nproc)
make install

# Build and install GCC
cd ../gcc-$GCC_VERSION
./contrib/download_prerequisites
mkdir -p build-gcc
cd build-gcc
../configure --target=$TARGET --prefix=$INSTALL_DIR --disable-nls --enable-languages=c,c++ --without-headers
make all-gcc -j$(nproc)
make install-gcc

# Finish GCC installation
make all-target-libgcc -j$(nproc)
make install-target-libgcc

# Verify installation
echo "Cross-compiler installed in $INSTALL_DIR"
echo "Verify by running: $TARGET-gcc --version"
