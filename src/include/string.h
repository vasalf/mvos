#ifndef STRING_H
#define STRING_H

#include <stddef.h>
#include <stdint.h>


size_t strlen(const char *str);

#define TEMPLATE_ITOA_DECL(NAME, ITYPE) \
char *NAME(ITYPE num, char *buf, unsigned int radix);

TEMPLATE_ITOA_DECL(uhhtoa, unsigned char)
TEMPLATE_ITOA_DECL(uhtoa, unsigned short int)
TEMPLATE_ITOA_DECL(uitoa, unsigned int)
TEMPLATE_ITOA_DECL(ultoa, unsigned long int)
TEMPLATE_ITOA_DECL(hhtoa, char)
TEMPLATE_ITOA_DECL(htoa, short int)
TEMPLATE_ITOA_DECL(itoa, int)
TEMPLATE_ITOA_DECL(ltoa, long int)

#endif
