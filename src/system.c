#include <stdint.h>
#include "include/system.h"
#include "include/vga.h"
#include "include/init.h"

void panic(char* buf)
{
    vga_puts("KERNEL PANIC: ");
    vga_puts(buf);
    __asm__ __volatile__("cli");
    __asm__ __volatile__("hlt");
    for (;;);
}


