#include "echo.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../options/verbose.h"

static int parse_options(char **argv, int *n_o, int *e_o, int *E_o)
{
    int i = 1;
    while (argv[i] && argv[i][0] == '-')
    {
        int j = 1;
        char option;
        while ((option = argv[i][j]) != '\0')
        {
            verbose("option = %s\n", option);
            switch (option)
            {
            case 'n':
                *n_o = 1;
                break;
            case 'e':
                *e_o = 1;
                *E_o = 0;
                break;
            case 'E':
                *E_o = 1;
                break;
            default:
                return i;
            }
            j++;
        }

        i++;
    }

    return i;
}

int command_echo(char **argv)
{
    int n_o = 0;
    int e_o = 0;
    int E_o = 1;

    int nb_option = parse_options(argv, &n_o, &e_o, &E_o);

    if (argv[nb_option] == NULL)
    {
        if (n_o == 0)
        {
            printf("\n");
        }
        return 0;
    }
    int i = nb_option;
    verbose("i = %d\n", i);
    for (; argv[i]; i++)
    {
        if (i != nb_option)
            printf(" ");

        for (int j = 0; argv[i][j]; j++)
        {
            if (e_o == 1 && E_o == 0 && argv[i][j] == '\\')
            {
                if (argv[i][j + 1] && argv[i][j + 1] == 'n')
                {
                    putchar('\n');
                    j++;
                }
                else if (argv[i][j + 1] && argv[i][j + 1] == 't')
                {
                    putchar('\t');
                    j++;
                }
                else if (argv[i][j + 1] && argv[i][j + 1] == '\\')
                {
                    putchar('\\');
                    j++;
                }
                else
                {
                    putchar('\\');
                }
            }
            else
            {
                putchar(argv[i][j]);
            }
        }
    }
    if (n_o == 0)
    {
        printf("\n");
    }

    return 0;
}
