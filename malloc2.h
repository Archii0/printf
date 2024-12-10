#include <unistd.h>

#define malloc2(x)                                                             \
    sbrk(x);                                                                   \
    _alloc += x;
#define freeall()                                                              \
    sbrk(-_alloc);                                                             \
    _alloc = 0;

unsigned int _alloc;
