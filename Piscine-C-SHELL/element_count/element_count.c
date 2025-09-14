#include "element_count.h"

size_t element_count(int *begin, int *end)
{
    size_t res = 0;
    if (begin != NULL && end != NULL)
    {
        for (; begin != end; begin++)
        {
            res++;
        }
    }
    return res;
}
