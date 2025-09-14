#include "exec_assignement_word.h"

#include "../expansion/variables.h"

void visit_assignement_word(struct ast *ast)
{
    add_var(ast->value);
}
