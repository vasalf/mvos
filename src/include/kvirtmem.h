#ifndef KVIRTMEM_H
#define KVIRTMEM_H

#include <stddef.h>

// Here comes headers for some useful debug stuff
#include <stdbool.h>

void init_kvirtmem();

extern const int KERNEL_RESERVED_BEGIN;
extern const int KERNEL_RESERVED_END;

void* kcalloc(size_t num, size_t size);
void kfree(void* ptr);
void* krealloc(void* ptr, size_t size);
void* kmalloc(size_t size);

// Here comes some useful debug stuff 
bool is_allocated(void* ptr);

#endif //KVIRTMEM_H
