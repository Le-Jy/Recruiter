#include "expand_double_quotes.h"

#include <stdbool.h>

#include "expand_backslash.h"
#include "expand_variable.h"
#include "expansion.h"

enum expansion_status expand_double_quotes(char *string, size_t *idx,
                                           char **res)
{
    if (string[*idx] == '\"')
    {
        add_char_to_res(res, string[*idx]);
        (*idx)++;
    }
    else
    {
        if (string[*idx] == '\\')
        {
            if (expand_backslash(string, idx, res) == EXPAND_ERROR)
                return EXPAND_ERROR;
        }
        else if (string[*idx] == '$')
        {
            (*idx)++;
            if (expand_variable(string, idx, res) == EXPAND_ERROR)
                return EXPAND_ERROR;
        }
        else
        {
            add_char_to_res(res, string[*idx]);
            (*idx)++;
        }

        return expand_double_quotes(string, idx, res);
    }
    return EXPAND_OK;
}
