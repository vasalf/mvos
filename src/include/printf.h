#ifndef PRINTF_H
#define PRINTF_H


#include <stdarg.h>

int vprintf(const char *format, va_list vl);
int printf(const char *format, ...);

#endif
