#include "my_strtok_r.h"

char *my_strtok_r(char *str, const char *delim, char **saveptr)
{
    if (str == NULL)
        str = *(saveptr);
    if (*str == '\0')
        return NULL;
    int j = 0;
    while (str[j])
    {
        int dl = 0;
        for (size_t i = 0; delim[i] && !dl; i++)
        {
            if (str[j] == delim[i])
                dl = 1;
        }
        if (!dl)
        {
            j++;
            if (str[j] == '\0')
                *saveptr = "\0";
        }
        else
        {
            int tmp = j;
            while (dl && str[tmp])
            {
                size_t i = 0;
                for (; delim[i]; i++)
                {
                    if (str[tmp] == delim[i])
                        break;
                }
                if (delim[i])
                {
                    tmp++;
                }
                else
                    dl = 0;
            }
            *(saveptr) = str + tmp;
            if (j == 0)
                return my_strtok_r(NULL, delim, saveptr);
            str[j] = '\0';
        }
    }
    return str;
}
