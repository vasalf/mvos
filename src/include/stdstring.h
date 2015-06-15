#ifndef __STDSTRING_H
#define __STDSTRING_H

#include <stddef.h>
#include <stdint.h>

size_t strlen(const char *str);

#define TEMPLATE_ITOA_DECL(NAME, ITYPE) \
char *NAME(ITYPE num, char *buf, unsigned int radix);

TEMPLATE_ITOA_DECL(uctoa, unsigned char)
TEMPLATE_ITOA_DECL(ustoa, unsigned short int)
TEMPLATE_ITOA_DECL(uitoa, unsigned int)
TEMPLATE_ITOA_DECL(ultoa, unsigned long int)
TEMPLATE_ITOA_DECL(ctoa, char)
TEMPLATE_ITOA_DECL(stoa, short int)
TEMPLATE_ITOA_DECL(itoa, int)
TEMPLATE_ITOA_DECL(ltoa, long int)

#endif
