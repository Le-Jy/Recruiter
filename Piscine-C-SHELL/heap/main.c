#include <stdio.h>

#include "heap.h"

int main(void)
{
    struct heap *heap = create_heap();
    add(heap, 10);
    add(heap, 6);
    add(heap, 8);
    add(heap, 1);
    add(heap, 4);
    add(heap, 3);
    print_heap(heap);
    pop(heap);
    print_heap(heap);
    delete_heap(heap);
}
