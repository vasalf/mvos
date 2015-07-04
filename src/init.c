#include "include/init.h"
#include "include/vga.h"
#include "include/gdt.h"
#include "include/pic.h"
#include "include/idt.h"
#include "include/timer.h"
#include "include/keyboard.h"

void init_all()
{
    init_vga();
    init_gdt();
    init_pic();
    init_idt();
    init_timer();
    init_keyboard();
}
