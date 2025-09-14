#include "bubble_sort.h"

#include <stdio.h>

void bubble_sort(int array[], size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size - i - 1; j++)
        {
            if (array[j] > array[j + 1])
            {
                int tmp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = tmp;
            }
        }
    }
}

int main(void)
{
    int arr[] = { 11, 10, 12, 16 };
    bubble_sort(arr, 4);
    for (size_t i = 0; i < 4; i++)
        printf("%d\n", arr[i]);
}
