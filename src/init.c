#include <init.h>
#include <vga.h>
#include <gdt.h>
#include <pic.h>
#include <idt.h>
#include <timer.h>
#include <keyboard.h>
#include <kvirtmem.h>

void init_all()
{
    init_vga();
    //init_kvirtmem();
    init_gdt();
    init_pic();
    init_idt();
    init_timer();
    init_keyboard();
}
