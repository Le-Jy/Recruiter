#include "exec_command_block.h"

#include "exec_compound_list.h"

int visit_command_block(struct ast *ast)
{
    return visit_compound_list(ast->children[0]);
}
