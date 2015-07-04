#include "include/irq.h"
#include "include/isr.h"
#include "include/pic.h"
#include "include/ports.h"

void irq_handler(registers_t regs) {
    if (regs.int_no >= 40) {
        outb(PIC2_COMMAND, PIC_EOI);
    }
    outb(PIC1_COMMAND, PIC_EOI);

    common_isr_handler(regs);
}
