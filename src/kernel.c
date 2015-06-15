#include <stdint.h>
#include <stddef.h>
#include "include/vga.h"
#include "include/stdstring.h"

void kernel_main(void)
{
    vga_init();
    char buf[4];
    uitoa(1000, buf, 10);
    vga_puts(buf);
    vga_putchar('\n');
    uitoa(255, buf, 16);
    vga_puts(buf);
    for (size_t i = 0; i <= 17; i++)
    {
        itoa(-i, buf, 10);
        vga_puts(buf);
        itoa(-i, buf, 16);
        vga_puts(buf);
        vga_putchar('\n');
    }
    return;
}
