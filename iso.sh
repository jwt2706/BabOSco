#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/BaboscOS.kernel isodir/boot/BaboscOS.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "BaboscOS" {
	multiboot /boot/BaboscOS.kernel
}
EOF
grub-mkrescue -o BaboscOS.iso isodir
