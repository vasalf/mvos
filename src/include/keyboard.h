#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>


extern uint16_t keyboard_port;

void init_keyboard();
void keyboard_irq();

#endif
