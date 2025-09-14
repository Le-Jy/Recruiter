#include "insertion_sort.h"

void insertion_sort(void **array, f_cmp comp)
{
    if (!array || !array[0])
        return;
    for (int i = 1; array[i]; i++)
    {
        void *x = array[i];
        int j = i - 1;
        while (j >= 0 && comp(array[j], x) > 0)
        {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = x;
    }
}
