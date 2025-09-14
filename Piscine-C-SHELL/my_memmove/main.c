#include <stdio.h>
#include <stdlib.h>

#include "my_memmove.h"

int main(void)
{
    char *dest = malloc(26);
    const char *src = dest + 5;
    src = "Coucou";
    char *res = my_memmove(dest, src, 6);
    printf("%s\n", res);
}
