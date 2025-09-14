#include "parse_funcdec.h"

#include <string.h>

#include "parse_shell_command.h"

bool first_funcdec(struct token *token)
{
    return token->type == TOKEN_WORD;
}

enum parser_status parse_funcdec(struct ast **res, struct lexer *lexer)
{
    (*res) = new_ast(AST_FUNCDEC);
    (*res)->children = calloc(3, sizeof(struct ast *));
    if (!(*res)->children)
        exit(1);
    (*res)->children[0] = new_ast(AST_WORD);
    (*res)->children[0]->value = strdup(peek_token(lexer)->value);

    token_free(eat_token(lexer));
    token_free(eat_token(lexer));
    if (peek_token(lexer)->type != TOKEN_RPAR)
        return PARSER_UNEXPECTED_TOKEN;
    token_free(eat_token(lexer));

    while (peek_token(lexer)->type == TOKEN_NEWLINE)
        token_free(eat_token(lexer));

    if (!first_shell_command(peek_token(lexer)))
        return PARSER_UNEXPECTED_TOKEN;

    if (parse_shell_command(&((*res)->children[1]), lexer) != PARSER_OK)
        return PARSER_UNEXPECTED_TOKEN;

    return PARSER_OK;
}
