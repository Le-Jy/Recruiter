#include "pretty_printer.h"

#include <stdbool.h>
#include <stdio.h>

bool PRETTY_PRINTER = false;

static const char *ast_strings[] = { "List",
                                     "And_or",
                                     "Pipeline",
                                     "Command",
                                     "Simple_command",
                                     "Shell_command",
                                     "Fundec",
                                     "Redirection",
                                     "Prefix",
                                     "Element",
                                     "Compound_list",
                                     "For",
                                     "While",
                                     "Until",
                                     "Case",
                                     "Case_clause",
                                     "Case_item",
                                     "If",
                                     "Else",
                                     "Not",
                                     "And",
                                     "Or",
                                     "Command_block",
                                     "Sub_shell",
                                     "Eof",
                                     "Word",
                                     "Assignement_word",
                                     "IOnumber" };

void set_pretty_print(bool activate)
{
    PRETTY_PRINTER = activate;
}

static void print_ast(struct ast *ast, int nbspace)
{
    if (ast)
    {
        for (int i = 0; i < 4 * nbspace; i++)
        {
            printf(" ");
        }
        if (ast->type == AST_WORD)
        {
            printf(" %s\n", ast->value);
        }
        else
        {
            printf(" %s\n", ast_strings[ast->type]);
        }
        if (ast->children)
        {
            for (int i = 0; i < 4 * nbspace; i++)
            {
                printf(" ");
            }
            printf(" {\n");
            for (int i = 0; ast->children[i] != NULL; i++)
            {
                print_ast(ast->children[i], nbspace + 1);
            }
            for (int i = 0; i < 4 * nbspace; i++)
            {
                printf(" ");
            }
            printf(" }\n");
        }
    }
}

void pretty_print(struct ast *ast)
{
    if (PRETTY_PRINTER)
    {
        printf("Ast :\n");
        print_ast(ast, 0);
        printf("\n");
    }
}
