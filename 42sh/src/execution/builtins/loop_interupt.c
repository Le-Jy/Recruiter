#include "loop_interupt.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

struct interupt interupt = { 0, 0, 0 };

static int min(int a, int b)
{
    if (a < b)
        return a;
    return b;
}

int command_break(struct command *cmd)
{
    int count = 1;
    if (cmd->command_line[1] != NULL)
    {
        for (int i = 0; cmd->command_line[1][i]; i++)
        {
            if (isdigit(cmd->command_line[1][i]) == 0)
            {
                fprintf(stderr, "break: %s: numeric argument required\n",
                        cmd->command_line[1]);
                return 128;
            }
        }
        count = atoi(cmd->command_line[1]);
        if (count < 0)
        {
            fprintf(stderr, "continue: argument is not positive: %d", count);
            return 1;
        }
    }
    interupt.break_count = min(count, interupt.count_loop) + 1;
    interupt.stop = 1;

    return 0;
}

int command_continue(struct command *cmd)
{
    int count = 0;
    if (cmd->command_line[1] != NULL)
    {
        for (int i = 0; cmd->command_line[1][i]; i++)
        {
            if (isdigit(cmd->command_line[1][i]) == 0)
            {
                fprintf(stderr, "continue: %s: numeric argument required\n",
                        cmd->command_line[1]);
                return 128;
            }
        }
        count = atoi(cmd->command_line[1]);
        if (count < 0)
        {
            fprintf(stderr, "continue: argument is not positive: %d", count);
            return 1;
        }
    }
    interupt.break_count = min(count, interupt.count_loop);
    interupt.stop = 1;

    return 0;
}
