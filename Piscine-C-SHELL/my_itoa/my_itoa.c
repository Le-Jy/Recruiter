#include "my_itoa.h"

char *my_itoa(int value, char *s)
{
    int tmp = value;
    int nb_digits = 1;
    int end = 0;

    for (; tmp > 9 || tmp < -9; nb_digits++)
    {
        tmp /= 10;
    }
    if (value < 0)
    {
        s[0] = '-';
        s[nb_digits + 1] = '\0';
        end = 1;
        value = value * -1;
    }
    else
    {
        s[nb_digits] = '\0';
        nb_digits--;
    }
    for (; nb_digits >= end; nb_digits--)
    {
        s[nb_digits] = (value % 10) + '0';
        value /= 10;
    }
    return s;
}
