#include "parse_list.h"

#include "parse_and_or.h"

bool first_list(struct token *token)
{
    return first_and_or(token);
}

/**
 * @brief Return true if the token is in the follow table of the rule.
 *
 * @param struct token *token: The token to check
 *
 * @return A boolean.
 */
static bool follow_list(struct token *token)
{
    return (token->type == TOKEN_EOF || token->type == TOKEN_NEWLINE);
}

enum parser_status parse_list(struct ast **res, struct lexer *lexer)
{
    struct token *current_token = peek_token(lexer);

    if (!first_and_or(current_token))
        return PARSER_UNEXPECTED_TOKEN;

    (*res) = new_ast(AST_LIST);

    size_t i = 1;

    (*res)->children = calloc(2, sizeof(struct ast *));
    if (!(*res)->children)
        exit(1);

    if (parse_and_or(&((*res)->children[0]), lexer) != PARSER_OK)
        return PARSER_UNEXPECTED_TOKEN;

    while (true)
    {
        current_token = peek_token(lexer);

        if (follow_list(current_token))
            break;

        if (current_token->type == TOKEN_SEMICOLON)
            token_free(eat_token(lexer));

        current_token = peek_token(lexer);

        if (follow_list(current_token))
            break;

        if (!first_and_or(peek_token(lexer)))
        {
            while (!follow_list(peek_token(lexer)))
                token_free(eat_token(lexer));

            return PARSER_UNEXPECTED_TOKEN;
        }

        (*res)->children =
            realloc((*res)->children, (i + 2) * sizeof(struct ast *));
        if (!(*res)->children)
            exit(1);

        (*res)->children[i + 1] = NULL;

        if (parse_and_or(&((*res)->children[i]), lexer) != PARSER_OK)
            return PARSER_UNEXPECTED_TOKEN;
        i++;
    }

    (*res)->children =
        realloc((*res)->children, (i + 1) * sizeof(struct ast *));

    if (!(*res)->children)
        exit(1);

    (*res)->children[i] = NULL;

    return PARSER_OK;
}
