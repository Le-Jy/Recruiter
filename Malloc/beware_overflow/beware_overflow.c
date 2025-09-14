#include "beware_overflow.h"

void *beware_overflow(void *ptr, size_t nmemb, size_t size)
{
    char *res = ptr;
    size_t tmp = 0;
    if (__builtin_umull_overflow(nmemb, size, &tmp))
        return NULL;
    res = res + (nmemb * size);
    return res;
}
