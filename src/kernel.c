#include <stdint.h>
#include <stddef.h>
#include "include/vga.h"
#include "include/stdstring.h"
#include "include/ports.h"
#include "include/dbg.h"
#include "include/init.h"

void kernel_main(void)
{
    init_all();
    vga_puts("Kernel loaded\n");
    int eipreg;
    get_eip();
    __asm__ __volatile__ ("movl %%ebx, %%eax" : "=a"(eipreg));
    vga_puts("EIP: 0x");
    char buf[10];
    itoa(eipreg, buf, 16);
    vga_puts(buf);
    vga_puts("\n");
    int cr0reg;
    __asm__ __volatile__("movl %%cr0, %%eax" : "=a"(cr0reg));
    vga_puts("CR0: 0b");
    itoa(cr0reg, buf, 2);
    vga_puts(buf);
    vga_puts("\n");
    __asm__ __volatile__ ("sti");
    vga_puts("Interrupts enabled\n");
    for(;;);
    return;
}
