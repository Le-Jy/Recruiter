#ifndef EXEC_ELSE_CLAUSE_H
#define EXEC_ELSE_CLAUSE_H

#include "../ast/ast.h"

/**
 * @brief Visits the "else" rule in the ast.
 *
 * Handles the logic for processing "else" rule in the grammar.
 *
 * @param Pointer to the AST node representing the "else" rule.
 * @return The result of visiting the elif rule or the else rule.
 */
int visit_else_clause(struct ast *ast);

#endif /* ! EXEC_ELSE_CLAUSE_H */
