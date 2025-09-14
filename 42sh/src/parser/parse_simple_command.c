#include "parse_simple_command.h"

#include <stdlib.h>
#include <string.h>

#include "parse_element.h"
#include "parse_prefix.h"
#include "parser.h"

bool first_simple_command(struct token *token)
{
    return (token->type == TOKEN_WORD || first_prefix(token));
}

/**
 * @brief Return true if the token is in the follow table of the rule.
 *
 * @param struct token *token: The token to check
 *
 * @return A boolean.
 */
static bool follow_simple_command(struct token *token)
{
    return (
        token->type == TOKEN_RPAR || token->type == TOKEN_NEWLINE
        || token->type == TOKEN_EOF || token->type == TOKEN_SEMICOLON
        || (token->type == TOKEN_OPERATOR
            && (!strcmp(token->value, "|") || !strcmp(token->value, "&&")
                || !strcmp(token->value, "||") || !strcmp(token->value, ";;")))
        || token->type == TOKEN_ESAC);
}

static enum parser_status parse_element_loop(struct ast **res,
                                             struct lexer *lexer, size_t *i)
{
    if (!first_element(peek_token(lexer)))
        return PARSER_UNEXPECTED_TOKEN;

    (*res)->children =
        realloc((*res)->children, (*i + 2) * sizeof(struct ast *));
    if (!(*res)->children)
        exit(1);

    (*res)->children[*i + 1] = NULL;

    if (parse_element(&((*res)->children[*i]), lexer) != PARSER_OK)
        return PARSER_UNEXPECTED_TOKEN;
    return PARSER_OK;
}

static enum parser_status parse_prefix_loop(struct ast **res,
                                            struct lexer *lexer, size_t *i)
{
    (*res)->children =
        realloc((*res)->children, (*i + 2) * sizeof(struct ast *));
    if (!(*res)->children)
        exit(1);

    (*res)->children[*i + 1] = NULL;

    if (first_prefix(peek_token(lexer)))
    {
        if (parse_prefix(&((*res)->children[*i]), lexer) != PARSER_OK)
            return PARSER_UNEXPECTED_TOKEN;
        (*i)++;
    }
    return PARSER_OK;
}

enum parser_status parse_simple_command(struct ast **res, struct lexer *lexer)
{
    (*res) = new_ast(AST_SIMPLE_COMMAND);
    size_t i = 0;
    (*res)->children = calloc(2, sizeof(struct ast *));
    if (!(*res)->children)
        exit(1);

    while (true)
    {
        if (follow_simple_command(peek_token(lexer))
            || peek_token(lexer)->type == TOKEN_WORD)
            break;
        if (parse_prefix_loop(res, lexer, &i) != PARSER_OK)
            return PARSER_UNEXPECTED_TOKEN;
    }

    if (!i && peek_token(lexer)->type != TOKEN_WORD)
        return PARSER_UNEXPECTED_TOKEN;

    if (peek_token(lexer)->type == TOKEN_WORD)
    {
        (*res)->children =
            realloc((*res)->children, (i + 2) * sizeof(struct ast *));
        if (!(*res)->children)
            exit(1);

        (*res)->children[i] = new_ast(AST_WORD);
        (*res)->children[i++]->value = strdup(peek_token(lexer)->value);
        token_free(eat_token(lexer));

        while (true)
        {
            if (follow_simple_command(peek_token(lexer)))
                break;
            if (parse_element_loop(res, lexer, &i) != PARSER_OK)
                return PARSER_UNEXPECTED_TOKEN;
            i++;
        }
        (*res)->children =
            realloc((*res)->children, (i + 1) * sizeof(struct ast *));
        if (!(*res)->children)
            exit(1);
        (*res)->children[i] = NULL;
    }
    return PARSER_OK;
}
