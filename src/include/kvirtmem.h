#ifndef KVIRTMEM_H
#define KVIRTMEM_H

#include <stddef.h>

void init_kvirtmem();

extern const int KERNEL_RESERVED_BEGIN;
extern const int KERNEL_RESERVED_END;

void* kcalloc(size_t num, size_t size);
void kfree(void* ptr);
void* krealloc(void* ptr, size_t size);
void* kmalloc(size_t size);

#endif //KVIRTMEM_H
