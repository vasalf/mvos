#ifndef IDT_H
#define IDT_H


#include <stdint.h>

struct idt_descriptor {
    uint16_t base_low;
    uint16_t selector;
<<<<<<< HEAD
    uint8_t zero; //reserved, must be zero
    uint8_t attributes;
    uint16_t higher_offset;
=======
    uint8_t zero;
    uint8_t flags;
    uint16_t base_high;
>>>>>>> benny
} __attribute__((packed));

struct idt_pointer {
    uint16_t size;
    uint32_t base;
} __attribute__((packed));
<<<<<<< HEAD
=======

void init_idt(void);
void idt_set_descriptor(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags);
>>>>>>> benny

#endif
