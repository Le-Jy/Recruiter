#include "my_calloc.h"

void *my_calloc(size_t n, size_t size)
{
    char *pt = malloc(n * size);
    if (pt)
    {
        for (size_t i = 0; i < n * size; i++)
            pt[i] = 0;
    }
    return pt;
}
