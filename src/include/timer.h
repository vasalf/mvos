#ifndef TIMER_H
#define TIMER_H


#include "isr.h"
#include <stdint.h>

#define TIMER_FREQ 50

extern uint32_t uptime;

void init_timer(void);
void timer_irq(registers_t regs);

#endif
