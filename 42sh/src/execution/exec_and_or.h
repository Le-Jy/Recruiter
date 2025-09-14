#ifndef EXEC_AND_OR_H
#define EXEC_AND_OR_H

#include "../ast/ast.h"

/**
 * @brief Visits the "and_or" rule in the ast.
 *
 * Handles the logic for processing "and_or" rule in the grammar.
 *
 * @param Pointer to the AST node representing the "and_or" rule.
 * @return 0 if successful, 1 if there is an error.
 */
int visit_and_or(struct ast *ast);

#endif /* ! EXEC_AND_OR_H */
