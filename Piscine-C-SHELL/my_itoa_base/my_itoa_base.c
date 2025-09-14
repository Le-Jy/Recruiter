#include "my_itoa_base.h"

void invert_string(char *s)
{
    size_t len = 0;
    while (s[len])
        len++;
    size_t j = len - 1;
    for (size_t i = 0; i < j; i++, j--)
    {
        char tmp = s[i];
        s[i] = s[j];
        s[j] = tmp;
    }
}

char *my_itoa_base(int n, char *s, const char *base)
{
    int len = 0;
    int sign = 0;
    int i = 0;
    for (size_t k = 0; base[k]; k++)
        len++;
    if (n < 0)
    {
        n = -n;
        sign = 1;
    }
    do
    {
        s[i] = base[(n % len)];
        n /= len;
        i++;
    } while (n != 0);
    if (sign)
    {
        s[i] = '-';
        i++;
    }
    s[i] = '\0';

    invert_string(s);
    return s;
}
