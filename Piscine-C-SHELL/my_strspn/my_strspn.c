#include "my_strspn.h"

int check_char(const char c, const char *accept)
{
    int res = -1;
    for (int i = 0; res == -1 && accept[i]; i++)
    {
        if (c == accept[i])
        {
            res = i;
        }
    }
    return res;
}

size_t my_strspn(const char *s, const char *accept)
{
    if (s && accept)
    {
        if (!s[0] || !accept[0])
            return 0;
        size_t res = 0;
        size_t i = 0;
        while (s[i] && check_char(s[i], accept) != -1)
        {
            i++;
            res++;
        }
        return res;
    }
    return 0;
}
