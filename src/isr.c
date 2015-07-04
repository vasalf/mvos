#include <isr.h>
#include <ports.h>
#include <pic.h>
#include <vga.h>
#include <string.h>

void isr_common_handler(struct registers regs) {
    if (isr_handlers[regs.int_no] != 0) {
        isr_handlers[regs.int_no](regs);
    } else {
        char s[10];
        uitoa(regs.int_no, s, 16);
        vga_puts("unhandled interrupt: 0x");
        vga_puts(s);
        vga_puts("\n");
    }
}

void isr_register_handler(int num, isr_t handler) {
    isr_handlers[num] = handler;
    pic_mask(num);
}

void isr_deregister_handler(int num) {
    isr_handlers[num] = 0;
    pic_unmask(num);
}
