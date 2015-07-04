#include <timer.h>
#include <asm_timer.h>
#include <ports.h>
#include <vga.h>
#include <system.h>


uint32_t uptime;

void timer_irq(registers_t regs) {
    if (regs.err) {
        panic("Timer interrupt error\n");
    }
    ++uptime;
}

void init_timer(void) {
    isr_register_handler(0x20, _asm_timer_irq);
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
