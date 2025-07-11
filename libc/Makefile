OBJS=string/strlen.libc.o
BINARIES=libc.a

.PHONY: clean install install-headers install-libs
.SUFFIXES: .o .libc.o .c .s

libc.a: $(OBJS)
	$(AR) rcs $@ $(OBJS)

.c.o:
	$(CC) -MD -c $< -o $@ -std=gnu99 -ffreestanding -O2 -Wall -Wextra -Iinclude

.c.libc.o:
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

