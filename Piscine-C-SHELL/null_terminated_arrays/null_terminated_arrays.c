#include "null_terminated_arrays.h"

#include <stddef.h>
#include <stdio.h>

static size_t get_len_big_matrix(const char ***matrix)
{
    size_t len_matrix = 0;
    while (matrix[len_matrix] != NULL)
        len_matrix++;
    return len_matrix;
}

static size_t get_len_smaller_matrix(const char **matrix)
{
    size_t len_tab_of_string = 0;
    while (matrix[len_tab_of_string] != NULL)
        len_tab_of_string++;
    return len_tab_of_string;
}

static void reverse_string_tab(const char **matrix)
{
    size_t len_tab = get_len_smaller_matrix(matrix);
    for (size_t i = 0; i < len_tab / 2; i++)
    {
        const char *tmp = matrix[i];
        matrix[i] = matrix[len_tab - i - 1];
        matrix[len_tab - i - 1] = tmp;
    }
}

void reverse_matrix(const char ***matrix)
{
    size_t len_matrix = get_len_big_matrix(matrix);
    for (size_t i = 0; i < len_matrix / 2; i++)
    {
        const char **tmp = matrix[i];
        matrix[i] = matrix[len_matrix - i - 1];
        matrix[len_matrix - i - 1] = tmp;
    }
    for (size_t l = 0; l < len_matrix; l++)
    {
        reverse_string_tab(matrix[l]);
    }
}
