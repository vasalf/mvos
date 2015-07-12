#include <init.h>
#include <stdio.h>
#include <string.h>
#include <asm/registers.h>

void kernel_main(void)
{
    init_all();
    printf("Kernel loaded\n");
    printf("EIP: %#X\n", get_eip());
    printf("CR0: %#X\n", get_cr0());
    __asm__ __volatile__ ("sti");
    printf("Interrupts enabled\n");
    for (;;) {
        __asm__ __volatile__ ("hlt\n");
    }
    return;
}
