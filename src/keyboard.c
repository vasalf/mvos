#include "include/keyboard.h"
#include "include/ports.h"
#include "include/vga.h"
#include "include/system.h"
#include "include/string.h"
#include "include/irq.h"
#include "include/timer.h"

uint16_t keyboard_port;

void keyboard_irq(registers_t regs) {
    char buf[10];
    if (regs.int_no != 0x21) {
        panic("This is just weird\n");
    }
    vga_puts("keyboard_irq called.\n");
    uint8_t signal = inb(keyboard_port);
    vga_puts("Keyboard sent 0x");
    uitoa(signal, buf, 16);
    vga_puts(buf);
    vga_puts(".\nUptime: ");
    uitoa(uptime / TIMER_FREQ, buf, 10);
    vga_puts(buf);
    vga_puts("s\n");
}

void init_keyboard(void) {
    keyboard_port = 0x60;
    irq_register_handler(1, keyboard_irq);
}
