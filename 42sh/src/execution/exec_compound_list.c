#include "exec_compound_list.h"

#include <stdlib.h>

#include "../options/verbose.h"
#include "builtins/loop_interupt.h"
#include "exec_and_or.h"

extern struct interupt interupt;

int visit_compound_list(struct ast *ast)
{
    verbose("Visiting \033[1;37mcompound_list\033[0;37m:\n");
    int return_value = 1;
    for (struct ast **child = ast->children; *child != NULL; ++child)
    {
        if (interupt.stop == 1)
        {
            return 0;
        }

        if ((*child)->type == AST_AND_OR)
        {
            return_value &= visit_and_or(*child);
        }
    }

    return return_value;
}
