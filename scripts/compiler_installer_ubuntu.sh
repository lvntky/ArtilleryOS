#!/bin/bash

echo "Artillery OS Compiler Installer Helper Script"

# Update package lists
sudo apt update

# Install necessary dependencies
sudo apt install -y build-essential wget libgmp3-dev libmpc-dev libmpfr-dev flex bison libncurses5-dev

# Set the installation directory (use an absolute path)
INSTALL_DIR=$(pwd)/opt/artillery-compiler/gcc-10.2

# Create a temporary directory for building
BUILD_DIR=$(mktemp -d)

# Download and extract Binutils
cd $BUILD_DIR
wget https://ftp.gnu.org/gnu/binutils/binutils-2.41.tar.gz
tar -xf binutils-2.41.tar.gz

# Build and install Binutils
mkdir build-binutils
cd build-binutils
../binutils-2.41/configure --target=i686-elf --prefix=$INSTALL_DIR --with-sysroot --disable-nls --disable-werror
make
sudo make install

# Download and extract GCC
cd $BUILD_DIR
wget https://ftp.gnu.org/gnu/gcc/gcc-10.2.0/gcc-10.2.0.tar.gz
tar -xf gcc-10.2.0.tar.gz

# Build and install GCC
mkdir build-gcc
cd build-gcc
../gcc-10.2.0/configure --target=i686-elf --prefix=$INSTALL_DIR --disable-nls --enable-languages=c,c++ --without-headers
make all-gcc
make all-target-libgcc
sudo make install-gcc
sudo make install-target-libgcc

# Clean up
rm -r $BUILD_DIR

# Add the compiler to the system's PATH (temporary for the current session)
export PATH=$INSTALL_DIR/bin:$PATH

echo "Installation completed. You can use i686-elf-gcc and i686-elf-g++ now."