#include "include/isr.h"
#include "include/ports.h"
#include "include/pic.h"
#include "include/vga.h"
#include "include/string.h"

void common_isr_handler(struct registers regs) {
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
