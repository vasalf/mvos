#ifndef __STDSTRING_H
#define __STDSTRING_H

#include <stddef.h>
#include <stdint.h>

size_t strlen(const char *str);
#define TEMPLATE_UITOA_DECL(NAME, ITYPE) \
char *NAME(ITYPE num, char *buf, unsigned int radix);

TEMPLATE_UITOA_DECL(uctoa, unsigned char)
TEMPLATE_UITOA_DECL(ustoa, unsigned short int)
TEMPLATE_UITOA_DECL(uitoa, unsigned int)
TEMPLATE_UITOA_DECL(ultoa, unsigned long int)

#endif
