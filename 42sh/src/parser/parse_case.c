#include "parse_case.h"

#include <string.h>

#include "parse_case_clause.h"
#include "parser.h"

bool first_case(struct token *token)
{
    return (token->type == TOKEN_CASE);
}

enum parser_status parse_case(struct ast **res, struct lexer *lexer)
{
    token_free(eat_token(lexer));
    if (peek_token(lexer)->type != TOKEN_WORD)
        return PARSER_UNEXPECTED_TOKEN;

    (*res) = new_ast(AST_CASE);

    (*res)->children = calloc(3, sizeof(struct ast *));
    if (!(*res)->children)
        exit(1);
    (*res)->children[0] = new_ast(AST_WORD);
    (*res)->children[0]->value = strdup(peek_token(lexer)->value);
    token_free(eat_token(lexer));
    while (peek_token(lexer)->type == TOKEN_NEWLINE)
        token_free(eat_token(lexer));
    if (peek_token(lexer)->type != TOKEN_IN)
        return PARSER_UNEXPECTED_TOKEN;
    token_free(eat_token(lexer));
    while (peek_token(lexer)->type == TOKEN_NEWLINE)
        token_free(eat_token(lexer));
    size_t i = 1;
    if (first_case_clause(peek_token(lexer)))
    {
        if (parse_case_clause(&((*res)->children[i]), lexer) != PARSER_OK)
            return PARSER_UNEXPECTED_TOKEN;
    }
    if (peek_token(lexer)->type != TOKEN_ESAC)
        return PARSER_UNEXPECTED_TOKEN;
    token_free(eat_token(lexer));
    return PARSER_OK;
}
