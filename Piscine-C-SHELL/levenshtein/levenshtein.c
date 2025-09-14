#include "levenshtein.h"

size_t min(size_t i1, size_t i2)
{
    return (i1 > i2) ? i2 : i1;
}

size_t max(size_t i1, size_t i2)
{
    return (i1 > i2) ? i1 : i2;
}

size_t len(const char *s)
{
    size_t len = 0;
    while (s[len])
        len++;
    return len;
}

size_t rec(const char *s1, const char *s2, size_t ind1, size_t ind2)
{
    if (min(ind1, ind2) == 0)
        return max(ind1, ind2);
    size_t first = rec(s1, s2, ind1 - 1, ind2) + 1;
    size_t second = rec(s1, s2, ind1, ind2 - 1) + 1;
    size_t third = rec(s1, s2, ind1 - 1, ind2 - 1);
    if (s1[ind1 - 1] != s2[ind2 - 1])
        third++;
    return min(min(first, second), third);
}

size_t levenshtein(const char *s1, const char *s2)
{
    size_t len1 = len(s1);
    size_t len2 = len(s2);
    return rec(s1, s2, len1, len2);
}
