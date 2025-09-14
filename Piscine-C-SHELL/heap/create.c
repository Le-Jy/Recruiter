#include <stdlib.h>

#include "heap.h"

struct heap *create_heap(void)
{
    struct heap *h = malloc(sizeof(struct heap));

    h->size = 0;
    h->capacity = 8;
    h->array = malloc(8 * sizeof(int));
    return h;
}
