OBJS=string/strlen.o
BINARIES=libc.a

INCLUDE_DIR=/usr/local/include/
LIB_DIR=/usr/local/lib/

.PHONY: clean install install-headers install-libs

libc.a: $(OBJS)
	ar rcs $@ $(OBJS)

.c.o:
	$(CC) -MD -c $< -o $@ -std=gnu99 -ffreestanding -O2 -Wall -Wextra -Iinclude

clean:
	rm -f *.a 
	rm -f *.o */*.o */*/*.o
	rm -f *.d */*.d */*/*.d
	rm -rf $(SYSROOT)/*

install: install-headers install-libs

install-headers: 
	mkdir -p $(SYSROOT)$(INCLUDE_DIR)
	cp -R include/. $(SYSROOT)$(INCLUDE_DIR).

install-libs: $(BINARIES)
	mkdir -p $(SYSROOT)$(LIB_DIR)
	cp $(BINARIES) $(SYSROOT)$(LIB_DIR).

