#include <stdio.h>

#include "my_strspn.h"

int main(void)
{
    printf("%zu\n", my_strspn("cabbage", "abc"));
    printf("%zu\n", my_strspn("abcd", ""));
    printf("%zu\n", my_strspn("abcd", "ABCD"));
}
