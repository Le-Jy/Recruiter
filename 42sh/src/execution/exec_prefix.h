#ifndef EXEC_PREFIX_H
#define EXEC_PREFIX_H

#include "../ast/ast.h"

/**
 * @brief Visits the "prefix" rule in the ast.
 *
 * Handles the logic for processing "prefix" rule in the grammar.
 *
 * @param Pointer to the AST node representing the "prefix" rule.
 * @return 0 if successful, 1 if there is an error.
 */
int visit_prefix(struct ast *ast);

#endif /* ! EXEC_PREFIX_H */
