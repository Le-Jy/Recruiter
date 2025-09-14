#include <stdio.h>

#include "my_memcmp.h"

int main(void)
{
    int s1 = 123456789;
    int s2 = 123456788;
    printf("%d\n", my_memcmp(&s1, &s2, 9));
}
