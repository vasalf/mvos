#ifndef ISR_H
#define ISR_H


#include <stdint.h>
#include <asm_isr.h>

#define IRQ0    0x20
#define IRQ1    0x21
#define IRQ2    0x22
#define IRQ3    0x23
#define IRQ4    0x24
#define IRQ5    0x25
#define IRQ6    0x26
#define IRQ7    0x27
#define IRQ8    0x28
#define IRQ9    0x29
#define IRQ10   0x2A
#define IRQ11   0x2B
#define IRQ12   0x2C
#define IRQ13   0x2D
#define IRQ14   0x2E
#define IRQ15   0x2F

typedef struct registers {
    uint32_t ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t err;
    uint32_t eip, cs, eflags, user_esp, ss;
} registers_t;
typedef void (*isr_t)(registers_t);

void isr_common_handler(registers_t regs);
void isr_register_handler(int num, isr_t handler);
void isr_deregister_handler(int num);

isr_t isr_handlers[256];

#endif
