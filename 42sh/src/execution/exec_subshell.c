#include "exec_subshell.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include "../expansion/variables.h"
#include "exec_compound_list.h"

int visit_subshell(struct ast *ast)
{
    int pid = fork();

    if (pid == 0)
    {
        int return_value = visit_compound_list(ast->children[0]);
        exit(return_value);
    }
    else
    {
        int status = 0;
        int exit_status = 0;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
        {
            exit_status = WEXITSTATUS(status);

            int size = snprintf(NULL, 0, "%d", exit_status);
            char *to_str = calloc(size + 1, sizeof(char));
            sprintf(to_str, "%d", exit_status);

            struct special_var current_var = { .key = "?", .value = to_str };
            modify_special_var(&current_var);

            free(to_str);
        }
        fflush(stdout);
        return exit_status;
    }
}
