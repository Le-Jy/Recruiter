#include "exec_else_clause.h"

#include <stdlib.h>

#include "../options/verbose.h"
#include "exec_compound_list.h"

int visit_else_clause(struct ast *ast)
{
    if (ast->children[1] == NULL)
    {
        verbose("\033[1;37mElse\033[0;37m:\n");
        return visit_compound_list(ast->children[0]);
    }
    else if (visit_compound_list(ast->children[0]) == 0)
    {
        verbose("\033[1;37mElse If \033[0;37mcondition is "
                "\033[1;37mtrue\033[0;37m:\n");
        return visit_compound_list(ast->children[1]);
    }
    else if (ast->children[2] != NULL)
    {
        verbose("\033[1;37mElse If \033[0;37mcondition is "
                "\033[1;37mfalse\033[0;37m:\n");
        return visit_else_clause(ast->children[2]);
    }
    else
    {
        return 0;
    }
}
