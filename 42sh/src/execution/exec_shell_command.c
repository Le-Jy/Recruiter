
#include "exec_shell_command.h"

#include "../options/verbose.h"
#include "exec_command_block.h"
#include "exec_for.h"
#include "exec_if.h"
#include "exec_rule_case.h"
#include "exec_subshell.h"
#include "exec_until.h"
#include "exec_while.h"

int visit_shell_command(struct ast *ast)
{
    verbose("Visiting \033[1;37mshell_command\033[0;37m:\n");

    struct ast *child = ast->children[0];
    switch (child->type)
    {
    case AST_FOR:
        return visit_for(child);
    case AST_WHILE:
        return visit_while(child);
    case AST_UNTIL:
        return visit_until(child);
    case AST_CASE:
        return visit_rule_case(child);
    case AST_IF:
        return visit_if(child);
    case AST_COMMAND_BLOCK:
        return visit_command_block(child);
    case AST_SUBSHELL:
        return visit_subshell(child);
    default:
        return 1;
        break;
    }

    return 1;
}
