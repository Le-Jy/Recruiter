#ifndef EXIT_H
#define EXIT_H

#include "../exec_simple_command.h"

/**
 * @brief Set exit_found to 1 and set the exit_value to n or $?
 *
 * @param *cmd pointer to the command line containing exit and n.
 * @return Void.
 */
void command_exit(struct command *cmd);

/**
 * @brief Getter of exit_found.
 *
 * @return Return the value of exit_found
 */
int is_exit_found(void);

/**
 * @brief Getter of exit_value.
 *
 * @return Return the value of exit_value
 */
int get_exit_value(void);

#endif /* ! EXIT_H */
