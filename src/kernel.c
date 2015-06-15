#include <stdint.h>
#include <stddef.h>
#include "include/vga.h"
#include "include/stdstring.h"

unsigned char response(unsigned short port)
{
    char ans;
    __asm__ __volatile__ ("inb %1, %0" : "=a"(ans) : "dN"(port));
    return ans;
}

unsigned char send_command(unsigned short port, unsigned char val)
{
    __asm__ __volatile__ ("outb %0, %1" : : "a"(val), "dN"(port));
    char ans;
    __asm__ __volatile__ ("inb %1, %0" : "=a"(ans) : "dN"(port));
    return ans;
}

// This calls send_command while the response is 0xfe (RESEND)
unsigned char get_response_for(unsigned short port, unsigned char val)
{
    unsigned char res = send_command(port, val);
    while (res == 0xfe)
        res = send_command(port, val);
    return res;
}

void print_hex_char(unsigned char c)
{
    char buf[10];
    uctoa(c, buf, 16);
    vga_puts("0x");
    vga_puts(buf);
}

void read_port(unsigned short port)
{
    unsigned char ans = get_response_for(port, 0xee);
    if (ans == 0xee)
    {
        print_hex_char(port); vga_puts(" responsed "); print_hex_char(ans);
        vga_puts(" ... ");
        ans = get_response_for(port, 0xf5);
        if (ans != 0xfa)
        {
            vga_puts("Something got wrong (");
            print_hex_char(ans);
            vga_puts(")\n");
            return;
        }
        ans = get_response_for(port, 0xf2);
        ans = response(port);
        print_hex_char(ans);
        vga_puts(" ");
        if (ans == 0xab)
        {
            ans = response(port);
            print_hex_char(ans); vga_puts(" ");
            if (ans == 0xab || ans == 0x41)
            {
                print_hex_char(response(port));
            }
        }
        vga_puts("\n");
    }
}

void kernel_main(void)
{
    vga_init();
    for (int port = 0; port <= 0x99; port++)
    {
        read_port(port);
    }
    for (int port = 0xa1; port <= 0xff; port++)
    {
        read_port(port);
    }
    for (;;);
    return;
}
