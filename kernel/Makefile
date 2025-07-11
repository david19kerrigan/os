OBJS=asm/boot.o kernel.o

CRTI_OBJ=asm/crti.o
CRTBEGIN_OBJ:=$(shell $(CC) $(CFLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJ:=$(shell $(CC) $(CFLAGS) -print-file-name=crtend.o)
CRTN_OBJ=asm/crtn.o

OBJ_LINK_LIST:=$(CRTI_OBJ) $(CRTBEGIN_OBJ) $(OBJS) -lk -nostdlib -lgcc $(CRTEND_OBJ) $(CRTN_OBJ)
INTERNAL_OBJS:=$(CRTI_OBJ) $(OBJS) $(CRTN_OBJ)

.PHONY: link boot clean 
.SUFFIXES: .o .c .S

.S.o:
	$(CC) -MD -c $< -o $@ -ffreestanding -O2 -Wall -Wextra -Iinclude

.c.o:
	$(CC) -MD -c $< -o $@ -std=gnu99 -ffreestanding -O2 -Wall -Wextra -Iinclude

myos.bin: $(OBJS) $(CRTI_OBJ) $(CRTN_OBJ)
	$(CC) -T linker.ld -o $@ -ffreestanding -O2 -Iinclude $(OBJ_LINK_LIST)

boot: myos.bin
	mkdir -p $(SYSROOT)$(BOOTDIR)
	cp myos.bin $(SYSROOT)$(BOOTDIR)/

clean:
	rm -f *.o */*.o
	rm -f *.d */*.d
	rm -f myos.bin

