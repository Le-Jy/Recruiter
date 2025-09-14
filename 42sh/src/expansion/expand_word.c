#include "expand_word.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "../utils/string_arrays/string_arrays.h"
#include "expand_backslash.h"
#include "expand_double_quotes.h"
#include "expand_quote.h"
#include "expand_variable.h"
#include "expansion.h"
#include "field_splitting.h"
#include "quote_removal.h"

void add_char_to_res(char **res, char c)
{
    *res = realloc(*res, strlen(*res) + 2);
    if (!(*res))
        exit(1);
    char end[2] = { c, '\0' };
    strcat(*res, end);
}

enum expansion_status substitution(char *string, size_t *idx, char **res)
{
    char c = string[*idx];
    if (c == '\'')
    {
        add_char_to_res(res, string[(*idx)++]);
        if (expand_quote(string, idx, res) == EXPAND_ERROR)
            return EXPAND_ERROR;
    }
    else if (c == '\"')
    {
        add_char_to_res(res, string[(*idx)++]);
        if (expand_double_quotes(string, idx, res) == EXPAND_ERROR)
            return EXPAND_ERROR;
    }
    else if (c == '\\')
        expand_backslash(string, idx, res);
    else if (c == '$' || c == '`')
    {
        if (c == '$')
            (*idx)++;
        size_t before = *idx;
        if (expand_variable(string, idx, res) == EXPAND_ERROR)
            return EXPAND_ERROR;
        if (*idx == before)
            add_char_to_res(res, c);
    }
    else
    {
        add_char_to_res(res, c);
        (*idx)++;
    }

    if (c != '\0')
        return substitution(string, idx, res);
    return EXPAND_OK;
}

static char *prepare_string(char **fields)
{
    char *res = calloc(1, sizeof(char));
    char space[2] = { ' ', '\0' };
    for (size_t i = 0; fields[i]; i++)
    {
        res =
            realloc(res, (strlen(res) + strlen(fields[i]) + 2) * sizeof(char));
        if (!res)
            exit(1);
        strcat(res, fields[i]);
        strcat(res, space);
    }
    size_t len = strlen(res);
    res[len - 1] = '\0';
    return res;
}

enum expansion_status expand_word(char *string, char **res)
{
    size_t expand_idx = 0;
    if (substitution(string, &expand_idx, res) != EXPAND_OK)
        return EXPAND_ERROR;

    if (strlen(*res) == 0)
    {
        free(*res);
        *res = NULL;
        return EXPAND_OK;
    }

    char **fields = field_splitting(*res);

    for (size_t i = 0; fields[i]; i++)
    {
        size_t remove_idx = 0;
        quotes_removal(fields[i], &remove_idx);
    }

    free(*res);

    *res = prepare_string(fields);

    free_value(fields);

    return EXPAND_OK;
}
