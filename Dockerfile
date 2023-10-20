# Use a base image with the desired Linux distribution
# This example uses Ubuntu 20.04
FROM ubuntu:20.04

# Set environment variables for the cross-compiler
ENV PREFIX="/usr/local/i686-elf"
ENV TARGET="i686-elf"
ENV PATH="$PREFIX/bin:$PATH"

# Update and install required packages
RUN apt-get update && apt-get install -y \
    build-essential \
    bison \
    flex \
    libgmp3-dev \
    libmpc-dev \
    libmpfr-dev \
    texinfo \
    wget \
    libisl-dev \
    nasm

# Create a directory for the build and set it as the working directory
WORKDIR /root

# Download and extract the source code for binutils
RUN wget https://ftp.gnu.org/gnu/binutils/binutils-2.35.tar.gz
RUN tar -xzf binutils-2.35.tar.gz

# Create a build directory for binutils, configure, build, and install
RUN mkdir build-binutils
WORKDIR /root/build-binutils
RUN ../binutils-2.35/configure --target=$TARGET --prefix=$PREFIX --with-sysroot --disable-nls --disable-werror
RUN make
RUN make install

# Go back to the root directory and download and extract the source code for GCC
WORKDIR /root
RUN wget https://ftp.gnu.org/gnu/gcc/gcc-10.2.0/gcc-10.2.0.tar.gz
RUN tar -xzf gcc-10.2.0.tar.gz

# Create a build directory for GCC, configure, build, and install
RUN mkdir build-gcc
WORKDIR /root/build-gcc
RUN ../gcc-10.2.0/configure --target=$TARGET --prefix=$PREFIX --disable-nls --enable-languages=c,c++
RUN make all-gcc
RUN make all-target-libgcc
RUN make install-gcc
RUN make install-target-libgcc

# Clean up
WORKDIR /root
RUN rm -rf binutils-2.35 gcc-10.2.0 build-binutils build-gcc
RUN apt-get autoremove -y && apt-get clean

# Print a message indicating the setup is complete
RUN echo "Cross-compiler for $TARGET has been built and installed to $PREFIX."

# Set the working directory to /code
WORKDIR /code

# You can now mount your Artillery OS source code directory to /code
# and build your operating system within the Docker container.

# Example usage:
# docker build -t artillery-os-dev-env .
# docker run -v /path/to/artillery-os-source:/code -it artillery-os-dev-env
