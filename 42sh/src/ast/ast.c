#include "ast.h"

#include <stdlib.h>

struct ast *new_ast(enum ast_type type)
{
    struct ast *new_ast = calloc(1, sizeof(struct ast));
    if (!new_ast)
        return NULL;

    new_ast->type = type;

    return new_ast;
}

void free_ast(struct ast *ast)
{
    if (!ast)
        return;

    if (ast->children)
    {
        size_t i = 0;
        while (ast->children[i])
        {
            free_ast(ast->children[i]);
            i++;
        }

        free(ast->children);
    }
    if (ast->value)
        free(ast->value);
    free(ast);
}
