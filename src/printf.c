#include <printf.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#include <vga.h>
#include <kvirtmem.h>
#include <asm/registers.h>
#include <system.h>

#define FLAG_LEFT   (1 << 0)
#define FLAG_SIGN   (1 << 1)
#define FLAG_SPACE  (1 << 2)
#define FLAG_ZERO   (1 << 4)
#define FLAG_ALT    (1 << 5)

static const char *printf_flags(const char *format, int *flags) {
    *flags = 0;
    for (;; ++format) {
        switch (*format) {
        case '-':
            *flags |= FLAG_LEFT;
            break;
        case '+':
            *flags |= FLAG_SIGN;
            break;
        case ' ':
            *flags |= FLAG_SPACE;
            break;
        case '0':
            *flags |= FLAG_ZERO;
            break;
        case '#':
            *flags |= FLAG_ALT;
            break;
        default:
            return format;
        }
    }
}

static const char *printf_width(const char *format, int *width) {
    *width = -1;
    if (*format == '*') {
        *width = -2;
        return format + 1;
    }
    for (;; ++format) {
        if ('0' <= *format && *format <= '9') {
            *width *= 10;
            *width += *format - '0';
        } else {
            return format;
        }
    }
}

#define SIZE_       (1 << 0)
#define SIZE_l      (1 << 1)
#define SIZE_ll     (1 << 2)
#define SIZE_h      (1 << 3)
#define SIZE_hh     (1 << 4)
#define SIZE_j      (1 << 5)
#define SIZE_z      (1 << 6)
#define SIZE_t      (1 << 7)

static const char *printf_size(const char *format, int *size) {
    *size = SIZE_;
    switch (*format) {
    case 'l':
        if (*(format + 1) == 'l') {
            *size = SIZE_ll;
            ++format;
        } else {
            *size = SIZE_l;
        }
        break;
    case 'h':
        if (*(format + 1) == 'h') {
            *size = SIZE_hh;
            ++format;
        } else {
            *size = SIZE_h;
        }
        break;
    case 'j':
        *size = SIZE_j;
        break;
    case 'z':
        *size = SIZE_z;
        break;
    case 't':
        *size = SIZE_t;
        break;
    default:
        return format;
    }
    return format + 1;
}

#define TYPE_d      (1 << 0)
#define TYPE_o      (1 << 1)
#define TYPE_u      (1 << 2)
#define TYPE_x      (1 << 3)
#define TYPE_X      (1 << 4)
#define TYPE_b      (1 << 5)
#define TYPE_p      (1 << 6)
#define TYPE_n      (1 << 7)

#define TYPE_s      (1 << 8)
#define TYPE_c      (1 << 9)
#define TYPE_PERC   (1 << 10)

#define TYPE_SIGNED (TYPE_d | TYPE_n)
#define TYPE_UNSIGNED (TYPE_u | TYPE_p | TYPE_o | TYPE_x | TYPE_X | TYPE_b)

static const char *printf_type(const char *format, int *type) {
    *type = -1;
    switch (*format) {
    case 'd': case 'i':
        *type = TYPE_d;
        break;
    case 'o':
        *type = TYPE_o;
        break;
    case 'u':
        *type = TYPE_u;
        break;
    case 'x':
        *type = TYPE_x;
        break;
    case 'X':
        *type = TYPE_X;
        break;
    case 'b':
        *type = TYPE_b;
        break;
    case 'c':
        *type = TYPE_c;
        break;
    case 's':
        *type = TYPE_s;
        break;
    case 'p':
        *type = TYPE_p;
        break;
    case 'n':
        *type = TYPE_n;
        break;
    case '%':
        *type = TYPE_PERC;
        break;
    default:
        return format;
    }
    return format + 1;
}

static int printf_ibuflen(intmax_t n, int radix) {
    int ret = 0;
    if (n == 0) {
        return 1;
    }
    if (n < 0) {
        n = -n;
    }
    while (n) {
        n /= radix;
        ++ret;
    }
    return ret;
}

static int printf_ubuflen(uintmax_t n, int radix) {
    int ret = 0;
    if (n == 0) {
        return 1;
    }
    while (n) {
        n /= radix;
        ++ret;
    }
    return ret;
}

static char *printf_itoa(char *buf, intmax_t n, int radix, char cap_base) {
    if (n < 0) {
        n = -n;
    }
    if (n >= radix) {
        buf = printf_itoa(buf, n / radix, radix, cap_base);
    }
    n %= radix;
    if (n < 10) {
        buf[0] = '0' + n;
    } else {
        buf[0] = cap_base + n - 10;
    }
    buf[1] = 0;
    return buf + 1;
}

static char *printf_utoa(char *buf, uintmax_t n, unsigned int radix, char cap_base) {
    if (n >= radix) {
        buf = printf_utoa(buf, n / radix, radix, cap_base);
    }
    n %= radix;
    if (n < 10) {
        buf[0] = '0' + n;
    } else {
        buf[0] = cap_base + n - 10;
    }
    buf[1] = 0;
    return buf + 1;
}

static int printf_strlen(const char *str) {
    int res = 0;
    for (; *str; ++str) {
        ++res;
    }
    return res;
}

static void printf_strcpy(char *dst, const char *src) {
    while (*src) {
        *dst++ = *src++;
    }
}

int vprintf(const char *format, va_list vl) {
    intmax_t sarg = 0;
    uintmax_t uarg = 0;
    char *string_arg = 0;

    const char *i = 0;
    char *buf = NULL;
    char *bufpos = 0, *j = 0;
    int ret = 0, flags = 0, width = 0, size = 0, type = 0, buflen = 0;

    for (i = format; *i; ++i) {
        if (*i != '%') {
            vga_putchar(*i);
            ++ret;
        } else {
            ++i;
            i = printf_flags(i, &flags);
            i = printf_width(i, &width);
            i = printf_size(i, &size);
            i = printf_type(i, &type);
            --i;
            if (width == -2) {
                width = va_arg(vl, unsigned int);
            }
            switch (type) {
            case TYPE_d:
                switch (size) {
                case SIZE_hh:
                    sarg = (intmax_t) ((unsigned char) va_arg(vl, int));
                    break;
                case SIZE_h:
                    sarg = (intmax_t) ((signed short int) va_arg(vl, int));
                    break;
                case SIZE_:
                    sarg = (intmax_t) va_arg(vl, signed int);
                    break;
                case SIZE_l:
                    sarg = (intmax_t) va_arg(vl, signed long int);
                    break;
                case SIZE_ll:
                    sarg = (intmax_t) va_arg(vl, signed long long int);
                    break;
                case SIZE_j:
                    sarg = (intmax_t) va_arg(vl, intmax_t);
                    break;
                case SIZE_z:
                    sarg = (intmax_t) va_arg(vl, size_t);
                    break;
                case SIZE_t:
                    sarg = (intmax_t) va_arg(vl, ptrdiff_t);
                    break;
                }
                break;
            case TYPE_o:
            case TYPE_x:
            case TYPE_X:
            case TYPE_b:
            case TYPE_u:
                switch (size) {
                case SIZE_hh:
                    uarg = (uintmax_t) ((unsigned char) va_arg(vl, unsigned int));
                    break;
                case SIZE_h:
                    uarg = (uintmax_t) ((unsigned short int) va_arg(vl, unsigned int));
                    break;
                case SIZE_:
                    uarg = (uintmax_t) va_arg(vl, unsigned int);
                    break;
                case SIZE_l:
                    uarg = (uintmax_t) va_arg(vl, unsigned long int);
                    break;
                case SIZE_ll:
                    uarg = (uintmax_t) va_arg(vl, unsigned long long int);
                    break;
                case SIZE_j:
                    uarg = (uintmax_t) va_arg(vl, intmax_t);
                    break;
                case SIZE_z:
                    uarg = (uintmax_t) va_arg(vl, size_t);
                    break;
                case SIZE_t:
                    uarg = (uintmax_t) va_arg(vl, ptrdiff_t);
                    break;
                }
                break;
            case TYPE_c:
                uarg = (intmax_t) ((char) va_arg(vl, int));
                break;
            case TYPE_p:
                uarg = (uintmax_t) ((uintptr_t) va_arg(vl, void *));
                flags |= FLAG_ALT;
                break;
            case TYPE_n:
                switch (size) {
                case SIZE_hh:
                    sarg = (intmax_t) *va_arg(vl, unsigned char *);
                    break;
                case SIZE_h:
                    sarg = (intmax_t) *va_arg(vl, short int *);
                    break;
                case SIZE_:
                    sarg = (intmax_t) *va_arg(vl, int *);
                    break;
                case SIZE_l:
                    sarg = (intmax_t) *va_arg(vl, long int *);
                    break;
                case SIZE_ll:
                    sarg = (intmax_t) *va_arg(vl, long long int *);
                    break;
                case SIZE_j:
                    sarg = (intmax_t) *va_arg(vl, intmax_t *);
                    break;
                case SIZE_z:
                    sarg = (intmax_t) *va_arg(vl, size_t *);
                    break;
                case SIZE_t:
                    sarg = (intmax_t) *va_arg(vl, ptrdiff_t *);
                    break;
                }
                break;
            case TYPE_s:
                string_arg = va_arg(vl, char *);
                break;
            case TYPE_PERC:
                break;
            }
            bufpos = buf;
            if (type == TYPE_s) {
                buflen = printf_strlen(string_arg);
            } else if (type & (TYPE_c | TYPE_PERC)) {
                buflen = 1;
            } else if (type == TYPE_u) {
                buflen = printf_ubuflen(uarg, 10);
            } else if (type == TYPE_p) {
                buflen = printf_ubuflen(uarg, 16) + 2;
            } else if (type == TYPE_o) {
                buflen = printf_ubuflen(uarg, 8);
                if (flags & FLAG_ALT) {
                    ++buflen;
                }
            } else if (type & (TYPE_x | TYPE_X)) {
                buflen = printf_ubuflen(uarg, 16);
                if (flags & FLAG_ALT) {
                    buflen += 2;
                }
            } else if (type == TYPE_b) {
                buflen = printf_ubuflen(uarg, 2);
                if (flags & FLAG_ALT) {
                    buflen += 2;
                }
            } else {
                buflen = printf_ibuflen(sarg, 10);
                if (sarg < 0) {
                    ++buflen;
                }
            }
            if (width > buflen) { 
                buf = kmalloc((width + 1) * sizeof(char));
            } else {
                buf = kmalloc((buflen + 1) * sizeof(char));
            }
            bufpos = buf;
            if (buflen < width) {
                bufpos += width - buflen;
            }
            for (j = buf; j < bufpos; ++j) {
                if (flags & FLAG_ZERO) {
                    *j = '0';
                } else {
                    *j = ' ';
                }
            }
            if (type & TYPE_SIGNED) {
                if (sarg < 0) {
                    *bufpos = '-';
                    ++bufpos;
                } else if (flags & FLAG_SPACE) {
                    *bufpos = ' ';
                    ++bufpos;
                } else if (flags & FLAG_SIGN) {
                    *bufpos = '+';
                    ++bufpos;
                }
            }
            if (flags & FLAG_ALT) {
                if (type == TYPE_o) {
                    *bufpos = '0';
                    ++bufpos;
                } else if (type & (TYPE_x | TYPE_X | TYPE_p)) {
                    bufpos[0] = '0';
                    bufpos[1] = 'x';
                    bufpos += 2;
                } else if (type == TYPE_b) {
                    bufpos[0] = '0';
                    bufpos[1] = 'b';
                    bufpos += 2;
                }
            }
            if (type == TYPE_s) {
                printf_strcpy(bufpos, string_arg);
            } else if (type == TYPE_c) {
                bufpos[0] = (char) uarg;
                bufpos[1] = 0;
            } else if (type == TYPE_PERC) {
                bufpos[0] = '%';
                bufpos[1] = 0;
            } else if (type == TYPE_u) {
                printf_utoa(bufpos, uarg, 10, 'a');
            } else if (type == TYPE_p) {
                printf_utoa(bufpos, uarg, 16, 'A');
            } else if (type == TYPE_o) {
                printf_utoa(bufpos, uarg, 8, 'a');
            } else if (type == TYPE_x) {
                printf_utoa(bufpos, uarg, 16, 'a');
            } else if (type == TYPE_X) {
                printf_utoa(bufpos, uarg, 16, 'A');
            } else if (type == TYPE_b) {
                printf_utoa(bufpos, uarg, 2, 'a');
            } else {
                printf_itoa(bufpos, sarg, 10, 'a');
            }
            ret += printf_strlen(buf);
            vga_puts(buf);
            kfree(buf);
        }
    }

    return ret;
}
int printf(const char *format, ...) {
    int ret;
    va_list vl;
    va_start(vl, format);
    ret = vprintf(format, vl);
    va_end(vl);
    return ret;
}
