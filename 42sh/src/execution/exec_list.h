#ifndef EXEC_LIST_H
#define EXEC_LIST_H

#include "../ast/ast.h"

/**
 * @brief Visits the "list" rule in the ast.
 *
 * Handles the logic for processing "list" rule in the grammar.
 *
 * @param Pointer to the AST node representing the "list" rule.
 * @return The binary operation "or" on all the and_or rule return values.
 */
int visit_list(struct ast *ast);

#endif /* ! EXEC_LIST_H */
