#ifndef EXEC_REDIRECTION_H
#define EXEC_REDIRECTION_H

#include <stddef.h>

#include "../ast/ast.h"

struct redirection_data
{
    int stream_dup;
    int target_stream;
    struct redirection_data *next;
};

/**
 * @brief Visits the "redirection" rule in the ast.
 *
 * Handles the logic for processing "redirection" rule in the grammar.
 *
 * @param Pointer to the AST node representing the "redirection" rule.
 * @return 0 if successful, 1 if there is an error.
 */
int visit_redirection(struct ast *ast);

void redirect(void);

#endif /* ! EXEC_REDIRECTION_H */
