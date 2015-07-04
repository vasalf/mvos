#include <stdint.h>
#include "include/ports.h"

uint8_t inb(uint16_t port)
{
    uint8_t ans;
    __asm__ __volatile__ ("inb %1, %0" : "=a"(ans) : "dN"(port));
    return ans;
}

void outb(uint16_t port, uint8_t to_send)
{
    __asm__ __volatile__ ("outb %0, %1" : : "a"(to_send), "dN"(port));
}

uint8_t iob(uint16_t port, uint8_t to_send)
{
    uint8_t ans;
    outb(port, to_send);
    while ((ans = inb(port)) == 0xfe)
        outb(port, to_send);
    return ans;
}

void io_wait(void) {
    __asm__ __volatile__ (
        "nop\n"
        "nop\n"
        "nop\n"
    );
}
