#include "parse_case_clause.h"

#include <string.h>

#include "parse_case_item.h"

static bool follow_case_clause(struct token *token)
{
    return (token->type == TOKEN_ESAC);
}

bool first_case_clause(struct token *token)
{
    return first_case_item(token);
}

enum parser_status parse_case_clause(struct ast **res, struct lexer *lexer)
{
    if (!first_case_item(peek_token(lexer)))
        return PARSER_UNEXPECTED_TOKEN;
    size_t i = 1;
    (*res) = new_ast(AST_CASE_CLAUSE);
    (*res)->children = calloc(2, sizeof(struct ast *));
    if (parse_case_item(&((*res)->children[0]), lexer) != PARSER_OK)
        return PARSER_UNEXPECTED_TOKEN;
    while (true)
    {
        if (peek_token(lexer)->type != TOKEN_OPERATOR
            && strcmp(";;", peek_token(lexer)->value))
            break;
        token_free(eat_token(lexer));

        while (peek_token(lexer)->type == TOKEN_NEWLINE)
            token_free(eat_token(lexer));

        if (follow_case_clause(peek_token(lexer)))
            break;

        if (!first_case_item(peek_token(lexer)))
            return PARSER_UNEXPECTED_TOKEN;

        (*res)->children =
            realloc((*res)->children, (i + 2) * sizeof(struct ast *));
        if (!(*res)->children)
            exit(1);

        (*res)->children[i + 1] = NULL;
        if (parse_case_item(&((*res)->children[i]), lexer) != PARSER_OK)
            return PARSER_UNEXPECTED_TOKEN;

        i++;
    }
    if (peek_token(lexer)->type == TOKEN_OPERATOR
        && !strcmp(";;", peek_token(lexer)->value))
        token_free(eat_token(lexer));

    while (peek_token(lexer)->type == TOKEN_NEWLINE)
        token_free(eat_token(lexer));
    return PARSER_OK;
}
