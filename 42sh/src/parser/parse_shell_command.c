#include "parse_shell_command.h"

#include "parse_case.h"
#include "parse_compound_list.h"
#include "parse_for.h"
#include "parse_if.h"
#include "parse_until.h"
#include "parse_while.h"

bool first_shell_command(struct token *token)
{
    return (first_if(token) || first_while(token) || first_until(token)
            || first_for(token) || first_case(token)
            || token->type == TOKEN_LBRACE || token->type == TOKEN_LPAR);
}

enum parser_status call_for_command_block(struct ast **res, struct lexer *lexer)
{
    (*res)->children[0] = new_ast(AST_COMMAND_BLOCK);

    (*res)->children[0]->children = calloc(2, sizeof(struct ast *));
    if (!(*res)->children[0]->children)
        exit(1);

    token_free(eat_token(lexer));

    if (parse_compound_list(&((*res)->children[0]->children[0]), lexer)
        != PARSER_OK)
        return PARSER_UNEXPECTED_TOKEN;

    if (peek_token(lexer)->type != TOKEN_RBRACE)
        return PARSER_UNEXPECTED_TOKEN;

    token_free(eat_token(lexer));

    return PARSER_OK;
}

enum parser_status call_for_subshell(struct ast **res, struct lexer *lexer)
{
    (*res)->children[0] = new_ast(AST_SUBSHELL);

    (*res)->children[0]->children = calloc(2, sizeof(struct ast *));
    if (!(*res)->children[0]->children)
        exit(1);

    token_free(eat_token(lexer));

    if (parse_compound_list(&((*res)->children[0]->children[0]), lexer)
        != PARSER_OK)
        return PARSER_UNEXPECTED_TOKEN;

    if (peek_token(lexer)->type != TOKEN_RPAR)
        return PARSER_UNEXPECTED_TOKEN;

    token_free(eat_token(lexer));

    return PARSER_OK;
}

enum parser_status parse_shell_command(struct ast **res, struct lexer *lexer)
{
    struct token *current_token = peek_token(lexer);

    if (first_shell_command(current_token))
    {
        (*res) = new_ast(AST_SHELL_COMMAND);

        (*res)->children = calloc(2, sizeof(struct ast *));
        if (!(*res)->children)
            exit(1);

        (*res)->children[1] = NULL;
        if (current_token->type == TOKEN_LBRACE)
        {
            if (call_for_command_block(res, lexer) != PARSER_OK)
                return PARSER_UNEXPECTED_TOKEN;
        }
        else if (current_token->type == TOKEN_LPAR)
        {
            if (call_for_subshell(res, lexer) != PARSER_OK)
                return PARSER_UNEXPECTED_TOKEN;
        }
        else if (first_if(current_token))
        {
            if (parse_if(&((*res)->children[0]), lexer) != PARSER_OK)
                return PARSER_UNEXPECTED_TOKEN;
        }
        else if (first_while(current_token))
        {
            if (parse_while(&((*res)->children[0]), lexer) != PARSER_OK)
                return PARSER_UNEXPECTED_TOKEN;
        }
        else if (first_until(current_token))
        {
            if (parse_until(&((*res)->children[0]), lexer) != PARSER_OK)
                return PARSER_UNEXPECTED_TOKEN;
        }
        else if (first_for(current_token))
        {
            if (parse_for(&((*res)->children[0]), lexer) != PARSER_OK)
                return PARSER_UNEXPECTED_TOKEN;
        }
        else if (first_case(current_token))
        {
            if (parse_case(&((*res)->children[0]), lexer) != PARSER_OK)
                return PARSER_UNEXPECTED_TOKEN;
        }

        return PARSER_OK;
    }
    return PARSER_UNEXPECTED_TOKEN;
}
