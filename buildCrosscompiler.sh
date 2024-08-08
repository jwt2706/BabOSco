# this script will just build the cross compiler for x86_64-elf
# you only need to run this once

sudo apt-get update
sudo apt-get install -y bison flex libgmp3-dev libmpfr-dev libmpc-dev texinfo nasm
mkdir -p /opt
cd /opt
wget https://ftp.gnu.org/gnu/binutils/binutils-2.36.tar.gz
tar -xzvf binutils-2.36.tar.gz
cd binutils-2.36
mkdir build
cd build
../configure --target=x86_64-elf --prefix="/opt/cross" --disable-nls --disable-werror
make
make install
cd /opt
wget https://ftp.gnu.org/gnu/gcc/gcc-10.2.0/gcc-10.2.0.tar.gz
tar -xzvf gcc-10.2.0.tar.gz
cd gcc-10.2.0
mkdir build
cd build
../configure --target=x86_64-elf --prefix="/opt/cross" --disable-nls --enable-languages=c,c++ --without-headers
make all-gcc
make all-target-libgcc
make install-gcc
make install-target-libgcc