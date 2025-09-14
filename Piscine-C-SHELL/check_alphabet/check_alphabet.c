#include "check_alphabet.h"

int check_alphabet(const char *str, const char *alphabet)
{
    int res = 1;
    if (alphabet)
    {
        if (alphabet[0])
        {
            size_t i = 0;
            for (; alphabet[i] && res; i++)
            {
                size_t j = 0;
                res = 0;
                while (str[j] && !res)
                {
                    if (str[j] == alphabet[i])
                    {
                        res = 1;
                    }
                    j++;
                }
            }
        }
    }
    return res;
}
