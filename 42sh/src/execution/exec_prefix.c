#include "exec_prefix.h"

#include "../options/verbose.h"
#include "exec_assignement_word.h"
#include "exec_redirection.h"

int visit_prefix(struct ast *ast)
{
    verbose("Visiting \033[1;37mprefix\033[0;37m:\n");

    struct ast *child = ast->children[0];

    if (child->type == AST_REDIRECTION)
    {
        return visit_redirection(child);
    }
    else if (child->type == AST_ASSIGNEMENT_WORD)
    {
        visit_assignement_word(child);
        return 0;
    }
    else
    {
        return 1;
    }
}
