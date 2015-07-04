#ifndef DBG_H
#define DBG_H


#define get_eip(X) \
do { \
    _asm_get_eip(); \
    __asm__ __volatile__ ("movl %%ebx, %%eax" : "=a"(X)); \
} while (0)
#define get_cr0(X) __asm__ __volatile__ ("movl %%cr0, %%eax" : "=a"(X))
void _asm_get_eip(void);

#endif
