#!/bin/sh
set -e

export INCLUDEDIR=/usr/include
export LIBDIR=/usr/lib
export BOOTDIR=/boot
export SYSROOT="$(pwd)/sysroot"

export CC=/home/david/Downloads/cc/i386-elf-7.5.0-Linux-x86_64/bin/i386-elf-gcc
export AR=/home/david/Downloads/cc/i386-elf-7.5.0-Linux-x86_64/bin/i386-elf-ar
export AS=/home/david/Downloads/cc/i386-elf-7.5.0-Linux-x86_64/bin/i386-elf-as
export CC="$CC --sysroot=$SYSROOT"
export CC="$CC -isystem=$INCLUDEDIR"

cd libc
make clean
make install

cd ../kernel
make clean
make boot
cd ..

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/myos.bin isodir/boot/myos.bin
grub2-mkrescue -o myos.iso isodir
qemu-system-i386 -cdrom myos.iso

