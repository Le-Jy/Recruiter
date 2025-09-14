#include "my_strlen.h"

size_t my_strlen(const char *s)
{
    size_t i = 0;
    while (s[i])
        i++;
    return i;
}
