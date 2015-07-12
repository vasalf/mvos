#include <idt.h>
#include <system.h>
#include <asm/isr.h>
#include <asm/irq.h>
#include <asm/lidt.h>

struct idt_descriptor idtd[256];
struct idt_pointer idtp;

void init_idt(void)
{
    for (int i = 0; i < 256; i++)
    {
        idtd[i].base_low = 0;
        idtd[i].selector = 0;
        idtd[i].zero = 0;
        idtd[i].flags = 0;
        idtd[i].base_high = 0;
    }
    idtp.size = sizeof(struct idt_descriptor) * 256 - 1;
    idtp.base = (uint32_t) &idtd;
    if (sizeof(struct idt_descriptor) != 8) {
        panic("sizeof(struct idt_descriptor) must be 8, not %d\n", sizeof(struct idt_descriptor));
    }
    for (int i = 0; i < 0x20; ++i) {
        idt_set_descriptor(i, (uint32_t) _asm_isr_default_noerror, 0x08, 0x8E);
    }
    idt_set_descriptor(8, (uint32_t) _asm_isr_default, 0x08, 0x8E);
    idt_set_descriptor(10, (uint32_t) _asm_isr_default, 0x08, 0x8E);
    idt_set_descriptor(11, (uint32_t) _asm_isr_default, 0x08, 0x8E);
    idt_set_descriptor(12, (uint32_t) _asm_isr_default, 0x08, 0x8E);
    idt_set_descriptor(13, (uint32_t) _asm_isr_default, 0x08, 0x8E);
    idt_set_descriptor(14, (uint32_t) _asm_isr_default, 0x08, 0x8E);
    for (int i = 0x21; i < 0x28; ++i) {
        idt_set_descriptor(i, (uint32_t) _asm_irq_default_master, 0x08, 0x8E);
    }
    for (int i = 0x28; i < 0x30; ++i) {
        idt_set_descriptor(i, (uint32_t) _asm_irq_default_slave, 0x08, 0x8E);
    }

    _asm_lidt();
}

void idt_set_descriptor(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags)
{
    idtd[num].base_low = base & 0xFFFF;
    idtd[num].base_high = (base >> 16) & 0xFFFF;
    idtd[num].selector = sel;
    idtd[num].zero = 0;
    idtd[num].flags = flags;
}
