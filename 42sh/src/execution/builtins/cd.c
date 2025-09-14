#define _POSIX_C_SOURCE 200112L

#include "cd.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int command_cd(struct command *cmd)
{
    if (cmd->nb_param > 3)
    {
        fprintf(stderr, "cd: too many arguments\n");
        return 1;
    }
    char *newdir = NULL;
    if (cmd->nb_param == 2 || strcmp(cmd->command_line[1], "~") == 0)
    {
        if (getenv("HOME") == NULL)
        {
            newdir = ".";
        }
        else
        {
            newdir = getenv("HOME");
        }
    }
    else if (strcmp(cmd->command_line[1], "-") == 0)
    {
        newdir = getenv("OLDPWD");
        if (newdir == NULL)
        {
            fprintf(stderr, "cd: OLDPWD not set\n");
            return 1;
        }
        puts(newdir);
    }
    else
    {
        newdir = cmd->command_line[1];
    }

    char olddir[4096];
    if (getcwd(olddir, 4096) == NULL)
    {
        fprintf(stderr, "cd: error with getcwd");
        return 1;
    }
    setenv("OLDPWD", olddir, 1);

    if (chdir(newdir) == -1)
    {
        fprintf(stderr, "cd: %s: no such file or directory\n", newdir);
        return 1;
    }

    setenv("PWD", newdir, 1);

    return 0;
}
