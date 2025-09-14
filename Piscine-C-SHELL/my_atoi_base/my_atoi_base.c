#include "my_atoi_base.h"

int is_in_base(char c, const char *base)
{
    int i = 0;
    for (; base[i]; i++)
    {
        if (c == base[i])
            break;
    }
    return (base[i] == '\0') ? -1 : i;
}

int my_atoi_base(const char *str, const char *base)
{
    int len = 0;
    for (size_t k = 0; base[k]; k++)
        len++;
    int lenstr = 0;
    for (size_t k = 0; str[k]; k++)
        lenstr++;

    int num = 0;
    int i = 0;
    int neg = 0;
    while (str[i] == ' ' || str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-' || str[i] == '+')
        {
            if (str[i] == '-')
            {
                neg = 1;
            }
            i++;
            break;
        }
        i++;
    }
    int iib = is_in_base(str[i], base);
    while (str[i] && iib >= 0)
    {
        int lenpow = 1;
        for (int l = 0; l < lenstr - i - 1; l++)
            lenpow *= len;
        num += lenpow * iib;
        i++;
        iib = is_in_base(str[i], base);
    }
    if (str[i] != '\0')
        return 0;
    return (neg) ? num * -1 : num;
}
