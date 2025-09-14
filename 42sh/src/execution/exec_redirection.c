#define _POSIX_C_SOURCE 200809L

#include "exec_redirection.h"

#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "../options/verbose.h"
#include "exec_ionumber.h"
#include "exec_word.h"

static struct redirection_data *RD = NULL;

static struct redirection_data *init_redirection_data(void)
{
    struct redirection_data *rd = malloc(sizeof(struct redirection_data));
    if (rd == NULL)
    {
        exit(1);
    }
    rd->next = NULL;
    return rd;
}

static void push_redirection_datas(struct redirection_data **RD, int stream_dup,
                                   int target_stream)
{
    if (!*RD)
    {
        (*RD) = init_redirection_data();
        (*RD)->next = NULL;
        (*RD)->stream_dup = stream_dup;
        (*RD)->target_stream = target_stream;
        return;
    }

    struct redirection_data *cur = *RD;

    while (cur->next != NULL)
    {
        cur = cur->next;
    }
    cur->next = init_redirection_data();
    cur->next->stream_dup = stream_dup;
    cur->next->target_stream = target_stream;
    cur->next->next = NULL;
}

void redirect(void)
{
    verbose("reversing redirection\n");
    struct redirection_data *tmp = NULL;
    while (RD != NULL)
    {
        dup2(RD->stream_dup, RD->target_stream);
        close(RD->stream_dup);

        tmp = RD->next;
        free(RD);
        RD = tmp;
    }
}

static int exec_redirection(int ionumber, char *redirection_type,
                            char *filename)
{
    verbose("executing_redirection");
    int stream_dup = -1;
    int fd = -1;
    int flags = -1;

    if (redirection_type[0] == '<')
    {
        ionumber = (ionumber == -1) ? fileno(stdin) : ionumber;
        if (redirection_type[1] == '\0')
        {
            flags = O_RDONLY;
        }
        else if (redirection_type[1] == '&')
        {
            if (strcmp(filename, "-") == 0)
            {
                return close(ionumber);
            }
        }
        else if (redirection_type[1] == '>')
        {
            flags = O_CREAT | O_TRUNC | O_RDWR;
        }
    }
    else if (redirection_type[0] == '>')
    {
        ionumber = (ionumber == -1) ? fileno(stdout) : ionumber;
        if (redirection_type[1] == '>')
        {
            flags = O_WRONLY | O_CREAT | O_APPEND;
        }
        else if (redirection_type[1] == '&')
        {
            if (strcmp(filename, "-") == 0)
            {
                if (close(ionumber) == -1)
                {
                    return -2;
                }
            }
        }
        else if (redirection_type[1] == '|' || redirection_type[1] == '\0')
        {
            flags = O_WRONLY | O_CREAT | O_TRUNC;
        }
    }

    stream_dup = dup(ionumber);
    fd = redirection_type[1] == '&' ? atoi(filename)
                                    : open(filename, flags, 0644);
    if (fd == -1)
    {
        redirect();
        fprintf(stderr, "42sh: %s: No such file or directory\n", filename);
        return -2;
    }
    if (dup2(fd, ionumber) == -1)
    {
        redirect();
        fprintf(stderr, "42sh: %s: No such file or directory\n", filename);
        return -2;
    }
    close(fd);
    push_redirection_datas(&RD, stream_dup, ionumber);
    return 0;
}

int visit_redirection(struct ast *ast)
{
    verbose("Visiting \033[1;37mredirection\033[0;37m:\n");

    int ionumber = -1;
    char *filename = NULL;

    if (ast->children[1] != NULL)
    {
        ionumber = visit_ionumber(ast->children[0]);
        filename = visit_word(ast->children[1]);
    }
    else
    {
        filename = visit_word(ast->children[0]);
    }

    int res = exec_redirection(ionumber, ast->value, filename);
    free_word(filename);
    return res;
}
