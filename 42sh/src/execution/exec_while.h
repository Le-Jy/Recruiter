#ifndef EXEC_WHILE_H
#define EXEC_WHILE_H

#include "../ast/ast.h"

/**
 * @brief Visits the "while" rule in the ast.
 *
 * Handles the logic for processing "while" rule in the grammar.
 *
 * @param Pointer to the AST node representing the "while" rule.
 * @return The result of visiting the while rule.
 */
int visit_while(struct ast *ast);

#endif /* ! EXEC_WHILE_H */
