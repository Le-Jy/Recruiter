#include "exec_for.h"

#include <stdlib.h>
#include <string.h>

#include "../expansion/variables.h"
#include "builtins/loop_interupt.h"
#include "exec_compound_list.h"
#include "exec_word.h"

extern struct interupt interupt;

static int len(struct ast *ast)
{
    int res = 0;
    while (ast->children[res] != NULL)
    {
        res++;
    }
    return res;
}

int visit_for(struct ast *ast)
{
    char *var = visit_word(ast->children[0]);
    struct ast *compound_list = ast->children[len(ast) - 1];

    interupt.count_loop += 1;

    int return_code = 0;

    int i = 1;
    while (ast->children[i]->type != AST_COMPOUND_LIST)
    {
        if (interupt.break_count > 1)
        {
            interupt.break_count -= 1;
            break;
        }
        char *target = visit_word(ast->children[i]);
        char *assignment =
            calloc(strlen(var) + strlen(target) + 2, sizeof(char));
        assignment = strcat(assignment, var);
        assignment = strcat(assignment, "=");
        assignment = strcat(assignment, target);
        add_var(assignment);
        free(assignment);

        return_code = visit_compound_list(compound_list);

        interupt.stop = 0;
        i++;
        free_word(target);
    }

    free_word(var);

    interupt.count_loop -= 1;

    return return_code;
}
