# gcc 10.2.0 x86_64-elf Artillery OS cross-compiler container
FROM ubuntu:latest

# Set environment variables
ENV DEBIAN_FRONTEND=noninteractive

LABEL maintainer "Levent Kaya <github.com/lvntky>"

ARG BINUTILS_VERSION=2.41
ARG GCC_VERSION=10.2.0

# Install cross-compiler prerequisites
RUN set -x \
    && apt-get update \
    && apt-get install -y wget gcc build-essential bison flex libgmp3-dev \
    libmpc-dev libmpfr-dev texinfo

# Pull binutils and gcc source code
RUN set -x \
    && mkdir -p /usr/local/src \
    && cd /usr/local/src \
    && wget -q https://ftp.gnu.org/gnu/binutils/binutils-${BINUTILS_VERSION}.tar.gz \
    && wget -q https://ftp.gnu.org/gnu/gcc/gcc-${GCC_VERSION}/gcc-${GCC_VERSION}.tar.gz \
    && tar zxf binutils-${BINUTILS_VERSION}.tar.gz \
    && tar zxf gcc-${GCC_VERSION}.tar.gz \
    && rm binutils-${BINUTILS_VERSION}.tar.gz gcc-${GCC_VERSION}.tar.gz \
    && chown -R root:root binutils-${BINUTILS_VERSION} \
    && chown -R root:root gcc-${GCC_VERSION} \
    && chmod -R o-w,g+w binutils-${BINUTILS_VERSION} \
    && chmod -R o-w,g+w gcc-${GCC_VERSION}

# Copy compile scripts
COPY files/src /usr/local/src/

# Copy gcc patches
COPY files/gcc/t-x86_64-elf /usr/local/src/gcc-${GCC_VERSION}/gcc/config/i386/
COPY files/gcc/config.gcc.patch /usr/local/src/gcc-${GCC_VERSION}/gcc/

# Build and install binutils and the cross-compiler
RUN set -x \
    && cd /usr/local/src \
    && ./build-binutils.sh ${BINUTILS_VERSION} \
    && ./build-gcc.sh ${GCC_VERSION}

CMD ["/bin/bash"]

RUN apt-get install -y nasm
RUN apt-get install -y xorriso
RUN apt-get install -y grub-pc-bin
RUN apt-get install -y grub-common

VOLUME /root/env
WORKDIR /root/env
