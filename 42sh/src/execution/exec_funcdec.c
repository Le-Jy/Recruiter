#define _POSIX_C_SOURCE 200809L

#include "exec_funcdec.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "../utils/hash_map_funcdec/hash_map_funcdec.h"

struct hash_map_funcdec *hash_map_funcdec = NULL;

struct ast *ast_copy(struct ast *ast)
{
    struct ast *res = new_ast(ast->type);
    if (ast->value)
        res->value = strdup(ast->value);
    if (ast->children == NULL)
        return res;
    int max_children = 4;
    res->children = calloc(max_children, sizeof(struct ast));

    for (int i = 0; ast->children[i] != NULL; i++)
    {
        res->children[i] = ast_copy(ast->children[i]);

        if (i - 1 >= max_children)
        {
            max_children *= 2;
            res->children =
                realloc(res->children, max_children * sizeof(struct ast));
        }
    }
    return res;
}

int visit_funcdec(struct ast *ast)
{
    if (!hash_map_funcdec)
    {
        hash_map_funcdec = hash_map_funcdec_init(42);
    }
    struct ast *func = ast_copy(ast->children[1]);
    bool updated = 0;
    hash_map_funcdec_insert(hash_map_funcdec, ast->children[0]->value, func,
                            &updated);
    return 0;
}
