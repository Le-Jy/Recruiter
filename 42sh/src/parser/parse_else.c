#include "parse_else.h"

#include "parse_compound_list.h"

/**
 * @brief Return true if the token is in the follow table of the rule.
 *
 * @param struct token *token: The token to check
 *
 * @return A boolean.
 */
static bool follow_else(struct token *token)
{
    return (token->type == TOKEN_FI);
}

bool first_else(struct token *token)
{
    return (token->type == TOKEN_ELSE || token->type == TOKEN_ELIF);
}

static enum parser_status parse_else_case(struct ast **res, struct lexer *lexer)
{
    if (!first_compound_list(peek_token(lexer)))
        return PARSER_UNEXPECTED_TOKEN;

    (*res) = new_ast(AST_ELSE);

    (*res)->children = calloc(2, sizeof(struct ast *));

    if (!(*res)->children)
        exit(1);

    if (parse_compound_list(&((*res)->children[0]), lexer) != PARSER_OK)
        return PARSER_UNEXPECTED_TOKEN;

    (*res)->children[1] = NULL;
    if (!follow_else(peek_token(lexer)))
        return PARSER_UNEXPECTED_TOKEN;

    return PARSER_OK;
}

static enum parser_status parse_elif_case(struct ast **res, struct lexer *lexer)
{
    if (!first_compound_list(peek_token(lexer)))
        return PARSER_UNEXPECTED_TOKEN;

    (*res) = new_ast(AST_ELSE);

    (*res)->children = calloc(4, sizeof(struct ast *));
    if (!(*res)->children)
        exit(1);

    if (parse_compound_list(&((*res)->children[0]), lexer) != PARSER_OK)
        return PARSER_UNEXPECTED_TOKEN;

    if (peek_token(lexer)->type != TOKEN_THEN)
        return PARSER_UNEXPECTED_TOKEN;

    token_free(eat_token(lexer));

    if (!first_compound_list(peek_token(lexer)))
        return PARSER_UNEXPECTED_TOKEN;
    if (parse_compound_list(&((*res)->children[1]), lexer) != PARSER_OK)
        return PARSER_UNEXPECTED_TOKEN;

    if (first_else(peek_token(lexer)))
    {
        if (parse_else(&((*res)->children[2]), lexer) != PARSER_OK)
            return PARSER_UNEXPECTED_TOKEN;

        (*res)->children[3] = NULL;
    }
    else
        (*res)->children[2] = NULL;

    if (!follow_else(peek_token(lexer)))
        return PARSER_UNEXPECTED_TOKEN;

    return PARSER_OK;
}

enum parser_status parse_else(struct ast **res, struct lexer *lexer)
{
    struct token *current_token = eat_token(lexer);

    if (current_token->type == TOKEN_ELSE)
    {
        token_free(current_token);
        return parse_else_case(res, lexer);
    }

    if (current_token->type == TOKEN_ELIF)
    {
        token_free(current_token);
        return parse_elif_case(res, lexer);
    }
    token_free(current_token);

    return PARSER_UNEXPECTED_TOKEN;
}
