#include <stdio.h>

#include "heap_sort.h"

int main(void)
{
    int a[] = { 6, 5, 4, 3, 2, 1 };
    int a2[] = { 3, 8, 6, 9, 7 };
    heapify(a, 6);
    heap_sort(a2, 5);
    for (size_t i = 0; i < 6; i++)
        printf("%d ", a[i]);
    printf("\n");
    for (size_t i = 0; i < 5; i++)
        printf("%d ", a2[i]);
    printf("\n");
}
