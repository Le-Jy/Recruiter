#include "functional_programming.h"

int foldr(int *array, size_t len, int (*func)(int, int))
{
    int res = 0;
    for (size_t i = len - 1; i != 0; i--)
    {
        res = func(array[i], res);
    }
    return func(array[0], res);
}
