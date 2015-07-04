#ifndef IDT_H
#define IDT_H

#include <stdint.h>


struct idt_descriptor
{
    uint16_t base_low;
    uint16_t selector;
    uint8_t zero;
    uint8_t flags;
    uint16_t base_high;
} __attribute__((packed));

struct idt_pointer
{
    uint16_t size;
    uint32_t base;
} __attribute__((packed));

void init_idt(void);
void idt_set_descriptor(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags);

#endif
