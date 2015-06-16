#include "include/ports.h"

unsigned char read_from_port(unsigned short port)
{
    unsigned char ans;
    __asm__ __volatile__ ("inb %1, %0" : "=a"(ans) : "dN"(port));
    return ans;
}

void send_to_port(unsigned short port, unsigned char to_send)
{
    __asm__ __volatile__ ("outb %0, %1" : : "a"(to_send), "dN"(port));
}

unsigned char get_response(unsigned short port, unsigned char to_send)
{
    unsigned char ans;
    send_to_port(port, to_send);
    while ((ans = read_from_port(port)) == 0xfe)
        send_to_port(port, to_send);
    return ans;
}

