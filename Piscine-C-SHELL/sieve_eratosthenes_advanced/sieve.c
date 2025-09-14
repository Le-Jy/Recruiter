#include <stdio.h>
#include <stdlib.h>

void sieve(int n)
{
    if (n < 2)
        return;
    int *prime = calloc(n, sizeof(int));
    for (int p = 2; p * p <= n - 1; p++)
    {
        if (!prime[p])
        {
            for (int i = p * p; i <= n - 1; i += p)
                prime[i] = 1;
        }
    }
    int sum = 0;
    for (int j = 2; j < n; j++)
    {
        if (!prime[j])
            sum++;
    }
    if (sum)
        printf("%d\n", sum);
    free(prime);
}
