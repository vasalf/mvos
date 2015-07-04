#ifndef VGA_H
#define VGA_H

#include <stdint.h>
#include <stddef.h>


enum vga_color 
{
    COLOR_BLACK = 0,
    COLOR_BLUE = 1,
    COLOR_GREEN = 2,
    COLOR_CYAN = 3,
    COLOR_RED = 4,
    COLOR_MAGENTA = 5,
    COLOR_BROWN = 6,
    COLOR_LIGHT_GREY = 7,
    COLOR_DARK_GREY = 8,
    COLOR_LIGHT_BLUE = 9,
    COLOR_LIGHT_GREEN = 10,
    COLOR_LIGHT_CYAN = 11,
    COLOR_LIGHT_RED = 12,
    COLOR_LIGHT_MAGENTA = 13, 
    COLOR_LIGHT_BROWN = 14,
    COLOR_WHITE = 15,
};

uint8_t make_color(enum vga_color fg, enum vga_color bg);
uint16_t make_vgachar(char c, uint8_t color);

extern const size_t VGA_HEIGHT;
extern const size_t VGA_WIDTH;

void init_vga(void);
void vga_setcolor(uint8_t color);
void vga_putcharat(char c, uint8_t color, size_t x, size_t y);
void vga_putchar(char c);
void vga_puts(const char *str);

#endif
