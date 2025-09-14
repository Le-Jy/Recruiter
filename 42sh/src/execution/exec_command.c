#include "exec_command.h"

#include <stdio.h>

#include "../options/verbose.h"
#include "exec_funcdec.h"
#include "exec_redirection.h"
#include "exec_shell_command.h"
#include "exec_simple_command.h"

// TODO : Understand the return
// A return for exec_simple_command is OK because only one argument for this
// derivative No return for shell_command or funcdec becausde 2 arguments for
// these derivatives, we can t stop the rule after reaching only 1 arg / 2
int visit_command(struct ast *ast)
{
    int return_code = 0;

    verbose("Visiting \033[1;37mcommand\033[0;37m:\n");
    for (struct ast **child = ast->children; *child != NULL; ++child)
    {
        switch ((*child)->type)
        {
        case AST_SIMPLE_COMMAND:
            return_code = exec_simple_command(*child);
            break;
        case AST_SHELL_COMMAND:
            return_code = visit_shell_command(*child);
            break;
        case AST_FUNCDEC:
            return_code = visit_funcdec(*child);
            break;
        case AST_REDIRECTION:
            return_code = visit_redirection(*child);
            break;
        default:
            // TODO : gerer erreur
            return_code = 1;
            break;
        }
        verbose("\n");
    }

    redirect();

    return return_code;
}
