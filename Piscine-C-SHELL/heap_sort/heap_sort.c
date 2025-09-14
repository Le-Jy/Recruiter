#include "heap_sort.h"

static void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

static void max_heapify(int *array, size_t size, size_t i)
{
    size_t largest = i;
    size_t left = 2 * i + 1;
    size_t right = 2 * i + 2;
    if (left < size && array[left] > array[largest])
        largest = left;
    if (right < size && array[right] > array[largest])
        largest = right;
    if (largest != i)
    {
        swap(&array[i], &array[largest]);
        max_heapify(array, size, largest);
    }
}

void heapify(int *array, size_t size)
{
    for (size_t i = size / 2 - 1; i < size; i--)
        max_heapify(array, size, i);
}

void heap_sort(int *array, size_t size)
{
    heapify(array, size);
    for (size_t i = size - 1; i < size; i--)
    {
        swap(&array[0], &array[i]);
        max_heapify(array, i, 0);
    }
}
