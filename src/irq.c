#include <irq.h>
#include <pic.h>
#include <ports.h>

void irq_common_handler(registers_t regs) {
    isr_common_handler(regs);
    if (regs.int_no >= 40) {
        outb(PIC2_COMMAND, PIC_EOI);
    }
    outb(PIC1_COMMAND, PIC_EOI);
}

void irq_register_handler(int num, isr_t handler) {
    isr_handlers[IRQ0 + num] = handler;
    pic_mask(IRQ0 + num);
}

void irq_deregister_handler(int num) {
    isr_handlers[IRQ0 + num] = 0;
    pic_unmask(IRQ0 + num);
}
