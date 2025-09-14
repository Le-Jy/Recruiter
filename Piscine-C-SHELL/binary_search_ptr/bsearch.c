#include "bsearch.h"

int *binary_search(int *begin, int *end, int elt)
{
    if (begin != end)
    {
        while (begin <= end)
        {
            int *pivot = begin + (end - begin) / 2;
            if (*pivot == elt)
                return pivot;
            if (*pivot < elt)
                begin = pivot + 1;
            else
                end = pivot - 1;
        }
    }
    return begin;
}
