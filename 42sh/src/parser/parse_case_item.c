#include "parse_case_item.h"

#include <string.h>

#include "parse_compound_list.h"
#include "parser.h"

bool first_case_item(struct token *token)
{
    return (token->type == TOKEN_LPAR || token->type == TOKEN_WORD);
}

static void init_ast(struct ast **res, struct lexer *lexer, size_t i)
{
    (*res)->children[i] = new_ast(AST_WORD);
    (*res)->children[i]->value = strdup(peek_token(lexer)->value);
    (*res)->children[i + 1] = NULL;
}

enum parser_status parse_case_item(struct ast **res, struct lexer *lexer)
{
    if (peek_token(lexer)->type == TOKEN_LPAR)
        token_free(eat_token(lexer));
    if (peek_token(lexer)->type != TOKEN_WORD)
        return PARSER_UNEXPECTED_TOKEN;
    (*res) = new_ast(AST_CASE_ITEM);

    (*res)->children = calloc(2, sizeof(struct ast *));
    if (!(*res)->children)
        exit(1);
    init_ast(res, lexer, 0);
    token_free(eat_token(lexer));

    size_t i = 1;
    while (true)
    {
        if (peek_token(lexer)->type == TOKEN_RPAR)
            break;

        if (peek_token(lexer)->type != TOKEN_OPERATOR
            || strcmp(peek_token(lexer)->value, "|"))
            return PARSER_UNEXPECTED_TOKEN;

        token_free(eat_token(lexer));
        if (peek_token(lexer)->type != TOKEN_WORD)
            return PARSER_UNEXPECTED_TOKEN;

        (*res)->children =
            realloc((*res)->children, (i + 2) * sizeof(struct ast *));
        if (!(*res)->children)
            exit(1);
        init_ast(res, lexer, i++);
        token_free(eat_token(lexer));
    }
    if (peek_token(lexer)->type != TOKEN_RPAR)
        return PARSER_UNEXPECTED_TOKEN;
    token_free(eat_token(lexer));

    while (peek_token(lexer)->type == TOKEN_NEWLINE)
        token_free(eat_token(lexer));

    if (first_compound_list(peek_token(lexer)))
    {
        (*res)->children =
            realloc((*res)->children, (i + 2) * sizeof(struct ast *));
        if (!(*res)->children)
            exit(1);
        (*res)->children[i + 1] = NULL;

        return parse_compound_list(&((*res)->children[i]), lexer);
    }
    return PARSER_OK;
}
