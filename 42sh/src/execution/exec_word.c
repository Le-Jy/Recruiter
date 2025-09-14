#include "exec_word.h"

#include <stdio.h>
#include <stdlib.h>

#include "../expansion/expand_word.h"
#include "../expansion/expansion.h"
#include "../options/verbose.h"

char *visit_word(struct ast *ast)
{
    verbose("Visiting \033[1;37mword\033[0;37m:\n");

    char *res = calloc(1, sizeof(char));
    int return_value = expand_word(ast->value, &res);
    if (return_value == EXPAND_ERROR)
    {
        fprintf(stderr, "%s: bad substition", ast->value);
    }

    return res;
}

void free_word(char *word)
{
    if (word)
        free(word);
}
