#define _POSIX_C_SOURCE 200809L

#include "field_splitting.h"

#include <string.h>

#include "variables.h"

static void add_in_fields(char ***res, size_t res_len, char *start, char *end)
{
    *res = realloc(*res, (res_len + 2) * sizeof(char *));
    if (!res)
        exit(1);
    (*res)[res_len + 1] = NULL;
    size_t field_len = end - start;
    char *cpy = calloc(field_len + 1, sizeof(char));
    strncpy(cpy, end - field_len, field_len);
    (*res)[res_len] = cpy;
}

static char *get_ifs_whitespaces(char *ifs)
{
    char *res = calloc(strlen(ifs) + 1, sizeof(char));
    if (!res)
        exit(1);

    size_t res_idx = 0;
    for (size_t i = 0; ifs[i]; i++)
    {
        if (ifs[i] == '\n' || ifs[i] == ' ' || ifs[i] == '\t')
        {
            res[res_idx++] = ifs[i];
        }
    }
    return res;
}

static void default_case(char *string, char ***res, char *ifs)
{
    size_t idx = 0;
    size_t res_len = 0;
    while (strchr(ifs, string[idx]))
        idx++;

    char *start = string + idx;
    char *end;
    while (string[idx])
    {
        if (strchr(ifs, string[idx]))
        {
            idx++;
            start = string + idx;
            continue;
        }
        while (string[idx] && !strchr(ifs, string[idx]))
        {
            if (string[idx] == '\'')
            {
                idx++;
                while (string[idx] != '\'')
                    idx++;
                idx++;
            }
            else if (string[idx] == '\"')
            {
                idx++;
                while (string[idx] != '\"')
                {
                    if (string[idx] == '\\')
                        idx++;
                    idx++;
                }
                idx++;
            }
            else if (string[idx] == '\\')
            {
                idx += 2;
            }
            else
            {
                idx++;
            }
        }
        end = string + idx;
        add_in_fields(res, res_len, start, end);
        res_len++;
        start = end + 1;
    }
}

static void apply_ifs(char *string, char ***res, char *ifs,
                      char *ifs_whitespaces)
{
    size_t idx = 0;
    size_t res_len = 0;
    while (strchr(ifs_whitespaces, string[idx]))
        idx++;

    char *start = string + idx;
    char *end;
    while (string[idx])
    {
        if (strchr(ifs_whitespaces, string[idx]))
        {
            idx++;
            start = string + idx;
            continue;
        }
        while (string[idx] && !strchr(ifs, string[idx]))
        {
            if (string[idx] == '\'')
            {
                idx++;
                while (string[idx] != '\'')
                    idx++;
                idx++;
            }
            else if (string[idx] == '\"')
            {
                idx++;
                while (string[idx] != '\"')
                {
                    if (string[idx] == '\\')
                        idx++;
                    idx++;
                }
                idx++;
            }
            else if (string[idx] == '\\')
            {
                idx += 2;
            }
            else
            {
                idx++;
            }
        }
        end = string + idx;
        add_in_fields(res, res_len, start, end);
        res_len++;
        start = end + 1;
        if (string[idx] && strchr(ifs, string[idx]))
            idx++;
    }
}

char **field_splitting(char *string)
{
    char **res = calloc(2, sizeof(char *));
    char *ifs = get_var("IFS");

    if (ifs && strlen(ifs) == 0)
    {
        res[0] = strdup(string);
        return res;
    }

    if (!ifs)
        ifs = "\n\t ";

    if ((strlen(ifs) == 3 && strchr(ifs, '\t') && strchr(ifs, '\n')
         && strchr(ifs, ' ')))
    {
        default_case(string, &res, ifs);
    }
    else
    {
        char *ifs_whitespaces = get_ifs_whitespaces(ifs);
        apply_ifs(string, &res, ifs, ifs_whitespaces);
        free(ifs_whitespaces);
    }

    return res;
}
