#include <stdio.h>
#include <stdlib.h>

#include "my_strtok_r.h"

int main()
{
    char str[] = "      foo   test  ";
    char *rest;
    printf("%s\n", my_strtok_r(str, " ", &rest));
    printf("%s\n", my_strtok_r(NULL, " ", &rest));
}
