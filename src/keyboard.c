#include "include/ports.h"
#include "include/keyboard.h"
#include "include/vga.h"
#include "include/system.h"
#include "include/stdstring.h"
#include "include/idt.h"

extern void _wrap_keyboard_handler();

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

void keyboard_handler()
{
    vga_puts("keyboard_handler called.\n");
    uint8_t signal = read_from_port(keyboard_port);
    vga_puts("Keyboard sent ");
    print_hex_char(signal);
    vga_puts(".\n");
}

extern void get_eip();

void init_keyboard()
{
    //detect_keyboard();
    keyboard_port = 0x60;
    vga_puts("In init_keyboard()\n");
    int eipreg;
    get_eip();
    __asm__ __volatile__ ("movl %%ebx, %%eax" : "=a"(eipreg));
    vga_puts("EIP: 0x");
    char buf[10];
    itoa(eipreg, buf, 16);
    vga_puts(buf);
    vga_puts("\n");
    set_idt_descriptor(33, _wrap_keyboard_handler);
    vga_puts("Added descriptor.\n");
    vga_puts("_wrap_keyboard_handler address is 0x");
    uitoa((uint32_t)&_wrap_keyboard_handler, buf, 16);
    vga_puts(buf);
    vga_puts("\n");
    vga_puts("keyboard_handler address is 0x");
    uitoa((uint32_t)&keyboard_handler, buf, 16);
    vga_puts(buf);
    vga_puts("\n");
}
