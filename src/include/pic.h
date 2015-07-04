#ifndef PIC_H
#define PIC_H

#include <stdint.h>


#define PIC1            0x20
#define PIC2            0xA0
#define PIC1_COMMAND    PIC1
#define PIC1_DATA       (PIC1 + 1)
#define PIC2_COMMAND    PIC2
#define PIC2_DATA       (PIC2 + 2)
#define PIC_EOI         0x20
#define ICW1            0x11
#define ICW4            0x01

void init_pic(void);
void pic_remap(int offset1, int offset2);
void pic_mask(uint8_t irq_line);
void pic_unmask(uint8_t irq_line);

#endif
