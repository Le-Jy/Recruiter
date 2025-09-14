#include "str_revert.h"

void str_revert(char str[])
{
    size_t i = 0;
    for (; str[i]; i++)
    {
        continue;
    }
    if (i <= 1)
        return;
    i--;
    size_t j = 0;
    for (; i >= j; i--, j++)
    {
        char tmp = str[i];
        str[i] = str[j];
        str[j] = tmp;
    }
}
