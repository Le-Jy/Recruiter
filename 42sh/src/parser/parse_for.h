#ifndef PARSE_FOR_H
#define PARSE_FOR_H

#include <stdbool.h>

#include "parser.h"

/**
 * @brief Return true if the token is in the first table of the rule.
 *
 * @param struct token *token: The token to check
 *
 * @return A boolean.
 */
bool first_for(struct token *token);

/**
 * @brief Parse an expression following this grammar :
 *  rule_for = 'for' WORD ( [';'] | [ {'\n'} 'in' { WORD }
 *  ( ';' | '\n' ) ] ) {'\n'} 'do' compound_list 'done' ;
 *
 * @param struct ast **res : The address of the AST to create.
 *        struct lexer *lexer : The lexer to get tokens.
 *
 * @return The status of the parser : OK or UNEXPECTED_TOKEN.
 */
enum parser_status parse_for(struct ast **res, struct lexer *lexer);

#endif /* ! PARSE_FOR_H */
