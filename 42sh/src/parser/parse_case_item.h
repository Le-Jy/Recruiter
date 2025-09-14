#ifndef PARSE_CASE_ITEM_H
#define PARSE_CASE_ITEM_H

#include <stdbool.h>

#include "parser.h"

/**
 * @brief Return true if the token is in the first table of the rule.
 *
 * @param struct token *token: The token to check
 *
 * @return A boolean.
 */
bool first_case_item(struct token *token);

/**
 * @brief Parse an expression following this grammar :
 *  case_clause = case_item { ';;' {'\n'} case_item } [';;'] {'\n'} ;
 *
 * @param struct ast **res : The address of the AST to create.
 *        struct lexer *lexer : The lexer to get tokens.
 *
 * @return The status of the parser : OK or UNEXPECTED_TOKEN.
 */
enum parser_status parse_case_item(struct ast **res, struct lexer *lexer);

#endif /* ! PARSE_CASE_ITEM_H */
