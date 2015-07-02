#include <stdint.h>

struct IDT_descriptor
{
    uint16_t lower_offset;
    uint16_t selector;
    uint8_t zero; //reserved, must be zero
    uint8_t attributes;
    uint16_t higher_offset;
};

struct IDT_pointer
{
    uint16_t size;
    uint32_t base;
};

void idt_init();
void set_idt_descriptor(uint16_t num, void* interrupt_wrapper);
