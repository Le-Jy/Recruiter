#include "expansion.h"

#include <stdlib.h>
#include <string.h>

#include "variables.h"

struct expansion *expansion;

static void init_special_vars(void)
{
    struct special_var *current_var = calloc(1, sizeof(struct special_var));
    if (!current_var)
        exit(1);

    current_var->key = "@";
    add_special_var(current_var);

    current_var->key = "*";
    add_special_var(current_var);

    current_var->key = "?";
    add_special_var(current_var);

    current_var->key = "#";
    add_special_var(current_var);

    current_var->key = "$";
    add_special_var(current_var);

    free(current_var);
}

void init_expansion(void)
{
    expansion = calloc(1, sizeof(struct expansion));
    if (!expansion)
        exit(1);

    expansion->variables = hash_map_init(42);
    if (!expansion->variables)
        exit(1);

    hash_map_insert(expansion->variables, "IFS", " \t\n");

    expansion->special_vars = NULL;
    init_special_vars();
}

void free_expansion(void)
{
    struct list *tmp = expansion->special_vars;
    struct special_var *current_var;
    while (tmp)
    {
        current_var = tmp->data;

        free(current_var->key);
        if (current_var->value)
            free(current_var->value);
        tmp = tmp->next;
    }

    list_destroy(expansion->special_vars);
    hash_map_free(expansion->variables);
    free(expansion);
}
