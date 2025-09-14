#ifndef EXEC_SHELL_COMMAND_H
#define EXEC_SHELL_COMMAND_H

#include "../ast/ast.h"

/**
 * @brief Visits the "shell_command" rule in the ast.
 *
 * Handles the logic for processing "shell_command" rule in the grammar.
 * Transfers the targeted rule (e.g., "if") to their respective visit functions.
 *
 * @param Pointer to the AST node representing the "shell_command" rule.
 * @return The value of the targeted rule, 1 if there is an error.
 */

int visit_shell_command(struct ast *ast);

#endif /* ! EXEC_SHELL_COMMAND_H */
