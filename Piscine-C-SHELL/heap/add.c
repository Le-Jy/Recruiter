#include <stdlib.h>

#include "heap.h"

void add(struct heap *heap, int val)
{
    if (!heap)
        return;
    if (heap->capacity == heap->size)
    {
        int *arr = realloc(heap->array, 2 * heap->capacity * sizeof(int));
        if (!arr)
            return;
        heap->array = arr;
        heap->capacity *= 2;
    }
    heap->array[heap->size] = val;
    size_t val_index = heap->size;
    size_t father_index = (val_index - 1) / 2;
    while (val_index != 0 && heap->array[father_index] < val)
    {
        int tmp = heap->array[father_index];
        heap->array[father_index] = val;
        heap->array[val_index] = tmp;
        val_index = father_index;
        father_index = (val_index - 1) / 2;
    }
    heap->size++;
}
