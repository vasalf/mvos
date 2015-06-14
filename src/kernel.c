#include <stdbool.h>
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

uint8_t make_color(enum vga_color fg, enum vga_color bg)
{
    return fg | (bg << 4);
}

uint16_t make_vgachar(char c, uint8_t color)
{
    if (c == '\n')
        c = '\0';
    return ((uint16_t)c) | ((uint16_t)color << 8);
}

size_t strlen(const char* str)
{
    size_t ret = 0;
    while ( str[ret] != 0 )
        ret++;
    return ret;
}

const size_t VGA_HEIGHT = 25;
const size_t VGA_WIDTH = 80;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

void terminal_init(void)
{
    terminal_row = 0;
    terminal_column = 0;
    terminal_color = make_color(COLOR_WHITE, COLOR_BLACK);
    terminal_buffer = (uint16_t*)0xB8000;
    for (size_t y = 0; y < VGA_HEIGHT; y++)
    {
        for (size_t x = 0; x < VGA_WIDTH; x++)
        {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = make_vgachar('\0', terminal_color);
        }
    }
}

void terminal_setcolor(uint8_t color)
{
    terminal_color = color;
}

void terminal_putcharat(char c, uint8_t color, size_t x, size_t y)
{
    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = make_vgachar(c, color);
}

void terminal_putchar(char c)
{
    terminal_putcharat(c, terminal_color, terminal_column, terminal_row);
    if (++terminal_column == VGA_WIDTH || c == '\n')
    {
        terminal_column = 0;
        if (++terminal_row == VGA_HEIGHT)
        {
            terminal_row = 0;
        }
    }
}

void terminal_puts(const char* data)
{
    size_t datalen = strlen(data);
    for (size_t i = 0; i < datalen; i++)
        terminal_putchar(data[i]);
}

void kernel_main(void)
{
    terminal_init();
    terminal_puts("179++\n");
}
