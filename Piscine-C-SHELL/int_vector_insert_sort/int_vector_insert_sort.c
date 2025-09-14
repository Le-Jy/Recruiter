#include "int_vector_insert_sort.h"

struct int_vector int_vector_insert_sort(struct int_vector vec)
{
    for (size_t i = 1; i < vec.size; i++)
    {
        int k = vec.data[i];
        int j = i - 1;
        while (j >= 0 && vec.data[j] > k)
        {
            vec.data[j + 1] = vec.data[j];
            j--;
        }
        vec.data[j + 1] = k;
    }
    return vec;
}
