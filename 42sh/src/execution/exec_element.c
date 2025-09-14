#include "exec_element.h"

#include "../options/verbose.h"
#include "exec_redirection.h"
#include "exec_word.h"

char *visit_element(struct ast *ast, int *return_code)
{
    verbose("Visiting \033[1;37melement\033[0;37m:\n");

    struct ast *child = ast->children[0];

    switch (child->type)
    {
    case AST_WORD:
        *return_code = 0;
        return visit_word(child);
    case AST_REDIRECTION:
        *return_code = visit_redirection(child);
        break;
    default:
        break;
    }

    return NULL;
}
