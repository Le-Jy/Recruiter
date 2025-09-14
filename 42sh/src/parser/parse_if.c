#include "parse_if.h"

#include <string.h>

#include "parse_compound_list.h"
#include "parse_else.h"
#include "parse_redirection.h"

/**
 * @brief Return true if the token is in the follow table of the rule.
 *
 * @param struct token *token: The token to check
 *
 * @return A boolean.
 */
static bool follow_if(struct token *token)
{
    return (
        token->type == TOKEN_RPAR || first_redirection(token)
        || token->type == TOKEN_NEWLINE || token->type == TOKEN_EOF
        || token->type == TOKEN_SEMICOLON
        || (token->type == TOKEN_OPERATOR
            && (!strcmp(token->value, "|") || !strcmp(token->value, "&&")
                || !strcmp(token->value, "||") || !strcmp(token->value, ";;")))
        || token->type == TOKEN_ESAC);
}

bool first_if(struct token *token)
{
    return (token->type == TOKEN_IF);
}

static enum parser_status parse_if_case(struct ast **res, struct lexer *lexer)
{
    struct token *current_token = peek_token(lexer);
    if (!first_compound_list(current_token))
        return PARSER_UNEXPECTED_TOKEN;

    (*res) = new_ast(AST_IF);

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
    if (peek_token(lexer)->type != TOKEN_FI)
        return PARSER_UNEXPECTED_TOKEN;

    token_free(eat_token(lexer));

    if (!follow_if(peek_token(lexer)))
        return PARSER_UNEXPECTED_TOKEN;

    return PARSER_OK;
}

enum parser_status parse_if(struct ast **res, struct lexer *lexer)
{
    struct token *current_token = eat_token(lexer);

    if (current_token->type == TOKEN_IF)
    {
        token_free(current_token);
        return parse_if_case(res, lexer);
    }
    token_free(current_token);

    return PARSER_UNEXPECTED_TOKEN;
}
