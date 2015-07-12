#include <keyboard.h>
#include <ports.h>
#include <vga.h>
#include <system.h>
#include <string.h>
#include <timer.h>
#include <asm/keyboard.h>

uint16_t keyboard_port;

void keyboard_irq(registers_t regs) {
    char buf[10];
    if (regs.err) {
        panic("Keyboard interrupt error\n");
    }
    vga_puts("keyboard_irq called.\n");
    uint8_t signal = inb(keyboard_port);
    vga_puts("Keyboard sent 0x");
    uitoa(signal, buf, 16);
    vga_puts(buf);
    vga_puts("\nUptime: ");
    uitoa(uptime / TIMER_FREQ, buf, 10);
    vga_puts(buf);
    vga_puts("s\n");
}

void init_keyboard(void) {
    keyboard_port = 0x60;
    isr_register_handler(0x21, _asm_keyboard_irq);
}
