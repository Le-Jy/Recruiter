#ifndef EXEC_RULE_CASE_H
#define EXEC_RULE_CASE_H

#include "../ast/ast.h"

/**
 * @brief Visits the "rule case" rule in the ast.
 *
 * Handles the logic for processing "rule case" rule in the grammar.
 *
 * @param Pointer to the AST node representing the "rule case" rule.
 */
int visit_rule_case(struct ast *ast);

#endif /* ! EXEC_RULE_CASE_H */
