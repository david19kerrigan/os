OBJS=\
stdio/printf.libk.o \
stdio/putchar.libk.o \
stdio/puts.libk.o \
stdlib/abort.libk.o \
string/memcmp.libk.o \
string/memcpy.libk.o \
string/memmove.libk.o \
string/memset.libk.o \
string/strlen.libk.o \

BINARIES=libk.a

.PHONY: clean install install-headers install-libs
.SUFFIXES: .o .libk.o .c .s

libk.a: $(OBJS)
	$(AR) rcs $@ $(OBJS)

.c.o:
	$(CC) -MD -c $< -o $@ -std=gnu99 -ffreestanding -O2 -Wall -Wextra -Iinclude

.c.libk.o:
	$(CC) -MD -c $< -o $@ -std=gnu99 -ffreestanding -O2 -Wall -Wextra -Iinclude

clean:
	rm -f *.a 
	rm -f *.o */*.o */*/*.o
	rm -f *.d */*.d */*/*.d
	rm -rf $(SYSROOT)/*

install: install-headers install-libs

install-headers: 
	mkdir -p $(SYSROOT)$(INCLUDEDIR)
	cp -R include/. $(SYSROOT)$(INCLUDEDIR)/.

install-libs: $(BINARIES)
	mkdir -p $(SYSROOT)$(LIBDIR)
	cp $(BINARIES) $(SYSROOT)$(LIBDIR)

