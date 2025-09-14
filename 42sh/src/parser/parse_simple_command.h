#ifndef PARSE_SIMPLE_COMMAND_H
#define PARSE_SIMPLE_COMMAND_H

#include <stdbool.h>

#include "parser.h"

/**
 * @brief Return true if the token is in the first table of the rule.
 *
 * @param struct token *token: The token to check
 *
 * @return A boolean.
 */
bool first_simple_command(struct token *token);

/**
 * @brief Parse an expression following this grammar :
 *  simple_command =
 *      prefix { prefix }
 *      | { prefix } WORD { element }
 *      ;
 *
 * @param struct ast **res : The address of the AST to create.
 *        struct lexer *lexer : The lexer to get tokens.
 *
 * @return The status of the parser : OK or UNEXPECTED_TOKEN.
 */
enum parser_status parse_simple_command(struct ast **res, struct lexer *lexer);

#endif /* ! PARSE_SIMPLE_COMMAND_H */
