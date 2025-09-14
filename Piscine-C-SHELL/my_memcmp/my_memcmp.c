#include "my_memcmp.h"

int my_memcmp(const void *s1, const void *s2, size_t num)
{
    if (!num)
        return 0;
    size_t i = 0;
    const unsigned char *s1_convert = s1;
    const unsigned char *s2_convert = s2;
    while (i < num && *(s1_convert + i) == *(s2_convert + i))
    {
        i++;
    }
    return (i == num) ? 0 : *(s1_convert + i) - *(s2_convert + i);
}
