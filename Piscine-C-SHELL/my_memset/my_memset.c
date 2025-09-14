#include "my_memset.h"

void *my_memset(void *s, int c, size_t n)
{
    char *s_convert = s;
    for (size_t i = 0; i < n; i++)
        *(s_convert + i) = c;
    return s_convert;
}
