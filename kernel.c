#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg){
	return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char letter, uint8_t color){
	return (uint16_t) letter | (uint16_t) color << 8;
}

size_t strlen(const char* str){
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

#define VGA_WIDTH   80
#define VGA_HEIGHT  25
#define VGA_MEMORY  0xB8000 

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer = (uint16_t*)VGA_MEMORY;

uint16_t get_vga_color(int index){
    return terminal_buffer[index] >> 8;
}

void terminal_initialize(void) {
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	
	for(size_t y = 0; y < VGA_HEIGHT; y++){
		for(size_t x = 0; x < VGA_WIDTH; x++){
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

void terminal_setcolor(uint8_t color){
	terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y){
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

void terminal_putchar(char c, enum vga_color color){
	if(c != '\n') terminal_putentryat(c, color, terminal_column, terminal_row);
    if(++terminal_column == VGA_WIDTH || c == '\n') {
		terminal_column = 0;
		if(++terminal_row == VGA_HEIGHT){
            for(int y = 1; y < VGA_HEIGHT; y++){
                for(int x = 0; x < VGA_WIDTH; x++){
                    int index = y * VGA_WIDTH + x;
                    terminal_putentryat(terminal_buffer[index], get_vga_color(index), x, y - 1);
                }
            }
            for(int x = 0; x < VGA_WIDTH; x++){
                terminal_putentryat(' ', color, x, VGA_HEIGHT);
            }
            terminal_row = VGA_HEIGHT - 1;
        }
	}
}

void terminal_write(const char* data, size_t size, enum vga_color color){
	for(size_t i = 0; i < size; i++) terminal_putchar(data[i], color);
}

void terminal_writestring(const char* data, enum vga_color color) {
	terminal_write(data, strlen(data), color);
}

void kernel_main(void){
	terminal_initialize();
	terminal_color = vga_entry_color(VGA_COLOR_BLUE, VGA_COLOR_BLACK);
    terminal_writestring("1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n", terminal_color);
	terminal_color = vga_entry_color(VGA_COLOR_GREEN, VGA_COLOR_BLACK);
    terminal_writestring("15\n16\n17\n18\n19\n20\n21\n22\n23\n24\n25\n26\n27\n28", terminal_color);
}
