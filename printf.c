#include "malloc2.h"
#include <stdarg.h>

#define putchar2(x) write(1, chardup2(x), 1)
#define swapchar(x) (x + 0x30)

#define Wait4char 1 // 00 01
#define Wait4fmt 2  // 00 10

typedef unsigned char State;

// Create a buffer of the char
char *chardup2(const char c) {
    static char buf[2];
    char *p;

    p = buf;
    *p++ = c;
    *p-- = 0;

    return buf;
}

unsigned int strlen2(const char *str) {
    unsigned int n;
    const char *p;

    for (p = str, n = 0; *p; ++p, ++n)
        ;

    return n;
}

int puts2(const char *str) {
    const unsigned int n = strlen2(str);

    if (n < 1)
        return -1;

    // 0 is stdin, 1 is stdout, 2 is stderr
    return write(1, str, n);
}

char *itoa2(int n) {
    unsigned int x, y;
    unsigned char *xs, *p;
    static char ret[10];

    y = n;
    xs = malloc2(10);
    p = xs;

    while (y > 9) {
        x = y;
        y = x / 10;
        *xs++ = x % 10;
    }

    *xs = y;

    for (x = 0; xs > p; ++x, --xs) {
        ret[x] = swapchar(*xs);
    }
    ret[x] = swapchar(*xs);
    ret[++x] = 0;

    freeall();

    return ret;
}

int printf2(const char *fmt, ...) {
    // unsigned int *p;
    unsigned char c; // the char we
    const char *f;   // pointer to format strig
    State s;

    va_list args;
    va_start(args, fmt);

    s = Wait4char;
    f = fmt;

    do {
        if (s & Wait4char)
            switch (*f) {
            case '%':
                s = Wait4fmt;
                break;

            default:
                putchar2(*f);
                break;
            }
        else if (s & Wait4fmt)
            switch (*f) {
            case '%':
                putchar2(*f);
                s = Wait4char;
                break;

            case 's':
                char *str = va_arg(args, char *);
                puts2(str);
                s = Wait4char;
                break;
            case 'c':
                char c = (char)va_arg(args, int);
                putchar2(c);
                s = Wait4char;
                break;
            case 'd':
                int x = va_arg(args, int);
                puts2(itoa2(x));
                s = Wait4char;
                break;
            default:
                s = Wait4char;
                va_arg(args, void *); // Skip the argument by consuming it
                break;
            }
    } while (*(++f));

    va_end(args);
    return 0;
}

int main() {
    char c;
    char *p;

    p = "Archie";
    c = 'x';
    printf2("Hello %d and %s abc\n", 500, p);
    return 0;
}