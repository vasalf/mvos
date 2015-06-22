#include <stdint.h>
#include "include/ports.h"

uint8_t read_from_port(uint16_t port)
{
    uint8_t ans;
    __asm__ __volatile__ ("inb %1, %0" : "=a"(ans) : "dN"(port));
    return ans;
}

void send_to_port(uint16_t port, uint8_t to_send)
{
    __asm__ __volatile__ ("outb %0, %1" : : "a"(to_send), "dN"(port));
}

uint8_t get_response(uint16_t port, uint8_t to_send)
{
    uint8_t ans;
    send_to_port(port, to_send);
    while ((ans = read_from_port(port)) == 0xfe)
        send_to_port(port, to_send);
    return ans;
}

