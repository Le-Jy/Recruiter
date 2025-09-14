#include "string_arrays.h"

#include <stdlib.h>
#include <string.h>

char **copy_value(char **value)
{
    if (!value)
        return NULL;
    size_t size = 0;
    while (value[size])
        size++;

    char **cpy = calloc(size + 1, sizeof(char *));
    if (!cpy)
        exit(1);

    for (size_t i = 0; i < size; i++)
    {
        cpy[i] = malloc((strlen(value[i]) + 1) * sizeof(char));
        if (!cpy[i])
            exit(1);
        strcpy(cpy[i], value[i]);
    }
    cpy[size] = NULL;

    return cpy;
}

void free_value(char **value)
{
    if (!value)
        return;
    size_t i = 0;
    while (value[i])
    {
        free(value[i]);
        i++;
    }
    free(value);
}
