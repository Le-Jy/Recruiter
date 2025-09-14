#include "parse_element.h"

#include <string.h>

#include "parse_redirection.h"

bool first_element(struct token *token)
{
    return (token->type == TOKEN_WORD || token->value
            || first_redirection(token));
}

enum parser_status parse_element(struct ast **res, struct lexer *lexer)
{
    if (peek_token(lexer)->type == TOKEN_ERROR)
        return PARSER_UNEXPECTED_TOKEN;

    struct token *current_token = peek_token(lexer);

    if (!current_token->value && !first_redirection(current_token))
    {
        token_free(eat_token(lexer));
        return PARSER_UNEXPECTED_TOKEN;
    }

    (*res) = new_ast(AST_ELEMENT);
    (*res)->children = calloc(2, sizeof(struct ast *));
    if (!(*res)->children)
        exit(1);

    if (first_redirection(current_token))
    {
        if (parse_redirection(&((*res)->children[0]), lexer) != PARSER_OK)
            return PARSER_UNEXPECTED_TOKEN;

        (*res)->children[1] = NULL;
        return PARSER_OK;
    }

    (*res)->children[0] = new_ast(AST_WORD);
    (*res)->children[0]->value = strdup(current_token->value);
    (*res)->children[1] = NULL;

    token_free(eat_token(lexer));

    return PARSER_OK;
}
