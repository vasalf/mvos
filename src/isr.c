#include <isr.h>
#include <idt.h>
#include <pic.h>
#include <stdio.h>
#include <system.h>

void isr_default_handler(struct registers regs) {
    if (regs.err) {
        panic("Interrupt error (%#hhX)\n", regs.err);
    }
    printf("Unhandled interrupt!\n");
}

void isr_register_handler(int num, isr_t handler) {
    idt_set_descriptor(num, (uint32_t) handler, 0x08, 0x8E);
    pic_mask(num);
}

void isr_deregister_handler(int num) {
    isr_handlers[num] = 0;
    pic_unmask(num);
}
