#include "count_children.h"

#include "stdlib.h"

int count_children(struct ast *ast)
{
    int res = 0;
    while (ast->children[res] != NULL)
    {
        res++;
    }
    return res;
}
