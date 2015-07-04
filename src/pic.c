#include "include/pic.h"
#include "include/ports.h"

void init_pic(void) {
    pic_remap(0x20, 0x28);
}

void pic_remap(int offset1, int offset2) {
    outb(PIC1_COMMAND, ICW1);
    io_wait();
    outb(PIC2_COMMAND, ICW1);
    io_wait();

    outb(PIC1_DATA, offset1);
    io_wait();
    outb(PIC2_DATA, offset2);
    io_wait();

    outb(PIC1_DATA, 0x4);
    io_wait();
    outb(PIC2_DATA, 0x2);
    io_wait();

    outb(PIC1_COMMAND, ICW4);
    io_wait();
    outb(PIC2_COMMAND, ICW4);
    io_wait();

    outb(PIC1_DATA, 0x00);
    io_wait();
    outb(PIC2_DATA, 0x00);
    io_wait();
}

void pic_mask(uint8_t irq) {
    uint16_t port;
    if (irq < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        irq -= 8;
    }
    outb(port, inb(port) | (1 << irq));
}

void pic_unmask(uint8_t irq) {
    uint16_t port;
    if (irq < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        irq -= 8;
    }
    outb(port, inb(port) & ~(1 << irq));
}
