#include "parse_command.h"

#include <string.h>

#include "parse_funcdec.h"
#include "parse_redirection.h"
#include "parse_shell_command.h"
#include "parse_simple_command.h"
#include "parser.h"

bool first_command(struct token *token)
{
    return first_simple_command(token) || first_shell_command(token)
        || first_funcdec(token);
}

/**
 * @brief Return true if the token is in the follow table of the rule.
 *
 * @param struct token *token: The token to check
 *
 * @return A boolean.
 */
static bool follow_command(struct token *token)
{
    return (
        token->type == TOKEN_RPAR || token->type == TOKEN_NEWLINE
        || token->type == TOKEN_EOF || token->type == TOKEN_SEMICOLON
        || (token->type == TOKEN_OPERATOR
            && (!strcmp(token->value, "|") || !strcmp(token->value, "&&")
                || !strcmp(token->value, "||") || !strcmp(token->value, ";;")))
        || token->type == TOKEN_ESAC);
}

enum parser_status parse_command(struct ast **res, struct lexer *lexer)
{
    bool is_redirection = false;
    struct token *current_token = peek_token(lexer);

    (*res) = new_ast(AST_COMMAND);

    (*res)->children = calloc(2, sizeof(struct ast *));
    if (!(*res)->children)
        exit(1);

    if (first_funcdec(current_token) && look_ahead(lexer)->type == TOKEN_LPAR)
    {
        if (parse_funcdec(&((*res)->children[0]), lexer) != PARSER_OK)
            return PARSER_UNEXPECTED_TOKEN;

        is_redirection = true;
    }
    else if (first_simple_command(current_token))
    {
        if (parse_simple_command(&((*res)->children[0]), lexer) != PARSER_OK)
            return PARSER_UNEXPECTED_TOKEN;

        (*res)->children[1] = NULL;
        return PARSER_OK;
    }
    else if (first_shell_command(current_token))
    {
        if (parse_shell_command(&((*res)->children[0]), lexer) != PARSER_OK)
            return PARSER_UNEXPECTED_TOKEN;

        is_redirection = true;
    }

    if (is_redirection)
    {
        size_t i = 1;
        while (true)
        {
            if (follow_command(peek_token(lexer)))
                break;

            if (!first_redirection(peek_token(lexer)))
                return PARSER_UNEXPECTED_TOKEN;

            (*res)->children =
                realloc((*res)->children, (i + 2) * sizeof(struct ast *));
            if (!(*res)->children)
                exit(1);

            (*res)->children[i + 1] = NULL;

            if (parse_redirection(&((*res)->children[i]), lexer) != PARSER_OK)
                return PARSER_UNEXPECTED_TOKEN;

            i++;
        }
        return PARSER_OK;
    }

    return PARSER_UNEXPECTED_TOKEN;
}
