# Use a base image with a Linux distribution of your choice.
# Ubuntu is commonly used for this purpose.
FROM ubuntu:20.04

# Set non-interactive mode for package installation.
ENV DEBIAN_FRONTEND=noninteractive

# Update package lists and install required packages.
RUN apt-get update -y && \
    apt-get install -y build-essential bison flex libgmp3-dev libmpc-dev \
    libmpfr-dev texinfo wget curl qemu ca-certificates && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# Define environment variables for the cross-compiler.
ENV PREFIX="/usr/local/i686-elf"
ENV TARGET=i686-elf
ENV PATH="$PREFIX/bin:$PATH"

# Create a directory for the source code and set it as the working directory.
WORKDIR /root

# Download and build binutils.
RUN wget https://ftp.gnu.org/gnu/binutils/binutils-2.36.tar.gz && \
    tar -xf binutils-2.36.tar.gz && \
    rm binutils-2.36.tar.gz && \
    mkdir build-binutils && \
    cd build-binutils && \
    ../binutils-2.36/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror && \
    make && \
    make install

# Download and build GCC.
RUN wget https://ftp.gnu.org/gnu/gcc/gcc-10.2.0/gcc-10.2.0.tar.gz && \
    tar -xf gcc-10.2.0.tar.gz && \
    rm gcc-10.2.0.tar.gz && \
    mkdir build-gcc && \
    cd build-gcc && \
    ../gcc-10.2.0/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers && \
    make all-gcc && \
    make all-target-libgcc && \
    make install-gcc && \
    make install-target-libgcc

# Cleanup
RUN rm -rf /root/binutils-2.36 /root/build-binutils /root/gcc-10.2.0 /root/build-gcc

# Print a message to indicate successful setup.
RUN echo "Cross-compiler setup completed. You can now use 'i686-elf-gcc' and 'i686-elf-g++' for OS development."

# Set a default command (in this case, just start a shell).
CMD ["/bin/bash"]
