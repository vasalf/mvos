#include <system.h>
#include <vga.h>


void panic(char *msg)
{
    __asm__ __volatile__ ("cli");
    if (msg) {
        vga_puts("KERNEL PANIC: ");
        vga_puts(msg);
    } else {
        vga_puts("KERNEL PANIC");
    }
    for (;;) {
        __asm__ __volatile__ ("hlt");
    }
}


