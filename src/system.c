#include <system.h>
#include <vga.h>
#include <string.h>

void _panic(char *msg, char *file, int line)
{
    char buf[10];
    uitoa(line, buf, 10);
    vga_puts(file);
    vga_puts(":");
    vga_puts(buf);
    vga_puts(": ");
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


