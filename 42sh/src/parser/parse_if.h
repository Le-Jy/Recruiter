#ifndef PARSE_IF_H
#define PARSE_IF_H

#include <stdbool.h>

#include "parser.h"

/**
 * @brief Return true if the token is in the first table of the rule.
 *
 * @param struct token *token: The token to check
 *
 * @return A boolean.
 */
bool first_if(struct token *token);

/**
 * @brief Parse an expression following this grammar :
 *  rule_if = 'if' compound_list 'then' compound_list [else_clause] 'fi' ;
 *
 * @param struct ast **res : The address of the AST to create.
 *        struct lexer *lexer : The lexer to get tokens.
 *
 * @return The status of the parser : OK or UNEXPECTED_TOKEN.
 */
enum parser_status parse_if(struct ast **res, struct lexer *lexer);

#endif /* ! PARSE_IF_H */
