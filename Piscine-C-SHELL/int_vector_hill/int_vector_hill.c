#include "int_vector_hill.h"

int int_vector_hill(struct int_vector vec)
{
    if (vec.size == 1)
        return 0;
    if (vec.size)
    {
        size_t left = 0;
        size_t right = vec.size - 1;
        while (left < vec.size - 1 && vec.data[left] <= vec.data[left + 1])
        {
            if (vec.data[left] < 0)
                return -1;
            left++;
        }
        while (vec.data[right - 1] >= vec.data[right])
        {
            if (vec.data[right] < 0)
                return -1;
            right--;
        }
        if (vec.data[left] == vec.data[right] && left >= right)
            return right;
    }
    return -1;
}
