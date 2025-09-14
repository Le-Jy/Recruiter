#ifndef PARSE_INPUT_H
#define PARSE_INPUT_H

#include "parser.h"

/**
 * @brief Parse an expression following this grammar :
 *  input =
 *      list '\n'
 *      | list EOF
 *      | '\n'
 *      | EOF
 *      ;
 *
 * @param struct ast **res : The address of the AST to create.
 *        struct lexer *lexer : The lexer to get tokens.
 *
 * @return The status of the parser : OK or UNEXPECTED_TOKEN.
 */
enum parser_status parse_input(struct ast **res, struct lexer *lexer);

#endif /* ! PARSE_INPUT_H */
