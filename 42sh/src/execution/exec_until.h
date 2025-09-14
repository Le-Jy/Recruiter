#ifndef EXEC_UNTIL_H
#define EXEC_UNTIL_H

#include "../ast/ast.h"

/**
 * @brief Visits the "until" rule in the ast.
 *
 * Handles the logic for processing "until" rule in the grammar.
 *
 * @param Pointer to the AST node representing the "until" rule.
 * @return The result of visiting the until rule.
 */
int visit_until(struct ast *ast);

#endif /* ! EXEC_UNTIL_H */
