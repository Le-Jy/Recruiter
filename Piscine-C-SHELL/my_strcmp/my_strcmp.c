#include "my_strcmp.h"

int my_strcmp(const char *s1, const char *s2)
{
    size_t i = 0;
    for (; s1[i] != '\0' && s1[i] == s2[i]; i++)
    {
        continue;
    }
    return (s1[i] == s2[i]) ? 0 : s1[i] - s2[i];
}
