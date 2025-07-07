OBJS=asm/boot.o asm/crti.o asm/crtn.o kernel.o 

CRTI_OBJ=asm/crti.o
CRTBEGIN_OBJ:=$(shell $(CC) $(CFLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJ:=$(shell $(CC) $(CFLAGS) -print-file-name=crtend.o)
CRTN_OBJ=asm/crtn.o

OBJ_LINK_LIST:=$(CRTI_OBJ) $(CRTBEGIN_OBJ) $(OBJS) $(CRTEND_OBJ) $(CRTN_OBJ)
INTERNAL_OBJS:=$(CRTI_OBJ) $(OBJS) $(CRTN_OBJ)

.PHONY: link boot clean 

.s.o:
	$(AS) $< -o $@

.c.o:
	$(CC) -MD -c $< -o $@ -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I$(SYSROOT)/usr/local/include

myos.bin: $(OBJS)
	$(CC) -T linker.ld -o myos.bin -ffreestanding -O2 -nostdlib $(OBJ_LINK_LIST) -lgcc

boot: myos.bin
	cp myos.bin isodir/boot/myos.bin
	grub2-mkrescue -o myos.iso isodir
	qemu-system-i386 -cdrom myos.iso

clean:
	rm -f *.o */*.o
	rm -f *.d */*.d

