#include "exec_pipeline.h"

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include "../expansion/variables.h"
#include "../options/verbose.h"
#include "../utils/itoa/itoa.h"
#include "exec_command.h"
#include "exec_not.h"

int get_return_value(int initial_return_value, int not )
{
    int return_value =
        not ? visit_not(initial_return_value) : initial_return_value;

    // char **val = calloc(2, sizeof(char *));
    char *val = calloc(1, 5 * sizeof(char));
    verbose("return value after not : %d\n", return_value);
    itoa(return_value, val);
    struct special_var current_var = { .key = "?", .value = val };
    modify_special_var(&current_var);
    free(val);

    return return_value;
}

int visit_pipeline(struct ast *ast)
{
    int not = 0;
    struct ast **child = ast->children;
    if ((*child)->type == AST_NOT)
    {
        verbose("! detected\n");
        not = 1;
        child++;
    }

    int return_value = 0;
    if (*(child + 1) == NULL)
    {
        return_value = visit_command(*child);
        return get_return_value(return_value, not );
    }

    pid_t pid;
    int fd[2];
    int fd_in = 0;

    for (; *child != NULL; child++)
    {
        if (pipe(fd) == -1)
        {
            errx(1, "error with dup2");
        }
        pid = fork();
        if (pid == -1)
        {
            errx(1, "error with fork");
        }
        else if (pid == 0)
        {
            close(fd[0]);
            if (dup2(fd_in, STDIN_FILENO) == -1)
            {
                errx(1, "error with dup2");
            }
            if (*(child + 1) != NULL)
            {
                if (dup2(fd[1], STDOUT_FILENO) == -1)
                {
                    errx(1, "error with dup2");
                }
            }
            return_value = visit_command(*child);
            exit(return_value);
        }
        else
        {
            waitpid(pid, &return_value, 0);
            close(fd[1]);
            fd_in = fd[0];
        }
    }

    return get_return_value(return_value, not );
}
