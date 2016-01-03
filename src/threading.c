#include <threading.h>
#include <vector.h>
#include <queue.h>
#include <system.h>
#include <kvirtmem.h>
#include <stdio.h>
#include <stdbool.h>
#include <asm/threading.h>

TEMPLATE_QUEUE_FUNC_DECLARATION(thread, thread_queue_t)

thread_queue_t thread_queue;

TEMPLATE_VECTOR_STRUCT_DECLARATION(int, index_vector_t)
TEMPLATE_VECTOR_FUNC_DECLARATION(int, index_vector_t)

static index_vector_t opened_indices;

void init_threading(void)
{
    thread_queue = thread_queue_t_init();
    opened_indices = index_vector_t_init();
    for (int i = KERNEL_MAX_THREADS - 1; i >= 0; i--)
        index_vector_t_push_back(&opened_indices, i);
}

thread init_thread(void (*f)(void))
{
    thread ret;
    ret.eip = f;
    if (opened_indices.size == 0)
        panic("init_thread: cannot open kernel thread: no more threads available");
    ret.id = index_vector_t_pop_back(&opened_indices);
    ret.esp = (void*)(KERNEL_THREADS_STACK_BEGIN + KERNEL_THREAD_STACK_SIZE * (ret.id + 1));
    printf("init_thread: initializing thread of address %p\n", f);
    printf("init_thread: id=%d, eip=%p, esp=%p\n", ret.id, ret.eip, ret.esp);
    void* my_esp;
    __asm__ __volatile__("movl    %%esp, %0   \n" : "=r"(my_esp));
    printf("init_thread: ret.esp=%p my_esp=%p\n", ret.esp, my_esp);
    __asm__ __volatile__("movl    %%esp, %%ebx\n\t"
                         "movl    %%ebp, %%ecx\n\t"
                         "movl    %%eax, %%esp\n\t"
                         "movl    %%eax, %%ebp\n\t"
                         "pusha               \n\t"
                         "movl    %%esp, %%eax\n\t"
                         "movl    %%ebx, %%esp\n\t"
                         "movl    %%ecx, %%ebp\n\t": "=a"(ret.esp) : "a"(ret.esp), "b"(0), "c"(0));
    printf("init_thread: id=%d, eip=%p, esp=%p\n", ret.id, ret.eip, ret.esp);
    return ret; 
}

// @param initial should be true only if the function is called for the first time
static void run_thread(bool initial, void* next_eip, void* next_esp)
{
    printf("run_thread: launched with args initial=%d next_eip=%p next_esp=%p\n", initial, next_eip, next_esp);
    if (thread_queue.in.size + thread_queue.out.size == 0)
        panic("run_thread: no kernel threads are alive");
    if (!initial)
    {
        thread cur = thread_queue_t_pop(&thread_queue);
        cur.eip = next_eip;
        cur.esp = next_esp;
        thread_queue_t_push(&thread_queue, cur);
    }
    else
    {
        assert(next_eip == NULL);
        assert(next_esp == NULL);
    }
    thread th = thread_queue_t_front(&thread_queue);
    printf("run_thread: launching thread with id=%d, eip=%p, esp=%p\n", th.id, th.eip, th.esp);
    _asm_run_thread(th.esp, th.eip);
}

void run_threading(void)
{
    printf("Kernel switched to multithreading mode\n");
    printf("Number of registered threads now: %d\n", thread_queue.in.size + thread_queue.out.size);
    run_thread(true, NULL, NULL);
    return;
    for (;;)
    {
        __asm__ __volatile__("hlt");
    }
}
