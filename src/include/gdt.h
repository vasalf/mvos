#ifndef GDT_H
#define GDT_H

#include <stdint.h>


struct gdt_descriptor
{
    uint16_t size_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t gran;
    uint8_t base_high;
} __attribute__((packed));

struct gdt_pointer
{
    uint16_t size;
    uint32_t base;
} __attribute__((packed));

void init_gdt(void);
void gdt_set_descriptor(int32_t num, uint32_t base, uint32_t size, uint8_t access, uint8_t gran);

#endif
