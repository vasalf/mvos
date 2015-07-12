#include <irq.h>
#include <pic.h>
#include <ports.h>
#include <system.h>
#include <stdio.h>

void irq_default_master_handler(registers_t regs) {
    if (regs.err) {
        panic("Hardware interrupt error (%#hhX)\n", regs.err);
    }
    printf("Unhandled hardware interrupt (master)!\n");
    outb(PIC1_COMMAND, PIC_EOI);
}

void irq_default_slave_handler(registers_t regs) {
    if (regs.err) {
        panic("Hardware interrupt error (%#hhX)\n", regs.err);
    }
    printf("Unhandled hardware interrupt (slave)!\n");
    outb(PIC2_COMMAND, PIC_EOI);
    outb(PIC1_COMMAND, PIC_EOI);
}
