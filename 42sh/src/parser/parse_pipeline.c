#include "parse_pipeline.h"

#include <string.h>

#include "parse_command.h"

bool first_pipeline(struct token *token)
{
    return (token->type == TOKEN_NOT || first_command(token));
}

static bool follow_pipeline(struct token *token)
{
    return (token->type == TOKEN_RPAR || token->type == TOKEN_NEWLINE
            || token->type == TOKEN_EOF || token->type == TOKEN_SEMICOLON
            || (token->type == TOKEN_OPERATOR && token->value
                && (!strcmp(token->value, "&&") || !strcmp(token->value, "||")
                    || !strcmp(token->value, ";;")))
            || token->type == TOKEN_ESAC);
}

enum parser_status parse_pipeline(struct ast **res, struct lexer *lexer)
{
    struct token *current_token = peek_token(lexer);

    if (!first_pipeline(current_token))
        return PARSER_UNEXPECTED_TOKEN;

    (*res) = new_ast(AST_PIPELINE);

    (*res)->children = calloc(3, sizeof(struct ast *));
    if (!(*res)->children)
        exit(1);

    size_t i = 0;

    if (current_token->type == TOKEN_NOT)
    {
        token_free(eat_token(lexer));
        (*res)->children[i++] = new_ast(AST_NOT);
    }

    if (parse_command(&((*res)->children[i++]), lexer) != PARSER_OK)
        return PARSER_UNEXPECTED_TOKEN;

    while (true)
    {
        if (follow_pipeline(peek_token(lexer)))
            break;

        if (peek_token(lexer)->type != TOKEN_OPERATOR
            && strcmp(peek_token(lexer)->value, "|"))
            return PARSER_UNEXPECTED_TOKEN;
        token_free(eat_token(lexer));

        while (peek_token(lexer)->type == TOKEN_NEWLINE)
            token_free(eat_token(lexer));

        (*res)->children =
            realloc((*res)->children, (i + 2) * sizeof(struct ast *));
        if (!(*res)->children)
            exit(1);

        (*res)->children[i + 1] = NULL;

        if (parse_command(&((*res)->children[i]), lexer) != PARSER_OK)
            return PARSER_UNEXPECTED_TOKEN;

        i++;
    }
    return PARSER_OK;
}
