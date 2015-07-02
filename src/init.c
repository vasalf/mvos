#include "include/init.h"
#include "include/vga.h"
#include "include/keyboard.h"
#include "include/ports.h"
#include "include/idt.h"

void init_all()
{
    vga_init();
    idt_init();
    init_keyboard();
}
