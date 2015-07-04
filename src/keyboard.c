#include "include/keyboard.h"
#include "include/wrappers.h"
#include "include/ports.h"
#include "include/vga.h"
#include "include/system.h"
#include "include/string.h"
#include "include/pic.h"
#include "include/idt.h"

uint16_t keyboard_port;

static void print_hex_char(unsigned char c)
{
    vga_puts("0x");
    char buf[2];
    uhhtoa(c, buf, 16);
    vga_puts(buf);
}

static void detect_keyboard(void)
{
    for (unsigned short port = 0; port < 0x100; port++)
    {
        if (port != 0xa0)
        {
            if (iob(port, 0xee) == 0xee && iob(port, 0xf5) == 0xfa)
            {
                unsigned char t1 = 0, t2 = 0, t3 = 0;
                t1 = iob(port, 0xf2);
                if (t1 != 0xfa)
                    continue;
                t1 = inb(port);
                if (t1 == 0xab)
                {
                    t2 = inb(port);
                    if (t2 == 0xab || t2 == 0x41)
                        t3 = inb(port);
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

void keyboard_isr()
{
    vga_puts("keyboard_handler called.\n");
    uint8_t signal = inb(keyboard_port);
    vga_puts("Keyboard sent ");
    print_hex_char(signal);
    vga_puts(".\n");
    pic_eoi(1);
}

void init_keyboard(void)
{
    //detect_keyboard();
    keyboard_port = 0x60;
    vga_puts("Added descriptor.\n");
    vga_puts("_asm_keyboard_isr address is 0x");
    char buf[10];
    uitoa((uint32_t)_asm_keyboard_isr, buf, 16);
    vga_puts(buf);
    vga_puts("\n");
    vga_puts("keyboard_isr address is 0x");
    uitoa((uint32_t)keyboard_isr, buf, 16);
    vga_puts(buf);
    vga_puts("\n");
}
