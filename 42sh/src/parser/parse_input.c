#include "parse_input.h"

#include <stdio.h>

#include "parse_list.h"

enum parser_status parse_input(struct ast **res, struct lexer *lexer)
{
    struct token *current_token = peek_token(lexer);

    *res = NULL;

    if (current_token->type == TOKEN_EOF
        || current_token->type == TOKEN_NEWLINE)
    {
        if (current_token->type == TOKEN_EOF)
        {
            *res = new_ast(AST_EOF);
            token_free(eat_token(lexer));
            lexer->next_token = NULL;
        }
        else
            token_free(eat_token(lexer));
        return PARSER_OK;
    }

    if (!first_list(peek_token(lexer)))
        return PARSER_UNEXPECTED_TOKEN;

    if (parse_list(res, lexer) == PARSER_OK)
    {
        current_token = peek_token(lexer);
        if (current_token->type == TOKEN_NEWLINE)
        {
            if (lexer->fd != stdin)
                token_free(eat_token(lexer));

            return PARSER_OK;
        }
        if (current_token->type == TOKEN_EOF)
            return PARSER_OK;
    }
    free_ast(*res);
    return PARSER_UNEXPECTED_TOKEN;
}
