#include "palindrome.h"

#include <stddef.h>

int is_alpha_numeric(char c)
{
    int maj = (c <= 57 && c >= 48);
    int min = (c >= 65 && c <= 90);
    int oth = (c >= 97 && c <= 122);
    return (maj || min || oth);
}

int palindrome(const char *s)
{
    if (!s)
        return 0;
    int res = 0;
    size_t i = 0;
    for (; s[i]; i++)
    {
        continue;
    }
    if (i <= 1)
        return 1;
    i--;
    size_t j = 0;
    for (; j <= i; i--, j++)
    {
        while (i > 0 && !is_alpha_numeric(s[i]))
        {
            i--;
        }
        while (s[j + 1] && !is_alpha_numeric(s[j]))
        {
            j++;
        }
        if (s[j] != s[i])
            break;
    }
    if (j >= i)
        res = 1;
    return res;
}
