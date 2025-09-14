#include <assert.h>
#include <stdlib.h>

#include "heap.h"

static size_t max(struct heap *heap, size_t i1, size_t i2)
{
    return (heap->array[i1] < heap->array[i2]) ? i2 : i1;
}

static int is_smaller(struct heap *heap, int i)
{
    int to_comp = heap->array[i];
    if (to_comp < heap->array[i * 2 + 1] || to_comp < heap->array[2 * i + 2])
        return 1;
    return 0;
}

static void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int pop(struct heap *heap)
{
    assert(heap && heap->size > 0);

    int root = heap->array[0];
    swap(&heap->array[0], &heap->array[heap->size - 1]);
    heap->size--;
    if (heap->size < heap->capacity / 2)
    {
        int *arr = NULL;
        if (heap->capacity / 2 < 8)
        {
            arr = realloc(heap->array, 8 * sizeof(int));
            assert(arr);

            heap->capacity = 8;
        }
        else
        {
            arr = realloc(heap->array, (heap->capacity / 2) * sizeof(int));
            assert(arr);

            heap->capacity /= 2;
        }
        heap->array = arr;
    }
    size_t move_index = 0;
    while (move_index * 2 + 2 < heap->size && is_smaller(heap, move_index))
    {
        size_t tmp = max(heap, 2 * move_index + 1, 2 * move_index + 2);
        swap(&heap->array[tmp], &heap->array[move_index]);
        move_index = tmp;
    }

    return root;
}
