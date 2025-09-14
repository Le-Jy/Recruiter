#include "quote_removal.h"

#include <stdbool.h>
#include <string.h>

void remove_idx(char *string, size_t idx)
{
    size_t len = strlen(string);

    if (idx >= len)
        return;

    for (size_t i = idx; i < len - 1; i++)
        string[i] = string[i + 1];

    string[len - 1] = '\0';
}

void remove_quote(char *string, size_t *idx)
{
    if (string[*idx] != '\'')
    {
        (*idx)++;
        remove_quote(string, idx);
    }
    else
    {
        remove_idx(string, *idx);
    }
}

static bool isspecial(char c)
{
    return (c == '$' || c == '\"' || c == '\\');
}

void remove_backslash(char *string, size_t *idx, bool dquoted)
{
    if (isspecial(string[(*idx) + 1]) || !dquoted)
    {
        remove_idx(string, *idx);
    }

    (*idx)++;
}

void remove_double_quotes(char *string, size_t *idx)
{
    if (string[*idx] == '\"')
    {
        remove_idx(string, *idx);
    }
    else
    {
        if (string[*idx] == '\\')
            remove_backslash(string, idx, true);
        else
            (*idx)++;

        remove_double_quotes(string, idx);
    }
}

void quotes_removal(char *string, size_t *idx)
{
    char c = string[*idx];
    if (c == '\'')
    {
        remove_idx(string, *idx);
        remove_quote(string, idx);
    }
    else if (c == '\"')
    {
        remove_idx(string, *idx);
        remove_double_quotes(string, idx);
    }
    else if (c == '\\')
        remove_backslash(string, idx, false);
    else
        (*idx)++;

    if (c != '\0')
        quotes_removal(string, idx);
}
