#include "include/ports.h"
#include "include/keyboard.h"
#include "include/vga.h"
#include "include/system.h"
#include "include/stdstring.h"

void print_hex_char(unsigned char c)
{
    vga_puts("0x");
    char buf[2];
    uctoa(c, buf, 16);
    vga_puts(buf);
}


void detect_keyboard()
{
    for (unsigned short port = 0; port < 0x100; port++)
    {
        if (port != 0xa0)
        {
            if (get_response(port, 0xee) == 0xee && get_response(port, 0xf5) == 0xfa)
            {
                unsigned char t1 = 0, t2 = 0, t3 = 0;
                t1 = get_response(port, 0xf2);
                if (t1 != 0xfa)
                    continue;
                t1 = read_from_port(port);
                if (t1 == 0xab)
                {
                    t2 = read_from_port(port);
                    if (t2 == 0xab || t2 == 0x41)
                        t3 = read_from_port(port);
                }
                if (t1 == 0x00 || t1 == 0xab)
                {
                    vga_puts("Detected keyboard at port ");
                    print_hex_char(port);
                    vga_puts(" (type ");
                    print_hex_char(t1); 
                    if (t1 == 0xab)
                    {
                        vga_putchar(' ');
                        print_hex_char(t2);
                    }
                    if (t2 == 0xab || t2 == 0x41)
                    {
                        vga_putchar(' ');
                        print_hex_char(t3);
                    }
                    vga_puts(")\n");
                    keyboard_port = port;
                    return;
                }
            }
        }
    }
    panic("No keyboards found");
}
