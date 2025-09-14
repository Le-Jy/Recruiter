#include "hill_array.h"

int top_of_the_hill(int tab[], size_t len)
{
    if (len == 1)
        return 0;
    if (len)
    {
        size_t left = 0;
        size_t right = len - 1;
        while (left < len - 1 && tab[left] <= tab[left + 1])
        {
            if (tab[left] < 0)
                return -1;
            left++;
        }
        while (tab[right - 1] >= tab[right])
        {
            if (tab[right] < 0)
                return -1;
            right--;
        }
        if (tab[left] == tab[right] && left >= right)
            return right;
    }
    return -1;
}
