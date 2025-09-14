#include "my_memcpy.h"

void *my_memcpy(void *dest, const void *source, size_t num)
{
    char *dest_convert = dest;
    const char *source_convert = source;
    for (size_t i = 0; i < num; i++)
        *(dest_convert + i) = *(source_convert + i);
    return dest_convert;
}
