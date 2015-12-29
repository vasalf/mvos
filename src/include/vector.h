#ifndef VECTOR_H
#define VECTOR_H

#include <stdint.h>
#include <kvirtmem.h>

#define VECTOR_DEFAULT_CAPACITY 4

#define TEMPLATE_VECTOR_STRUCT_DECLARATION(TYPE, NAME) \
typedef struct \
{ \
    TYPE* arr; \
    size_t size; \
    size_t capacity; \
} NAME; \
\
NAME NAME##_init();\
void NAME##_resize(NAME* vec, size_t new_size); \
void NAME##_push_back(NAME* vec, TYPE elem); \
TYPE NAME##_pop_back(NAME* vec); \
void NAME##_free(NAME* vec);

#define TEMPLATE_VECTOR_FUNC_DECLARATION(TYPE, NAME) \
NAME NAME##_init() \
{ \
    NAME vec; \
    vec.arr = kmalloc(sizeof(TYPE) * VECTOR_DEFAULT_CAPACITY); \
    vec.size = 0; \
    vec.capacity = VECTOR_DEFAULT_CAPACITY; \
    return vec; \
} \
\
void NAME##_resize(NAME* vec, size_t new_size) \
{ \
    size_t new_capacity = vec->capacity; \
    if (new_size < vec->size) \
    { \
        while (3 * new_size < new_capacity) \
            new_capacity >>= 1; \
    } \
    else \
    { \
        while (2 * new_size > new_capacity) \
            new_capacity <<= 1; \
    } \
    if (new_capacity < VECTOR_DEFAULT_CAPACITY) \
        new_capacity = VECTOR_DEFAULT_CAPACITY; \
    if (new_capacity != vec->capacity) \
    { \
        TYPE* new_arr = kmalloc(sizeof(TYPE) * new_capacity); \
        assert(new_arr != vec->arr); \
        memcpy(new_arr, vec->arr, sizeof(TYPE) * new_size); \
        kfree(vec->arr); \
        vec->arr = new_arr; \
        vec->size = new_size; \
        vec->capacity = new_capacity; \
    } \
    else \
        vec->size = new_size; \
} \
\
void NAME##_push_back(NAME* vec, TYPE elem) \
{ \
    size_t lsz = vec->size; \
    NAME##_resize(vec, vec->size + 1); \
    if (lsz + 1 != vec->size) \
        panic("What the fuck is going on?!!\n"); \
    vec->arr[vec->size - 1] = elem; \
} \
\
TYPE NAME##_pop_back(NAME* vec) \
{ \
    if (vec->size == 0) \
        panic("kenel attempted to pop from an empty vector"); \
    TYPE ret = vec->arr[vec->size - 1]; \
    NAME##_resize(vec, vec->size - 1); \
    return ret; \
} \
\
void NAME##_free(NAME* vec) \
{ \
    kfree(vec->arr); \
}

#endif //VECTOR_H
