#include <stdio.h>

#include "functional_programming.h"

int sum(int a, int b)
{
    return a + b;
}

int main(void)
{
    int arr[] = { 1, 2, 3 };
    int r = foldl(arr, 3, sum);
    printf("%d\n", r);
}
