#!/bin/sh
set -e

# This script builds the cross-compiler for the i686-elf target.
# You'll only need to run this once, then you can build the os however many times you please

# Set up environment variables
export HOME="/home/jwt"
export PREFIX="/opt/cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"
export SYSROOT="$HOME/meaty-skeleton/sysroot"

# Install prerequisites
sudo apt-get update
sudo apt-get install -y build-essential bison flex libgmp3-dev libmpc-dev libmpfr-dev texinfo

# Create directories
mkdir -p $HOME/src
mkdir -p $PREFIX

# Download Binutils and GCC
cd $HOME/src
wget https://ftp.gnu.org/gnu/binutils/binutils-2.36.1.tar.gz
wget https://ftp.gnu.org/gnu/gcc/gcc-10.2.0/gcc-10.2.0.tar.gz
tar -xf binutils-2.36.1.tar.gz
tar -xf gcc-10.2.0.tar.gz

# Build and install Binutils
mkdir -p build-binutils
cd build-binutils
../binutils-2.36.1/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
make
make install

# Build and install GCC
cd $HOME/src
mkdir -p build-gcc
cd build-gcc
../gcc-10.2.0/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers
make all-gcc
make all-target-libgcc
make install-gcc
make install-target-libgcc

# Verify installation
if ! command -v $TARGET-gcc > /dev/null; then
  echo "$TARGET-gcc not found in PATH"
  exit 1
fi