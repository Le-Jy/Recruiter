#include "expand_backslash.h"

enum expansion_status expand_backslash(char *string, size_t *idx, char **res)
{
    add_char_to_res(res, string[*idx]);
    (*idx)++;

    add_char_to_res(res, string[*idx]);
    (*idx)++;
    return EXPAND_OK;
}
