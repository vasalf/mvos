#ifndef IRQ_H
#define IRQ_H


#include "isr.h"
void irq_common_handler(registers_t regs);
void irq_register_handler(int num, isr_t handler);
void irq_deregister_handler(int num);

#endif
