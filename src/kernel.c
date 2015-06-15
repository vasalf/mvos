#include <stdint.h>
#include <stddef.h>
#include "include/vga.h"

void kernel_main(void)
{
    vga_init();
    vga_puts("179++\n");
}
