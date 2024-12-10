# printf
Recreating printf for fun
It supports:
- %s (string)
- %c (char)
- %d (integer)

Created using system calls, and only 1 library for variadic argument parsing.
Created a naive malloc method by moving the boundary between the stack and the heap using a system call.

Variadic parsing in x86 is simple, as arguments are placed on the stack:
```C
#define Args(p)                                      \
    __asm("movq %%rdi, %0" : "=r"(p));              \
    unsigned long *_stack_args;                     \
    __asm("movq %%rbp, %0" : "=r"(_stack_args));     \
    _stack_args = (unsigned long *)(_stack_args + 2); \
    p = (unsigned long *)_stack_args
```
But for 86_64 it is more complex, using six different registers for the first 6 arguments. This makes the implementation less nice, as it would require some context about which argument number it is.
