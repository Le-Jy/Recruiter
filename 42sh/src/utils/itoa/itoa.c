#include "itoa.h"

void strrevert(char *str)
{
    int len = 0;
    while (str[len] != '\0')
    {
        len++;
    }

    int i = len - 1;
    for (int j = 0; j < len / 2; j++)
    {
        char tmp = str[j];
        str[j] = str[i];
        str[i] = tmp;
        i--;
    }
}

char *itoa(int value, char *s)
{
    int i = 0;
    int neg = 0;
    if (value < 0)
    {
        neg = 1;
        value = -value;
    }
    if (value == 0)
    {
        s[i] = '0';
        i++;
    }
    while (value > 0)
    {
        s[i] = value % 10 + '0';
        value /= 10;
        i++;
    }
    if (neg)
    {
        s[i] = '-';
        i++;
    }
    s[i] = '\0';
    strrevert(s);
    return s;
}
