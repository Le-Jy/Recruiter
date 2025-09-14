#ifndef PARSE_ELEMENT_H
#define PARSE_ELEMENT_H

#include <stdbool.h>

#include "parser.h"

/**
 * @brief Return true if the token is in the first table of the rule.
 *
 * @param struct token *token: The token to check
 *
 * @return A boolean.
 */
bool first_element(struct token *token);

/**
 * @brief Parse an expression following this grammar :
 *  element =
 *      WORD
 *      | redirection
 *      ;
 *
 * @param struct ast **res : The address of the AST to create.
 *        struct lexer *lexer : The lexer to get tokens.
 *
 * @return The status of the parser : OK or UNEXPECTED_TOKEN.
 */
enum parser_status parse_element(struct ast **res, struct lexer *lexer);

#endif /* ! PARSE_ELEMENT_H */
