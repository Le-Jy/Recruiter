#ifndef EXEC_IF_H
#define EXEC_IF_H

#include "../ast/ast.h"

/**
 * @brief Visits the "if" rule in the ast.
 *
 * Handles the logic for processing "if" rule in the grammar.
 *
 * @param Pointer to the AST node representing the "if" rule.
 * @return The result of visiting the if rule, the else rule or return 0 if no
 * else rule.
 */
int visit_if(struct ast *ast);

#endif /* ! EXEC_IF_H */
