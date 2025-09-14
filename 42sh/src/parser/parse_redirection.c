#include "parse_redirection.h"

#include <string.h>

static char *str_allowed_operators[] = { ">",  "<",  ">>", ">&",
                                         "<&", ">|", "<>", NULL };

static bool check_allowed_operators(char *value)
{
    for (size_t i = 0; str_allowed_operators[i]; i++)
    {
        if (!strcmp(str_allowed_operators[i], value))
            return true;
    }
    return false;
}

bool first_redirection(struct token *token)
{
    return (token->type == TOKEN_IONUMBER
            || (token->value && check_allowed_operators(token->value)));
}

enum parser_status parse_redirection(struct ast **res, struct lexer *lexer)
{
    (*res) = new_ast(AST_REDIRECTION);
    (*res)->children = calloc(3, sizeof(struct ast *));
    if (!(*res)->children)
        exit(1);

    size_t i = 0;
    struct token *current_token = eat_token(lexer);
    if (current_token->type == TOKEN_IONUMBER)
    {
        (*res)->children[i] = new_ast(AST_IONUMBER);
        (*res)->children[i++]->value = strdup(current_token->value);
        token_free(current_token);
        current_token = eat_token(lexer);
    }

    (*res)->value = strdup(current_token->value);
    token_free(current_token);

    if (peek_token(lexer)->type != TOKEN_WORD)
        return PARSER_UNEXPECTED_TOKEN;
    (*res)->children[i] = new_ast(AST_WORD);
    (*res)->children[i++]->value = strdup(peek_token(lexer)->value);
    (*res)->children[i] = NULL;

    token_free(eat_token(lexer));
    return PARSER_OK;
}
