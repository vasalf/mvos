#include "include/system.h"
#include "include/vga.h"

void panic(char* buf)
{
    vga_puts("KERNEL PANIC: ");
    vga_puts(buf);
    __asm__ __volatile__("cli");
    __asm__ __volatile__("hlt");
    for (;;);
}
