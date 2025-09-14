#include "alignment.h"

size_t align(size_t size)
{
    size_t c = 0;
    size_t check = 0;
    while ((size + c) % sizeof(long double) != 0)
    {
        c++;
        if (__builtin_umull_overflow(size, c, &check))
            return 0;
    }
    return size + c;
}
