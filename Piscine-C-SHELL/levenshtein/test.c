#include <stdio.h>

#include "levenshtein.h"

int main(void)
{
    printf("%zu\n", levenshtein("doom", "tools"));
}
