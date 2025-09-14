#include "exec_ionumber.h"

#include <stdlib.h>

#include "../options/verbose.h"

int visit_ionumber(struct ast *ast)
{
    verbose("Visiting \033[1;37mionumber\033[0;37m:\n");

    return atoi(ast->value);
}
