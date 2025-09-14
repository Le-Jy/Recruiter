#include <stddef.h>

char *my_strcpy(char *dest, const char *source)
{
    size_t i = 0;
    for (; source[i]; i++)
    {
        dest[i] = source[i];
    }
    dest[i] = '\0';
    return dest;
}
