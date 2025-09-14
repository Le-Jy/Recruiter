#include "exec_and_or.h"

#include <string.h>

#include "../options/verbose.h"
#include "exec_pipeline.h"

int visit_and_or(struct ast *ast)
{
    verbose("Visiting \033[1;37mand_or\033[0;37m:\n");

    int shell_return_code = visit_pipeline(ast->children[0]);
    int return_code = !shell_return_code;

    for (int i = 1; ast->children[i] != NULL; i += 2)
    {
        if (ast->children[i]->type == AST_AND)
        {
            return_code = return_code ? !visit_pipeline(ast->children[i + 1])
                                      : return_code;
        }
        else if (ast->children[i]->type == AST_OR)
        {
            if (!return_code)
            {
                return_code =
                    return_code || !visit_pipeline(ast->children[i + 1]);
            }
        }
    }
    return shell_return_code != 0 ? !return_code * shell_return_code
                                  : !return_code;
}
