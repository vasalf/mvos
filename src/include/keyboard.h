#ifndef KEYBOARD_H
#define KEYBOARD_H


#include <stdint.h>
#include <isr.h>

extern uint16_t keyboard_port;

void init_keyboard(void);
void keyboard_irq(registers_t regs);

#endif
