#include "include/timer.h"
#include "include/irq.h"
#include "include/ports.h"


uint32_t tick;

void timer_irq(registers_t regs) {
    ++tick;
}

void init_timer(void) {
    isr_handlers[IRQ0] = timer_irq;
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
