#include "include/stdstring.h"

size_t strlen(const char *str)
{
    size_t ret = 0;
    while ( str[ret] != 0 )
        ret++;
    return ret;
}

#define TEMPLATE_UITOA_DEF(NAME, ITYPE) \
char *NAME(ITYPE num, char *buf, unsigned int radix) \
{ \
    if (num < radix) \
    { \
        if (num <= 9) \
            *buf = '0' + num; \
         else \
            *buf = 'a' + num - 10; \
        *(buf + 1) = '\0'; \
        return buf + 1; \
    } \
    char *next = NAME(num / radix, buf, radix); \
    if (num % radix <= 9) \
        *next = '0' + num % radix; \
    else \
        *next = 'a' + num % radix - 10; \
    next++; \
    *next = '\0'; \
    return next; \
}

TEMPLATE_UITOA_DEF(uctoa, unsigned char)
TEMPLATE_UITOA_DEF(ustoa, unsigned short int)
TEMPLATE_UITOA_DEF(uitoa, unsigned int)
TEMPLATE_UITOA_DEF(ultoa, unsigned long int)
