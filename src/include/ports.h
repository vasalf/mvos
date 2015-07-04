#ifndef PORTS_H
#define PORTS_H

#include <stdint.h>


uint8_t inb(uint16_t port);
void outb(uint16_t port, uint8_t to_send);
uint8_t iob(uint16_t port, uint8_t to_send);
void io_wait(void);

#endif
