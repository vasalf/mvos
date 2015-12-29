#ifndef QUEUE_H
#define QUEUE_H

#include <vector.h>
#include <system.h>

#define TEMPLATE_QUEUE_STRUCT_DECLARATION(TYPE, NAME) \
TEMPLATE_VECTOR_STRUCT_DECLARATION(TYPE, __##NAME##_vector) \
typedef struct \
{ \
    __##NAME##_vector in, out; \
} NAME; \
\
NAME NAME##_init(); \
void NAME##_push(NAME* q, TYPE elem); \
TYPE NAME##_front(NAME* q); \
TYPE NAME##_pop(NAME* q); \
void NAME##_free(NAME* q);

#define TEMPLATE_QUEUE_FUNC_DECLARATION(TYPE, NAME) \
TEMPLATE_VECTOR_FUNC_DECLARATION(TYPE, __##NAME##_vector) \
\
NAME NAME##_init() \
{ \
    NAME q; \
    q.in = __##NAME##_vector_init(); \
    q.out = __##NAME##_vector_init(); \
    return q; \
} \
\
void NAME##_push(NAME* q, TYPE elem) \
{ \
    __##NAME##_vector_push_back(&(q->in), elem); \
} \
\
TYPE NAME##_front(NAME* q) \
{ \
    if (q->out.size == 0) \
    { \
        while (q->in.size > 0) \
            __##NAME##_vector_push_back(&(q->out), __##NAME##_vector_pop_back(&(q->in))); \
    } \
    return q->out.arr[q->out.size - 1]; \
} \
\
TYPE NAME##_pop(NAME* q) \
{ \
    if (q->out.size == 0) \
    { \
        while (q->in.size > 0) \
            __##NAME##_vector_push_back(&(q->out), __##NAME##_vector_pop_back(&(q->in))); \
    } \
    return __##NAME##_vector_pop_back(&(q->out)); \
} \
\
void NAME##_free(NAME* q) \
{ \
    __##NAME##_vector_free(&(q->in)); \
    __##NAME##_vector_free(&(q->out)); \
}

#endif //QUEUE_H
