#include <gdt.h>
#include <system.h>
#include <asm/lgdt.h>

struct gdt_descriptor gdtd[5];
struct gdt_pointer gdtp;

/* Access Byte values
 *
 *  Pr - Present bit, should be always 1
 *  Privl - Privilege, 2 bits. Ring level, from 0 (highest, kernel) to 3 (lowest, user applications)
 *  Ex - Executable bit
 *  DC - Direction bit / Conforming bit:
 *       Direction bit for data (Ex = 0) selectors:
 *           0 if segment grows up
 *           1 if segment grows down
 *       Conforming bit for code selectors:
 *           if 1 code can be executed from an equal or lower privilege level
 *           if 0 code can be executed only from equal privilege level
 *  RW - Readable bit / Writable bit
 *       Readable bit for code selectors
 *       Writable bit for data selectors
 *  Ac - Accessed bit,  should be always 0, used by CPU
 *
 * +-------------------+----+-------+---+----+----+----+----+
 * | Access Byte       | Pr | Privl | 1 | Ex | DC | RW | Ac |
 * +-------------------+----+-------+---+----+----+----+----+
 * | 0x9A = 0b10011010 |  1 |   00  | 1 |  1 |  0 |  1 |  0 |
 * +-------------------+----+-------+---+----+----+----+----+
 * | 0x92 = 0b10010010 |  1 |   00  | 1 |  0 |  0 |  1 |  0 |
 * +-------------------+----+-------+---+----+----+----+----+
 * | 0xFA = 0b11111010 |  1 |   00  | 1 |  0 |  0 |  1 |  0 |
 * +-------------------+----+-------+---+----+----+----+----+
 * | 0xF2 = 0b11110010 |  1 |   00  | 1 |  0 |  0 |  1 |  0 |
 * +-------------------+----+-------+---+----+----+----+----+
 */


void init_gdt(void)
{
    gdtp.size = sizeof(struct gdt_descriptor) * 5 - 1;
    gdtp.base = (uint32_t) &gdtd;
    gdt_set_descriptor(0, 0, 0, 0, 0);
    gdt_set_descriptor(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    gdt_set_descriptor(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
    gdt_set_descriptor(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
    gdt_set_descriptor(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);
    if (sizeof(struct gdt_descriptor) != 8) 
    {
        panic("sizeof(struct gdt_descriptor) must be 8, not %d\n", sizeof(struct gdt_descriptor));
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
