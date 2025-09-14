#include "exec_if.h"

#include <stddef.h>

#include "../options/verbose.h"
#include "exec_compound_list.h"
#include "exec_else_clause.h"

int visit_if(struct ast *ast)
{
    verbose("Visiting \033[1;37mrule_if\033[0;37m:\n");

    if (visit_compound_list(ast->children[0]) == 0)
    {
        verbose(
            "\033[1;37mIf \033[0;37mcondition is \033[1;37mtrue\033[0;37m:\n");
        return visit_compound_list(ast->children[1]);
    }
    else if (ast->children[2] != NULL)
    {
        verbose(
            "\033[1;37mIf \033[0;37mcondition is \033[1;37mfalse\033[0;37m:\n");
        return visit_else_clause(ast->children[2]);
    }

    return 0;
}
