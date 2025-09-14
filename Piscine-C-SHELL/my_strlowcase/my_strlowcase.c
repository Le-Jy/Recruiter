#include "my_strlowcase.h"

void my_strlowcase(char *str)
{
    for (size_t j = 0; str[j]; j++)
    {
        if (*(str + j) >= 'A' && *(str + j) <= 'Z')
            *(str + j) += 32;
    }
}
