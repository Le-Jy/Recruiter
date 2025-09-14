#include "my_memmove.h"

void *my_memmove(void *dest, const void *src, size_t n)
{
    char *d = dest;
    const char *s = src;
    size_t i = 0;
    if (d > s + n || d + n < s)
    {
        while (i < n)
        {
            *(d + i) = *(s + i);
            i++;
        }
    }
    else if (d < s && d + n > s)
    {
        for (size_t i = 0; i < n; i++)
            *(d + i) = *(s + i);
    }
    else
    {
        for (size_t i = n - 1; i != 0; i--)
            *(d + i) = *(s + i);
        *d = *s;
    }
    return d;
}
