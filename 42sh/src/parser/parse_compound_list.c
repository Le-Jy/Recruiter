#include "parse_compound_list.h"

#include <string.h>

#include "parse_and_or.h"

/**
 * @brief Return true if the token is in the follow table of the rule.
 *
 * @param struct token *token: The token to check
 *
 * @return A boolean.
 */
static bool follow_compound_list(struct token *token)
{
    return (token->type == TOKEN_THEN || token->type == TOKEN_ELSE
            || token->type == TOKEN_ELIF || token->type == TOKEN_FI
            || token->type == TOKEN_DO || token->type == TOKEN_DONE
            || token->type == TOKEN_RPAR || token->type == TOKEN_RBRACE
            || (token->type == TOKEN_OPERATOR && !strcmp(token->value, ";;"))
            || token->type == TOKEN_ESAC);
}

bool first_compound_list(struct token *token)
{
    return (token->type == TOKEN_NEWLINE || first_and_or(token));
}

/**
 * @brief Subroutine of parse_compound_list to call multiples and_or rules.
 *
 * @param struct ast **res : The address of the AST to create.
 *        struct lexer *lexer : The lexer to get tokens.
 *        size_t i : adress of the idexer.
 *
 * @return The status of the parser : OK or UNEXPECTED_TOKEN.
 */
static enum parser_status call_for_and_or(struct ast **res, struct lexer *lexer,
                                          size_t *i)
{
    while (true)
    {
        struct token *current_token = peek_token(lexer);

        if (current_token->type == TOKEN_RPAR
            || (current_token->type == TOKEN_OPERATOR
                && !strcmp(current_token->value, ";;")))
            return PARSER_OK;

        if (current_token->type != TOKEN_SEMICOLON
            && current_token->type != TOKEN_NEWLINE)
            return PARSER_UNEXPECTED_TOKEN;

        token_free(eat_token(lexer));

        while (peek_token(lexer)->type == TOKEN_NEWLINE)
            token_free(eat_token(lexer));

        if (follow_compound_list(peek_token(lexer)))
            break;

        if (!first_and_or(peek_token(lexer)))
            return PARSER_UNEXPECTED_TOKEN;

        (*res)->children =
            realloc((*res)->children, (*i + 2) * sizeof(struct ast *));
        if (!(*res)->children)
            exit(1);
        (*res)->children[*i + 1] = NULL;

        if (parse_and_or(&((*res)->children[*i]), lexer) != PARSER_OK)
            return PARSER_UNEXPECTED_TOKEN;

        *i += 1;
    }
    return PARSER_OK;
}

enum parser_status parse_compound_list(struct ast **res, struct lexer *lexer)
{
    while (peek_token(lexer)->type == TOKEN_NEWLINE)
        token_free(eat_token(lexer));

    struct token *current_token = peek_token(lexer);

    if (!first_and_or(current_token))
        return PARSER_UNEXPECTED_TOKEN;

    size_t i = 1;

    (*res) = new_ast(AST_COMPOUND_LIST);

    (*res)->children = calloc(2, sizeof(struct ast *));
    if (!(*res)->children)
        exit(1);

    if (parse_and_or(&((*res)->children[0]), lexer) != PARSER_OK)
        return PARSER_UNEXPECTED_TOKEN;

    if (call_for_and_or(res, lexer, &i) != PARSER_OK)
        return PARSER_UNEXPECTED_TOKEN;

    (*res)->children =
        realloc((*res)->children, (i + 1) * sizeof(struct ast *));
    if (!(*res)->children)
        exit(1);

    (*res)->children[i] = NULL;

    while (peek_token(lexer)->type == TOKEN_NEWLINE)
        token_free(eat_token(lexer));

    return PARSER_OK;
}
