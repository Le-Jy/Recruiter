#include "exec_while.h"

#include "../options/verbose.h"
#include "builtins/loop_interupt.h"
#include "exec_compound_list.h"

extern struct interupt interupt;

int visit_while(struct ast *ast)
{
    verbose("Visiting \033[1;37mrule_while\033[0;37m:\n");

    interupt.count_loop += 1;

    int return_code = 0;

    while (visit_compound_list(ast->children[0]) == 0)
    {
        if (interupt.break_count > 1)
        {
            interupt.break_count -= 1;
            break;
        }
        return_code = visit_compound_list(ast->children[1]);
        interupt.stop = 0;
    }

    interupt.count_loop -= 1;
    return return_code;
}
