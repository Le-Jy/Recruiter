#ifndef EXEC_COMMAND_H
#define EXEC_COMMAND_H

#include "../ast/ast.h"

/**
 * @brief Visits the "command" rule in the ast.
 *
 * Handles the logic for processing "command" rule in the grammar.
 *
 * @param Pointer to the AST node representing the "command" rule.
 * @return The result of visiting the targeted rule: simple_command,
 * shell_command, funcdec or redirection
 */
int visit_command(struct ast *ast);

#endif /* ! EXEC_COMMAND_H */
