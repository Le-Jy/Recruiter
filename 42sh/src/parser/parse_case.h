#ifndef PARSE_CASE_H
#define PARSE_CASE_H

#include <stdbool.h>

#include "parser.h"

/**
 * @brief Return true if the token is in the first table of the rule.
 *
 * @param struct token *token: The token to check
 *
 * @return A boolean.
 */
bool first_case(struct token *token);

/**
 * @brief Parse an expression following this grammar :
 *  rule_case = 'case' WORD {'\n'} 'in' {'\n'} [case_clause] 'esac' ;
 *
 * @param struct ast **res : The address of the AST to create.
 *        struct lexer *lexer : The lexer to get tokens.
 *
 * @return The status of the parser : OK or UNEXPECTED_TOKEN.
 */
enum parser_status parse_case(struct ast **res, struct lexer *lexer);

#endif /* ! PARSE_CASE_H */
