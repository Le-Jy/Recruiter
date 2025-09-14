#ifndef EXEC_ELEMENT_H
#define EXEC_ELEMENT_H

#include "../ast/ast.h"

/**
 * @brief Visits the "element" rule in the ast.
 *
 * Handles the logic for processing "element" rule in the grammar.
 *
 * @param Pointer to the AST node representing the "element" rule.
 * @return The value of the word node.
 */
char *visit_element(struct ast *ast, int *return_code);

#endif /* ! EXEC_ELEMENT_H */
