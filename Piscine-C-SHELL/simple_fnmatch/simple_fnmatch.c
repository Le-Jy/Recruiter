#include "simple_fnmatch.h"

int simple_fnmatch(const char *pattern, const char *string)
{
    while (*string)
    {
        if (*pattern == '\\')
        {
            if (*(pattern + 1) == *(string))
            {
                pattern += 2;
                string++;
            }
            else
                return FNM_NOMATCH;
        }
        else if (*pattern == '*')
        {
            while (*pattern == '*')
                pattern++;
            if (*pattern == '\0')
                return 0;
            while (*string)
            {
                int res = simple_fnmatch(pattern, string);
                if (!res)
                    return 0;
                string++;
            }
            return FNM_NOMATCH;
        }
        else if (*pattern == '?' || *pattern == *string)
        {
            string++;
            pattern++;
        }
        else
            return FNM_NOMATCH;
    }
    while (*pattern == '*')
        pattern++;
    if (*string == '\0' && *pattern == '\0')
        return 0;
    return FNM_NOMATCH;
}
