#define _POSIX_C_SOURCE 200112L

#include "export.h"

#include <stdlib.h>
#include <string.h>

int command_export(struct command *cmd)
{
    char *value = strstr(cmd->command_line[1], "=");
    if (value)
    {
        *value = '\0';
        return setenv(cmd->command_line[1], value + 1, 1);
    }
    else
    {
        return setenv(cmd->command_line[1], "", 1);
    }
}
