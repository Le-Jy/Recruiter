#ifndef EXEC_IONUMBER_H
#define EXEC_IONUMBER_H

#include "../ast/ast.h"

/**
 * @brief Visits the "ionumber" rule in the ast.
 *
 * Handles the logic for processing "ionumber" rule in the grammar.
 *
 * @param Pointer to the AST node representing the "ionumber" rule.
 * @return The value of the io.
 */
int visit_ionumber(struct ast *ast);

#endif /* ! EXEC_IONUMBER_H */
