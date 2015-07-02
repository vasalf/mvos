#include "include/idt.h"
#include "include/ports.h"

struct IDT_descriptor idtd[256];
struct IDT_pointer idtp;

void irq_remap()
{
    send_to_port(0x20, 0x11); 
    send_to_port(0xa0, 0x11);
    send_to_port(0x21, 0x20);
    send_to_port(0xa1, 0x28);
    send_to_port(0x21, 0x04);
    send_to_port(0xa1, 0x02);
    send_to_port(0x21, 0x01);
    send_to_port(0xa1, 0x01);
    send_to_port(0x21, 0x0);
    send_to_port(0xa1, 0x0);
}

extern void idt_load();

void idt_init()
{
    irq_remap();
    for (int i = 0; i < 256; i++)
    {
        idtd[i].lower_offset = 0;
        idtd[i].selector = 0;
        idtd[i].zero = 0;
        idtd[i].attributes = 0;
        idtd[i].higher_offset = 0;
    }
    idtp.size = sizeof(struct IDT_descriptor) * 256 - 1;
    idtp.base = (uint32_t)idtd;
    idt_load();
}

void set_idt_descriptor(uint16_t num, void* interrupt_wrapper)
{
    uint32_t casted_iw_addr = (uint32_t)interrupt_wrapper;
    idtd[num].lower_offset = (casted_iw_addr & 0xffff);
//    idtd[num].selector = SELECTOR(0, 1, num);
    idtd[num].selector = 0x08;
    idtd[num].zero = 0;
    idtd[num].attributes = 0x8e;//INTERRUPT_GATE_ATTRIBUTES;
    idtd[num].higher_offset = ((casted_iw_addr >> 16) & 0xffff);
}
