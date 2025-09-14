#include "my_strstr.h"

int my_strstr(const char *haystack, const char *needle)
{
    if (needle && haystack)
    {
        if (needle[0] == '\0')
            return 0;
        size_t i = 0;
        for (; haystack[i]; i++)
        {
            size_t goback = i;
            size_t j = 0;
            while (needle[j] && haystack[i] == needle[j])
            {
                i++;
                j++;
            }
            if (needle[j] == '\0')
            {
                return goback;
            }
            i = goback;
        }
    }
    return -1;
}
