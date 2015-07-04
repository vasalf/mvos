#include "include/timer.h"
#include "include/irq.h"
#include "include/ports.h"
#include "include/vga.h"
#include "include/system.h"


uint32_t uptime;

void timer_irq(registers_t regs) {
    if (regs.int_no != 0x20) {
        panic("This is just weird\n");
    }
    ++uptime;
}

void init_timer(void) {
    irq_register_handler(0, timer_irq);
    uint32_t divisor = 1193180 / TIMER_FREQ;
    outb(0x43, 0x36);
    io_wait();
    uint8_t low = (uint8_t)(divisor & 0xFF);
    uint8_t hig = (uint8_t)((divisor >> 8) & 0xFF);
    outb(0x40, low);
    io_wait();
    outb(0x40, hig);
    io_wait();
}
