#!/bin/sh

export SYSROOT="$(pwd)/sysroot"
export CC=/home/david/Downloads/cc/i386-elf-7.5.0-Linux-x86_64/bin/i386-elf-gcc
export AS=/home/david/Downloads/cc/i386-elf-7.5.0-Linux-x86_64/bin/i386-elf-as

cd libc
make clean
make install
cd ../kernel
make clean
make boot
