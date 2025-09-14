#ifndef EXEC_PIPELINE_H
#define EXEC_PIPELINE_H

#include <stddef.h>

#include "../ast/ast.h"

enum pipe_side
{
    LEFT,
    RIGHT
};

/**
 * @brief Visits the "pipeline" rule in the ast.
 *
 * Handles the logic for processing "pipeline" rule in the grammar.
 *
 * @param Pointer to the AST node representing the "pipeline" rule.
 * @return The result of visiting the last command rule piped with the others.
 */
int visit_pipeline(struct ast *ast);

#endif /* ! EXEC_PIPELINE_H */
