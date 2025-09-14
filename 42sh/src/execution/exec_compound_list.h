#ifndef EXEC_COMPOUND_LIST_H
#define EXEC_COMPOUND_LIST_H

#include "../ast/ast.h"

/**
 * @brief Visits the "compound_list" rule in the ast.
 *
 * Handles the logic for processing "compound_list" rule in the grammar.
 *
 * @param Pointer to the AST node representing the "compound_list" rule.
 * @return The binary operation "and" on all the and_or rule return values.
 */
int visit_compound_list(struct ast *ast);

#endif /* ! EXEC_COMPOUND_LIST_H */
