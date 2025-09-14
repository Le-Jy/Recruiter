#include <stdio.h>

#include "my_itoa_base.h"

int main(void)
{
    char s[2];
    printf("%s\n", my_itoa_base(0, s, "0123456789ABCDEF"));
}
