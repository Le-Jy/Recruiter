#include <stdio.h>

#include "my_atoi_base.h"

int main(void)
{
    printf("%d\n", my_atoi_base("           ff", "0123456789abcdef"));
    printf("%d\n", my_atoi_base("-+-+-+-+-ff", "0123456789abcdef"));
    printf("%d\n", my_atoi_base("+ 77", "01234567"));
    printf("%d\n", my_atoi_base("WQWW", "QW"));
}
