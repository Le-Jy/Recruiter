#include <stdio.h>

#include "bsearch.h"

int main(void)
{
    int tab[] = { 0, 1, 4, 5, 9, 10, 18, 22, 51, 69 };
    printf("%d\n", *(binary_search(tab, tab + 11, 42)));
}
