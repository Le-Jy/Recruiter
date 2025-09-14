#include "parse_prefix.h"

#include <string.h>

#include "parse_redirection.h"

bool first_prefix(struct token *token)
{
    return first_redirection(token) || token->type == TOKEN_ASSIGNMENT_WORD;
}

enum parser_status parse_prefix(struct ast **res, struct lexer *lexer)
{
    struct token *current_token = peek_token(lexer);

    if (current_token->type == TOKEN_ASSIGNMENT_WORD)
    {
        (*res) = new_ast(AST_PREFIX);

        (*res)->children = calloc(2, sizeof(struct ast *));
        if (!(*res)->children)
            exit(1);

        (*res)->children[0] = new_ast(AST_ASSIGNEMENT_WORD);
        (*res)->children[0]->value = strdup(current_token->value);
        (*res)->children[1] = NULL;
        token_free(eat_token(lexer));

        return PARSER_OK;
    }

    if (first_redirection(current_token))
    {
        (*res) = new_ast(AST_PREFIX);

        (*res)->children = calloc(2, sizeof(struct ast *));
        if (!(*res)->children)
            exit(1);

        (*res)->children[1] = NULL;

        if (parse_redirection(&((*res)->children[0]), lexer) != PARSER_OK)
            return PARSER_UNEXPECTED_TOKEN;

        return PARSER_OK;
    }
    return PARSER_UNEXPECTED_TOKEN;
}
