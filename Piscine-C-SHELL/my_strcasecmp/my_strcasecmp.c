#include "my_strcasecmp.h"

#include <stddef.h>

char to_low_case(char c1)
{
    return (c1 >= 'A' && c1 <= 'Z') ? c1 += 32 : c1;
}

int my_strcasecmp(const char *s1, const char *s2)
{
    size_t i = 0;
    int same = 0;
    for (; s1[i] != '\0'; i++)
    {
        char c1 = to_low_case(s1[i]);
        char c2 = to_low_case(s2[i]);

        if (c1 != c2)
        {
            same = c1 - c2;
            break;
        }
    }
    if (s1[i] == '\0' && s2[i] != '\0')
        same = s1[i] - s2[i];
    else if (s1[i] != '\0' && s2[i] == '\0')
        same = s1[i] - s2[i];
    return same;
}
