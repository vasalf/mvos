#include <init.h>
#include <stdio.h>
#include <asm/registers.h>
#include <threading.h>
#include <timer.h>
#include <stdint.h>

// An idle thread. We need it to ensure that computer will shutdown correctly.
static void kernel_main_thread(void)
{
#ifdef DEBUG_THREADING
    printf("kernel_main_thread: successfully entered the main thread\n");
    volatile uint32_t last_uptime = uptime;
#endif
    for (;;)
    {
#ifdef DEBUG_THREADING
        if (uptime - last_uptime >= TIMER_FREQ)
        {
            printf("kernel_main_thread: uptime: %ds\n", uptime / TIMER_FREQ);
            last_uptime = uptime;
        }
#else
        __asm__ __volatile__("hlt");
#endif
    }
}

static void register_main_thread(void)
{
    thread th = init_thread(kernel_main_thread);
    thread_queue_t_push(&thread_queue, th);
}

void kernel_main(void)
{
    init_all();
    printf("Kernel loaded\n");
    printf("EIP: %#X\n", get_eip());
    printf("CR0: %#b\n", get_cr0());
    printf("Interrupts enabled\n");
    __asm__ __volatile__ ("sti");

    printf("kernel_main_thread address: %p\n", kernel_main_thread);
    /*for (;;)
    {
        __asm__ __volatile__("hlt");
    }*/

    register_main_thread();
    run_threading();
    for (;;)
    {
        __asm__ __volatile__("hlt");
    }
    return;
}
