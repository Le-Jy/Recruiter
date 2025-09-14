#include "expand_quote.h"

#include "expand_word.h"

enum expansion_status expand_quote(char *string, size_t *idx, char **res)
{
    if (string[*idx] != '\'')
    {
        add_char_to_res(res, string[*idx]);
        (*idx)++;
        return expand_quote(string, idx, res);
    }
    else
    {
        add_char_to_res(res, string[*idx]);
        (*idx)++;
    }
    return EXPAND_OK;
}
