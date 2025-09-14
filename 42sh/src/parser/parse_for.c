#include "parse_for.h"

#include <string.h>

#include "parse_compound_list.h"
#include "parser.h"

bool first_for(struct token *token)
{
    return (token->type == TOKEN_FOR);
}

static enum parser_status start_parse_for(struct ast **res, struct lexer *lexer)
{
    token_free(eat_token(lexer));

    if (peek_token(lexer)->type != TOKEN_WORD)
        return PARSER_UNEXPECTED_TOKEN;

    (*res) = new_ast(AST_FOR);

    (*res)->children = calloc(2, sizeof(struct ast *));
    if (!(*res)->children)
        exit(1);

    (*res)->children[0] = new_ast(AST_WORD);
    (*res)->children[0]->value = strdup(peek_token(lexer)->value);
    token_free(eat_token(lexer));
    return PARSER_OK;
}

static enum parser_status end_parse_for(struct ast **res, struct lexer *lexer,
                                        size_t *i)
{
    while (peek_token(lexer)->type == TOKEN_NEWLINE)
        token_free(eat_token(lexer));
    if (peek_token(lexer)->type != TOKEN_DO)
        return PARSER_UNEXPECTED_TOKEN;
    token_free(eat_token(lexer));

    if (!first_compound_list(peek_token(lexer)))
        return PARSER_UNEXPECTED_TOKEN;

    (*res)->children =
        realloc((*res)->children, (*i + 2) * sizeof(struct ast *));
    if (!(*res)->children)
        exit(1);
    (*res)->children[*i + 1] = NULL;

    if (parse_compound_list(&((*res)->children[*i]), lexer) != PARSER_OK)
        return PARSER_UNEXPECTED_TOKEN;

    if (peek_token(lexer)->type != TOKEN_DONE)
        return PARSER_UNEXPECTED_TOKEN;
    token_free(eat_token(lexer));
    return PARSER_OK;
}

enum parser_status parse_for(struct ast **res, struct lexer *lexer)
{
    if (start_parse_for(res, lexer) != PARSER_OK)
        return PARSER_UNEXPECTED_TOKEN;

    size_t i = 1;
    if (peek_token(lexer)->type == TOKEN_SEMICOLON)
    {
        token_free(eat_token(lexer));
    }
    else
    {
        while (peek_token(lexer)->type == TOKEN_NEWLINE)
            token_free(eat_token(lexer));
        if (peek_token(lexer)->type == TOKEN_IN)
        {
            token_free(eat_token(lexer));
            while (peek_token(lexer)->type == TOKEN_WORD)
            {
                (*res)->children =
                    realloc((*res)->children, (i + 2) * sizeof(struct ast *));
                if (!(*res)->children)
                    exit(1);

                (*res)->children[i] = new_ast(AST_WORD);
                (*res)->children[i]->value = strdup(peek_token(lexer)->value);
                (*res)->children[i + 1] = NULL;
                i++;
                token_free(eat_token(lexer));
            }
            if (peek_token(lexer)->type != TOKEN_SEMICOLON
                && peek_token(lexer)->type != TOKEN_NEWLINE)
                return PARSER_UNEXPECTED_TOKEN;
            token_free(eat_token(lexer));
        }
    }
    return end_parse_for(res, lexer, &i);
}
