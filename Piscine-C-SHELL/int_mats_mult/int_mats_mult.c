#include "int_mats_mult.h"

void mat_mult(int **mat1, int **mat2, size_t *matrices_size, int **out)
{
    for (size_t i = 0; i < matrices_size[0]; i++)
    {
        for (size_t j = 0; j < matrices_size[1]; j++)
        {
            for (size_t k = 0; k < matrices_size[2]; k++)
            {
                out[i][k] += mat1[i][j] * mat2[j][k];
            }
        }
    }
}
