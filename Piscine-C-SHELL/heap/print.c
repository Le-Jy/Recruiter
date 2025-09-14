#include <stdio.h>

#include "heap.h"

void dfs_rec_prefix(const struct heap *heap, size_t index)
{
    printf("%d", heap->array[index]);

    if (2 * index + 1 < heap->size)
    {
        printf(" ");
        dfs_rec_prefix(heap, 2 * index + 1);
    }
    if (2 * index + 2 < heap->size)
    {
        printf(" ");
        dfs_rec_prefix(heap, 2 * index + 2);
    }
    return;
}

void print_heap(const struct heap *heap)
{
    if (heap)
    {
        size_t index = 0;
        dfs_rec_prefix(heap, index);
        printf("\n");
    }
}
