#include "exit.h"

#include <stdio.h>
#include <stdlib.h>

#include "../../expansion/variables.h"

static int exit_found = 0;

static int exit_value = 1;

void command_exit(struct command *cmd)
{
    exit_found = 1;
    if (cmd->nb_param > 3)
    {
        fprintf(stderr, "exit: too many arguments\n");
    }
    if (cmd->nb_param == 3)
    {
        exit_value = atoi(cmd->command_line[1]);
    }
    else
    {
        exit_value = atoi(get_special_var("?"));
    }
}

int is_exit_found(void)
{
    return exit_found;
}

int get_exit_value(void)
{
    return exit_value;
}
