#include <stddef.h>

void rot_x(char *s, int x)
{
    if (s)
    {
        size_t i = 0;
        while (s[i])
        {
            if (s[i] >= 'A' && s[i] <= 'Z')
            {
                s[i] = (s[i] - 'A' + x + 26) % 26 + 'A';
            }
            else if (s[i] >= 'a' && s[i] <= 'z')
            {
                s[i] = (s[i] - 'a' + x + 26) % 26 + 'a';
            }
            i++;
        }
    }
}
