#include <keyboard.h>
#include <ports.h>
#include <stdio.h>
#include <system.h>
#include <string.h>
#include <timer.h>
#include <asm/keyboard.h>

uint16_t keyboard_port;

void keyboard_irq(void) {
    uint8_t signal;
    signal = inb(keyboard_port);
    printf("keyboard_irq called.\n");
    printf("Keyboard sent %#4hhX\n", signal);
    printf("Uptime: %ds\n", uptime / TIMER_FREQ);
}

void init_keyboard(void) {
    keyboard_port = 0x60;
    isr_register_handler(0x21, _asm_keyboard_irq);
}
