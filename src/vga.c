#include <vga.h>
#include <string.h>
#include <ports.h>

const size_t VGA_WIDTH = 80;
const size_t VGA_HEIGHT = 25;

#define VGA_BUFFER_INDEX(X, Y) ((Y) * VGA_WIDTH + (X))

uint8_t make_color(enum vga_color fg, enum vga_color bg)
{
    return fg | (bg << 4);
}

uint16_t make_vgachar(char c, uint8_t color)
{
    if (c == '\n')
        c = ' ';
    return ((uint16_t)c) | ((uint16_t)color << 8);
}

static size_t vga_row;
static size_t vga_column;
static uint8_t vga_color;
static uint16_t* vga_buffer;

void init_vga(void)
{
    vga_row = 0;
    vga_column = 0;
    vga_color = make_color(COLOR_WHITE, COLOR_BLACK);
    vga_buffer = (uint16_t*)0xb8000;
    for (size_t y = 0; y < VGA_HEIGHT; y++)
    {
        for (size_t x = 0; x < VGA_WIDTH; x++)
        {
            const size_t index = y * VGA_WIDTH + x;
            vga_buffer[index] = make_vgachar(' ', vga_color);
        }
    }
}

void vga_setcolor(uint8_t color)
{
    vga_color = color;
}

void vga_putcharat(char c, uint8_t color, size_t x, size_t y)
{
    vga_buffer[VGA_BUFFER_INDEX(x, y)] = make_vgachar(c, color);
}

void vga_move_cursor(size_t x, size_t y)
{
    uint16_t position = VGA_BUFFER_INDEX(y, x);
    outb(0x3d4, 0xf);
    outb(0x3d5, (uint8_t)(position & 0xff));
    outb(0x3d4, 0xe);
    outb(0x3d5, (uint8_t)((position >> 8) & 0xff));
}

void vga_putchar(char c)
{
    if (c == '\r') {
        vga_column = 0;
        return;
    }
    vga_putcharat(c, vga_color, vga_column, vga_row);
    if (++vga_column == VGA_WIDTH || c == '\n')
    {
        vga_column = 0;
        if (++vga_row == VGA_HEIGHT)
        {
            for (size_t i = 0; i < VGA_HEIGHT - 1; i++)
                for (size_t j = 0; j < VGA_WIDTH; j++)
                    vga_buffer[VGA_BUFFER_INDEX(j, i)] = vga_buffer[VGA_BUFFER_INDEX(j, i + 1)];
            for (size_t i = 0; i < VGA_WIDTH; i++)
                vga_putcharat(' ', vga_color, i, VGA_HEIGHT - 1);
            --vga_row;
        }
    }
    vga_move_cursor(vga_row, vga_column);
}

void vga_puts(const char* data)
{
    size_t datalen = strlen(data);
    for (size_t i = 0; i < datalen; i++)
        vga_putchar(data[i]);
}


