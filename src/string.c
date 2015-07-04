#include <string.h>

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

TEMPLATE_UITOA_DEF(uhhtoa, unsigned char)
TEMPLATE_UITOA_DEF(uhtoa, unsigned short int)
TEMPLATE_UITOA_DEF(uitoa, unsigned int)
TEMPLATE_UITOA_DEF(ultoa, unsigned long int)

#define TEMPLATE_ITOA_DEF(NAME, ITYPE, UINAME) \
char *NAME(ITYPE num, char *buf, unsigned int radix) \
{ \
    if (num < 0) \
    { \
        *buf = '-'; \
        return UINAME(-num, buf + 1, radix); \
    } \
    return UINAME(num, buf, radix); \
}

TEMPLATE_ITOA_DEF(hhtoa, char, uhhtoa)
TEMPLATE_ITOA_DEF(htoa, short int, uhtoa)
TEMPLATE_ITOA_DEF(itoa, int, uitoa)
TEMPLATE_ITOA_DEF(ltoa, long int, ultoa)
