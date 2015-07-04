#include <init.h>
#include <vga.h>
#include <string.h>
#include <registers.h>

void kernel_main(void)
{
    init_all();
    vga_puts("Kernel loaded\n");
    int eipreg;
    get_eip(eipreg);
    vga_puts("EIP: 0x");
    char buf[10];
    itoa(eipreg, buf, 16);
    vga_puts(buf);
    vga_puts("\n");
    int cr0reg;
    get_cr0(cr0reg);
    vga_puts("CR0: 0b");
    itoa(cr0reg, buf, 2);
    vga_puts(buf);
    vga_puts("\n");
    vga_puts("Interrupts enabled\n");
<<<<<<< HEAD
    for(;;);
=======
    __asm__ __volatile__ ("sti");
    for (;;) {
        __asm__ __volatile__ ("hlt\n");
    }
>>>>>>> benny
    return;
}
