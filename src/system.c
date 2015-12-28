#include <system.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

void _panic(char *msg, char *file, int line, ...)
{
    va_list vl;
    __asm__ __volatile__ ("cli");
    printf("%s:%d: ", file, line);
    if (msg) 
    {
        printf("KERNEL PANIC: ");
        va_start(vl, line);
        printf(msg, vl);
        va_end(vl);
    }
    else 
    {
        printf("KERNEL PANIC");
    }
    for (;;) 
    {
        __asm__ __volatile__ ("hlt");
    }
}


