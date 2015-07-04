#include <gdt.h>
#include <lgdt.h>
#include <system.h>

struct gdt_descriptor gdtd[5];
struct gdt_pointer gdtp;

void init_gdt(void)
{
    gdtp.size = sizeof(struct gdt_descriptor) * 5 - 1;
    gdtp.base = (uint32_t) &gdtd;
    gdt_set_descriptor(0, 0, 0, 0, 0);
    gdt_set_descriptor(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    gdt_set_descriptor(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
    gdt_set_descriptor(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
    gdt_set_descriptor(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);
    if (sizeof(struct gdt_descriptor) != 8) {
        panic("sizeof(struct gdt_descriptor) must be 8\n");
    }
    _asm_lgdt();
}

void gdt_set_descriptor(int32_t num, uint32_t base, uint32_t size, uint8_t access, uint8_t gran)
{
    gdtd[num].base_low = base & 0xFFFF;
    gdtd[num].base_middle = (base >> 16) & 0xFF;
    gdtd[num].base_high = (base >> 24) & 0xFF;
    gdtd[num].size_low = size & 0xFFFF;
    gdtd[num].gran = (size >> 16) & 0x0F;
    gdtd[num].gran |= gran & 0xF0;
    gdtd[num].access = access;
}
