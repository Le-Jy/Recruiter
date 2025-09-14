#include "exec_rule_case.h"

#include <fnmatch.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "../options/verbose.h"
#include "../utils/count_children/count_children.h"
#include "exec_compound_list.h"
#include "exec_word.h"

int visit_rule_case(struct ast *ast)
{
    verbose("Visiting \033[1;yy37mrule_rule_case\033[0;37m:\n");

    char *condition = visit_word(ast->children[0]);

    if (ast->children[1] != NULL)
    {
        struct ast *case_clause = ast->children[1];

        for (int i = 0; case_clause->children[i] != NULL; i++)
        {
            struct ast *case_item = case_clause->children[i];

            int j = 0;
            while (case_item->children[j]->type == AST_WORD)
            {
                if (strcmp(condition, case_item->children[j]->value) == 0)
                {
                    free_word(condition);
                    if (case_item->children[count_children(case_item) - 1]->type
                        == AST_COMPOUND_LIST)
                    {
                        return visit_compound_list(
                            case_item->children[count_children(case_item) - 1]);
                    }
                    return 0;
                }
                j++;
            }
        }
    }

    return 0;
}
