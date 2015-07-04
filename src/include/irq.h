#ifndef IRQ_H
#define IRQ_H


#include <isr.h>

void irq_default_master_handler(registers_t regs);
void irq_default_slave_handler(registers_t regs);

#endif
