#include "include/system.h"
#include "include/vga.h"
#include "include/panic.h"
#include <stdint.h>


void panic(char *msg)
{
    vga_puts("KERNEL PANIC: ");
    vga_puts(msg);
    _asm_panic();
}


