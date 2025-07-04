CC=/home/david/Downloads/cc/i386-elf-7.5.0-Linux-x86_64/bin/i386-elf-gcc
AS=/home/david/Downloads/cc/i386-elf-7.5.0-Linux-x86_64/bin/i386-elf-as
make:
	$(AS) boot.s -o boot.o
	$(CC) -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	$(CC) -T linker.ld -o myos.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc
	cp myos.bin isodir/boot/myos.bin
	grub2-mkrescue -o myos.iso isodir
	qemu-system-i386 -cdrom myos.iso
