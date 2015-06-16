#include <stdint.h>
#include <stddef.h>
#include "include/vga.h"
#include "include/stdstring.h"
#include "include/ports.h"
#include "include/keyboard.h"

void kernel_main(void)
{
    vga_init();
    detect_keyboard();
    vga_puts("Kernel loaded\n");
    for (;;);
    return;
}
