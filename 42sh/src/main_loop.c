#define _POSIX_C_SOURCE 200809L

#include "main_loop.h"

#include <stdio.h>
#include <unistd.h>

#include "ast/ast.h"
#include "execution/builtins/exit.h"
#include "execution/exec_list.h"
#include "expansion/expansion.h"
#include "expansion/variables.h"
#include "lexer/token.h"
#include "options/pretty_printer.h"
#include "options/verbose.h"
#include "parser/parse_input.h"
#include "parser/parser.h"

void set_specials_variables(void)
{
    struct special_var current_var = { .key = "?", .value = "0" };
    modify_special_var(&current_var);

    current_var.key = "#";
    modify_special_var(&current_var);

    int pid = getpid();
    int size = snprintf(NULL, 0, "%d", pid);
    char *to_str = calloc(size + 1, sizeof(char));
    sprintf(to_str, "%d", pid);

    current_var.key = "$";
    current_var.value = to_str;
    modify_special_var(&current_var);
    free(to_str);
}

int parse_execute_loop(struct lexer *lexer)
{
    int return_value = atoi(get_special_var("?"));
    struct ast *res;
    do
    {
        if (parse_input(&res, lexer) == PARSER_OK)
        {
            if (!res)
                continue;
            if (res->type == AST_EOF)
            {
                free_ast(res);
                break;
            }
            verbose("\n\033[1;32mParsing succeeded.\033[0;37m");
            verbose("\n\033[1;32mAst built.\n\n\033[0;37m");
            pretty_print(res);
            verbose("\n");
            return_value = visit_list(res);
            free_ast(res);

            if (is_exit_found())
            {
                return_value = get_exit_value();
                break;
            }
        }
        else
        {
            verbose("\n\033[1;31mParsing Error.\n\033[0;37m");
            fprintf(stderr, "42sh: syntax error near '%s'\n",
                    lexer->next_token->value);

            while (peek_token(lexer)->type != TOKEN_EOF
                   && peek_token(lexer)->type != TOKEN_NEWLINE)
                token_free(eat_token(lexer));
            return_value = 2;
        }
    } while (peek_token(lexer)->type != TOKEN_EOF);

    verbose("******************************************************************"
            "*\n");
    verbose("******************************************************************"
            "*\n");

    token_free(lexer->next_token);

    return return_value;
}
