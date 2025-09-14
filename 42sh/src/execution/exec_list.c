#include "exec_list.h"

#include <stdlib.h>

#include "../options/verbose.h"
#include "exec_and_or.h"

int visit_list(struct ast *ast)
{
    int return_code = 0;

    verbose("Visiting \033[1;37mlist\033[0;37m:\n");
    for (struct ast **child = ast->children; *child != NULL; ++child)
    {
        if ((*child)->type == AST_AND_OR)
        {
            return_code = visit_and_or(*child);
        }
        else
        {
            return 1;
        }
    }
    return return_code;
}
