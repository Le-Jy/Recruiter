#include <stdio.h>

#include "int_vector_vice_max.h"

int main(void)
{
    const struct int_vector v = { 5, { -1, -7, -32, -24, -12 } };
    printf("%d\n", int_vector_vice_max(v));
}
