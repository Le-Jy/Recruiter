#define _POSIX_C_SOURCE 200809L

#include "variables.h"

#include <stdlib.h>
#include <string.h>

#include "expand_word.h"
#include "quote_removal.h"

extern struct expansion *expansion;

void add_special_var(struct special_var *current_var)
{
    if (!current_var)
        return;
    expansion->special_vars = list_prepend(expansion->special_vars, current_var,
                                           sizeof(struct special_var));
    if (!expansion->special_vars)
        exit(1);

    struct special_var *new_var = expansion->special_vars->data;

    new_var->key = strdup(current_var->key);
    if (current_var->value)
        new_var->value = strdup(current_var->value);
}

void modify_special_var(struct special_var *current_var)
{
    struct list *tmp = expansion->special_vars;
    while (tmp
           && strcmp(((struct special_var *)tmp->data)->key, current_var->key))
        tmp = tmp->next;
    if (tmp)
    {
        struct special_var *var = tmp->data;
        if (var->value)
            free(var->value);
        var->value = strdup(current_var->value);
    }
}

char *get_special_var(char *key)
{
    struct list *tmp = expansion->special_vars;
    while (tmp && strcmp(((struct special_var *)tmp->data)->key, key))
        tmp = tmp->next;
    if (tmp)
        return ((struct special_var *)tmp->data)->value;
    return NULL;
}

char *get_var(char *key)
{
    return hash_map_get(expansion->variables, key);
}

bool remove_var(char *key)
{
    return hash_map_remove(expansion->variables, key);
}

char *escape_special_chars(char *string)
{
    size_t len = strlen(string);
    char *res = calloc(2 * len + 1, sizeof(char));
    if (!res)
        exit(1);

    size_t j = 0;
    for (size_t i = 0; i < len; i++)
    {
        if (string[i] == '\'' || string[i] == '\"' || string[i] == '\\')
            res[j++] = '\\';
        res[j++] = string[i];
    }
    res[j] = 0;

    return res;
}

void add_var(char *string)
{
    char *start = string;

    while (*string != '=')
        string++;

    size_t len = string - start;
    char *key = calloc(len + 1, sizeof(char));
    strncpy(key, string - len, len);

    string++;
    char *value = calloc(strlen(string) + 1, sizeof(char));
    strcpy(value, string);

    char *res = calloc(1, sizeof(char));
    size_t substitution_idx = 0;
    substitution(value, &substitution_idx, &res);
    size_t remove_idx = 0;
    quotes_removal(res, &remove_idx);
    free(value);

    value = res;
    res = escape_special_chars(value);
    free(value);
    value = res;

    hash_map_insert(expansion->variables, key, value);

    free(key);
    free(value);
}
