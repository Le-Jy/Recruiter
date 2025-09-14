#include "parse_and_or.h"

#include <string.h>

#include "parse_pipeline.h"

bool first_and_or(struct token *token)
{
    return first_pipeline(token);
}

static bool follow_and_or(struct token *token)
{
    return (token->type == TOKEN_RPAR || token->type == TOKEN_NEWLINE
            || token->type == TOKEN_EOF || token->type == TOKEN_SEMICOLON
            || (token->type == TOKEN_OPERATOR && !strcmp(token->value, ";;"))
            || token->type == TOKEN_ESAC);
}

static void create_and_or_children(struct ast **res, struct lexer *lexer,
                                   size_t i)
{
    if (strstr(peek_token(lexer)->value, "&&"))
    {
        (*res)->children[i] = new_ast(AST_AND);
    }
    else
        (*res)->children[i] = new_ast(AST_OR);
}

enum parser_status parse_and_or(struct ast **res, struct lexer *lexer)
{
    struct token *current_token = peek_token(lexer);

    (*res) = new_ast(AST_AND_OR);

    (*res)->children = calloc(2, sizeof(struct ast *));
    if (!(*res)->children)
        exit(1);

    if (!first_pipeline(current_token))
        return PARSER_UNEXPECTED_TOKEN;
    if (parse_pipeline(&((*res)->children[0]), lexer) != PARSER_OK)
        return PARSER_UNEXPECTED_TOKEN;
    size_t i = 1;
    while (true)
    {
        struct token *current_token = peek_token(lexer);

        if (follow_and_or(peek_token(lexer)))
            break;
        if (current_token->type != TOKEN_OPERATOR &&

            (!strstr(current_token->value, "&&")
             || !strstr(current_token->value, "||")))
            return PARSER_UNEXPECTED_TOKEN;

        (*res)->children =
            realloc((*res)->children, (i + 3) * sizeof(struct ast *));
        if (!(*res)->children)
            exit(1);
        (*res)->children[i + 1] = NULL;
        (*res)->children[i + 2] = NULL;

        create_and_or_children(res, lexer, i++);

        token_free(eat_token(lexer));

        while (peek_token(lexer)->type == TOKEN_NEWLINE)
            token_free(eat_token(lexer));

        if (!first_pipeline(peek_token(lexer)))
            return PARSER_UNEXPECTED_TOKEN;

        if (parse_pipeline(&((*res)->children[i]), lexer) != PARSER_OK)
            return PARSER_UNEXPECTED_TOKEN;

        i += 1;
    }
    return PARSER_OK;

    (*res)->children[1] = NULL;
    return PARSER_OK;
}
