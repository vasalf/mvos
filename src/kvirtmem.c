// Kernel memory allocator (for lists, for example).
// Allocates memory only in [KERNEL_RESERVED_BEGIN; KERNEL_RESERVED_END];
//
// Let's assume M = KERNEL_RESERVED_ALLOCLIMIT. Then the allocator works in 
// O(M) for each operation.

// The amount of memory needed in bytes is calculated by:
// sizeof(void*) * KERNEL_RESERVED_ALLOCLIMIT 
// + sizeof(int) * (3 * KERNEL_RESERVED_ALLOCLIMIT)
// + sizeof(size_t) * KERNEL_RESERVEC_ALLOCLIMIT.
// Kernel stack, code and all of its (and those) static arrays should be above
// KERNEL_RESERVED_BEGIN.

#include <kvirtmem.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <system.h>
#include <stdio.h>
#include <string.h>

const int KERNEL_RESERVED_BEGIN = 0x200000; // 2MiB
const int KERNEL_RESERVED_END = 0x400000; // 4MiB
//const int KERNEL_RESERVED_ALLOCLIMIT = 0x2000; 

#define KERNEL_RESERVED_ALLOCLIMIT 0x2000

// 8192 memory segments could only be allocated in one moment.

struct static_stack
{
    int st[KERNEL_RESERVED_ALLOCLIMIT];
    int stop;
};

struct static_stack default_static_stack()
{
    struct static_stack st;
    st.stop = -1;
    return st;
}

void static_stack_push(struct static_stack* st, int a)
{
    (st->st)[++(st->stop)] = a;
}

int static_stack_top(struct static_stack* st)
{
    return st->st[st->stop];
}

int static_stack_pop(struct static_stack* st)
{
    if (st->stop < 0)
        panic("static_stack_pop: kvirtmem function is trying to pop from an empty stack");
    uint32_t index = st->stop;
    (st->stop)--;
    return (st->st)[index];
}

size_t static_stack_size(struct static_stack* st)
{
    return st->stop + 1;
}

void* ptr_to_the_beginning[KERNEL_RESERVED_ALLOCLIMIT + 2];
int next_allocated[KERNEL_RESERVED_ALLOCLIMIT + 2];
int prev_allocated[KERNEL_RESERVED_ALLOCLIMIT + 2];
size_t allocated_size[KERNEL_RESERVED_ALLOCLIMIT + 2];
int num_allocated;
struct static_stack free_indices;

void clear_mem(void* begin, void* end)
{
    while (begin < end)
    
    {
        *((uint8_t*)begin) = 0;
        begin++;
    }
}

inline void clear_array(void* begin, size_t size, size_t num)
{
    clear_mem(begin, begin + size * num);
}

void init_kvirtmem()
{
    num_allocated = 0;
    clear_array(ptr_to_the_beginning, sizeof(void*), KERNEL_RESERVED_ALLOCLIMIT + 2);
    clear_array(next_allocated, sizeof(int), KERNEL_RESERVED_ALLOCLIMIT + 2);
    clear_array(prev_allocated, sizeof(int), KERNEL_RESERVED_ALLOCLIMIT + 2);
    clear_array(allocated_size, sizeof(size_t), KERNEL_RESERVED_ALLOCLIMIT + 2);
    ptr_to_the_beginning[0] = (void*)KERNEL_RESERVED_BEGIN;
    next_allocated[0] = 1;
    prev_allocated[0] = -1;
    next_allocated[1] = -1;
    prev_allocated[1] = 0;
    allocated_size[0] = 4;
    ptr_to_the_beginning[1] = (void*)KERNEL_RESERVED_END;
    free_indices = default_static_stack();
    for (int i = 2; i < KERNEL_RESERVED_ALLOCLIMIT + 2; i++)
        static_stack_push(&free_indices, i);
}

inline size_t distance(void* a, void* b)
{
    return b - a;
}

void* kmalloc(size_t size)
{
    assert(size > 0);
    while (size % 4 > 0)
        size++;
    if (num_allocated == KERNEL_RESERVED_ALLOCLIMIT)
    {
        printf("kmalloc: Too many segments allocated\n");
        return NULL;
    }
    int cur = 0;
    bool found = false;
    while (!found && cur != 1)
    {
        if (distance(ptr_to_the_beginning[cur] + allocated_size[cur], 
                     ptr_to_the_beginning[next_allocated[cur]]) >= size)
            found = true;
        else
            cur = next_allocated[cur];
    }
    if (!found)
    {
        printf("kmalloc: Segment of exact length was not found\n");
        return NULL;
    }
    int i = static_stack_pop(&free_indices);
    assert(!is_allocated(ptr_to_the_beginning[cur] + allocated_size[cur]));
    ptr_to_the_beginning[i] = ptr_to_the_beginning[cur] + allocated_size[cur];
    allocated_size[i] = size;
    next_allocated[i] = next_allocated[cur];
    prev_allocated[i] = cur;
    prev_allocated[next_allocated[i]] = i;
    next_allocated[cur] = i;
    num_allocated++;
    return ptr_to_the_beginning[i];
}

int find_ptr(void* ptr)
{
    int t = -1;
    for (int i = 0; i < KERNEL_RESERVED_ALLOCLIMIT + 2 && t == -1; i++)
        if (ptr_to_the_beginning[i] == ptr)
            t = i;
    return t;
}

void kfree(void* ptr)
{
    int t = find_ptr(ptr);
    if (t == -1)
        panic("kfree: Trying to free unallocated or used memory.");
    prev_allocated[next_allocated[t]] = prev_allocated[t];
    next_allocated[prev_allocated[t]] = next_allocated[t];
    ptr_to_the_beginning[t] = NULL;
    num_allocated--;
    static_stack_push(&free_indices, t);
}

void* stupid_krealloc(void* ptr, size_t size)
{
    int t = find_ptr(ptr);
    if (t == -1)
        panic("krealloc: Trying to reallocate unallocated or used memory.");
    if (distance(ptr, ptr_to_the_beginning[next_allocated[t]]) > size)
        return NULL;
    allocated_size[t] = size;
    return ptr;
}

void* krealloc(void* ptr, size_t size)
{
    if (stupid_krealloc(ptr, size))
        return ptr;
    kfree(ptr);
    return kmalloc(size);
}

void* kcalloc(size_t num, size_t size)
{
    void* ptr = kmalloc(num * size);
    if (ptr == NULL)
        return NULL;
    clear_array(ptr, size, num);
    return ptr;
}

// Here comes some useful debug stuff

bool is_allocated(void* ptr)
{
    return find_ptr(ptr) != -1; 
}
