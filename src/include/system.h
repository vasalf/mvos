#ifndef SYSTEM_H
#define SYSTEM_H


#include <stdint.h>

#define panic(msg, ...) _panic(msg, __FILE__, __LINE__, ##__VA_ARGS__)
void _panic(char *msg, char *file, int line, ...);

#define assert(f) if (!(f)) panic("assertion \""#f"\" failed.")

#endif
