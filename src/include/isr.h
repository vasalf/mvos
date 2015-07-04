#ifndef ISR_H
#define ISR_H


#include <stdint.h>
#include "asm_isr.h"

#define IRQ0    32
#define IRQ1    33
#define IRQ2    34
#define IRQ3    35
#define IRQ4    36
#define IRQ5    37
#define IRQ6    38
#define IRQ7    39
#define IRQ8    40
#define IRQ9    41
#define IRQ10   42
#define IRQ11   43
#define IRQ12   44
#define IRQ13   45
#define IRQ14   46
#define IRQ15   47

typedef struct registers {
    uint32_t ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t int_no, err;
    uint32_t eip, cs, eflags, user_esp, ss;
} registers_t;
typedef void (*isr_t)(registers_t);

void isr_common_handler(registers_t regs);
void isr_register_handler(int num, isr_t handler);
void isr_deregister_handler(int num);

isr_t isr_handlers[256];

#endif
