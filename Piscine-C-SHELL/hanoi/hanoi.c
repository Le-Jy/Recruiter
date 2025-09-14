#include <stdio.h>

void help_hanoi(unsigned n, int from, int to, int aux)
{
    if (n == 1)
    {
        printf("%d->%d\n", from, to);
        return;
    }
    help_hanoi(n - 1, from, aux, to);
    printf("%d->%d\n", from, to);
    help_hanoi(n - 1, aux, to, from);
}

void hanoi(unsigned n)
{
    help_hanoi(n, 1, 3, 2);
}
