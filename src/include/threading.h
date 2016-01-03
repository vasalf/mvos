#ifndef THREADING_H
#define THREADING_H

#include <queue.h>
#include <kvirtmem.h>

#define KERNEL_MAX_THREADS 16

#define KERNEL_THREAD_STACK_SIZE 0x100000 // 1 MiB
#define KERNEL_THREADS_STACK_BEGIN KERNEL_RESERVED_END
#define KERNEL_THREADS_STACK_END KERNEL_THREADS_STACK_BEGIN + KERNEL_MAX_THREADS * KERNEL_THREAD_STACK_SIZE

typedef struct
{
    void* eip;
    void* esp;
    int id;
} thread;

TEMPLATE_QUEUE_STRUCT_DECLARATION(thread, thread_queue_t)
extern thread_queue_t thread_queue;

void init_threading(void);
thread init_thread(void (*f)(void));

void run_threading(void);

#endif //THREADING_H
