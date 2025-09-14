#ifndef EXEC_SIMPLE_COMMAND_H
#define EXEC_SIMPLE_COMMAND_H

#include "../ast/ast.h"

struct command
{
    char **command_line;
    int nb_param;
    int max_param;
};

/**
 * @brief Visits the "simple_command" rule in the ast.
 *
 * Handles the logic for processing "simple_command" rule in the grammar.
 *
 * @param Pointer to the AST node representing the "simple_command" rule.
 * @param cmd Pointer to the command structure to be populated with parameters.
 * @return 0 if the structure command has been successfully parsed.
 *         1 if any errors occured.
 */
int visit_simple_command(struct ast *ast, struct command *cmd);

/**
 * @brief Executes the "simple_command" rule in the ast.
 *
 * Creates a command structure, call visit_simple_command(),
 * Finally executes the Builtin/Command.
 *
 * @param Pointer to the AST node representing the "else" rule.
 * @return The exit status of the Builtin/Command.
 */
int exec_simple_command(struct ast *ast);

/**
 * @brief Frees the memory allocated for a command structure.
 *
 * @param cmd Pointer to the command structure to be freed.
 */
void free_command(struct command *cmd);

#endif /* ! EXEC_SIMPLE_COMMAND_H */
