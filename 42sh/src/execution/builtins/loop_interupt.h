#ifndef LOOP_INTERUPT_H
#define LOOP_INTERUPT_H

#include "../exec_simple_command.h"

struct interupt
{
    int break_count;
    int stop;
    int count_loop;
};

int command_break(struct command *cmd);

int command_continue(struct command *cmd);

#endif /* ! LOOP_INTERUPT_H */
