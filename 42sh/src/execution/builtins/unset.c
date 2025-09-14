#define _POSIX_C_SOURCE 200809L

#include "unset.h"

#include <stdio.h>
#include <stdlib.h>

#include "../../expansion/variables.h"
#include "../../options/verbose.h"
#include "../../utils/hash_map_funcdec/hash_map_funcdec.h"

extern struct hash_map_funcdec *hash_map_funcdec;

static int parse_options(char **argv, int *f_o, int *v_o)
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
            case 'f':
                *f_o = 1;
                *v_o = 0;
                break;
            case 'v':
                *v_o = 1;
                break;
            default:
                return -1;
            }
            j++;
        }

        i++;
    }

    return i;
}

int command_unset(struct command *cmd)
{
    int f_o = 0;
    int v_o = 1;

    int nb_option = parse_options(cmd->command_line, &f_o, &v_o);

    if (nb_option == -1)
    {
        fprintf(stderr, "unset: bad option\n");
        return 2;
    }

    int i = nb_option;
    if (f_o == 1 && v_o == 1)
    {
        fprintf(
            stderr,
            "unset: cannot simultaneously unset a function and a variable\n");
        return 1;
    }
    if (cmd->nb_param <= i)
    {
        fprintf(stderr, "unset: no names given\n");
        return 1;
    }
    while (cmd->command_line[i])
    {
        if (f_o == 1)
        {
            hash_map_funcdec_remove(hash_map_funcdec, cmd->command_line[i]);
        }
        else if (v_o == 1)
        {
            char *env_val = getenv(cmd->command_line[i]);
            if (env_val == NULL)
                remove_var(cmd->command_line[i]);
            else
            {
                if (unsetenv(cmd->command_line[i]) != 0)
                {
                    fprintf(stderr, "unsetenv: unsetenv failed\n");
                    return 1;
                }
            }
        }
        i++;
    }

    return 0;
}
