#define _POSIX_C_SOURCE 200809L

#include "expand_variable.h"

#include <ctype.h>
#include <linux/limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#include "../io/io.h"
#include "../lexer/lexer.h"
#include "../main_loop.h"
#include "expansion.h"
#include "variables.h"

struct var_delim
{
    char *start;
    char *end;
};

static bool is_single_special(char c)
{
    return (c == '@' || c == '*' || c == '?' || c == '$' || isdigit(c)
            || c == '#');
}

static bool is_valid(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
        || (c >= '0' && c <= '9') || (c == '_');
}

static void append_value(char *val, char **res)
{
    if (!val)
        return;

    *res = realloc(*res, strlen(*res) + strlen(val) + 2);
    if (!(*res))
        exit(1);
    strcat(*res, val);
}

static char *get_other_special(char *string)
{
    char *res;
    int value = -1;
    if (!strcmp("RANDOM", string))
        value = rand();
    else if (!strcmp("UID", string))
        value = getuid();

    if (value != -1)
    {
        int size = snprintf(NULL, 0, "%d", value);
        char *to_str = calloc(size + 1, sizeof(char));
        sprintf(to_str, "%d", value);

        res = to_str;
    }
    else
        return NULL;

    return res;
}

static char *get_env_var(char *string)
{
    char *val;
    if (!strcmp(string, "PWD"))
    {
        val = getcwd(NULL, 0);
        return val;
    }

    val = getenv(string);
    if (val)
        val = strdup(val);
    return val;
}

static void set_exit_status(int exit_status)
{
    int size = snprintf(NULL, 0, "%d", exit_status);
    char *to_str = calloc(size + 1, sizeof(char));
    sprintf(to_str, "%d", exit_status);

    struct special_var current_var = { .key = "?", .value = to_str };
    modify_special_var(&current_var);

    free(to_str);
}

static void clean_buffer(char *string)
{
    size_t len = strlen(string);
    while (len > 0 && string[len - 1] == '\n')
    {
        string[len - 1] = '\0';
        len--;
    }
}

static char *calls_in_subshell(char *command)
{
    FILE *fd = get_stream_from_string(command);

    int pipe_fds[2];
    if (pipe(pipe_fds) == -1)
        exit(EXIT_FAILURE);

    int pid = fork();

    if (pid == 0)
    {
        close(pipe_fds[0]);

        dup2(pipe_fds[1], STDOUT_FILENO);

        struct lexer *lexer = new_lexer(fd);
        int return_value = parse_execute_loop(lexer);
        free_lexer(lexer);

        close(pipe_fds[1]);

        exit(return_value);
    }
    else
    {
        close(pipe_fds[1]);

        int status = 0;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            set_exit_status(WEXITSTATUS(status));

        char *buffer = calloc(1024, sizeof(char));
        size_t size = 0;
        ssize_t nread;

        while ((nread = read(pipe_fds[0], buffer + size, 1024)) > 0)
        {
            size += nread;
            buffer = realloc(buffer, size + 1024);
        }

        if (nread == -1)
            exit(EXIT_FAILURE);

        buffer[size] = '\0';
        clean_buffer(buffer);

        close(pipe_fds[0]);

        fflush(stdout);
        fclose(fd);
        return buffer;
    }
}

static enum expansion_status par_sub_case(char *string, size_t *idx,
                                          struct var_delim *vd)
{
    vd->start = string + *idx;
    size_t nb_tomatch = 0;
    bool quoted = false;
    bool dquoted = false;
    while (quoted || dquoted || string[*idx] != ')' || nb_tomatch)
    {
        if (!quoted && !dquoted && string[*idx] == '(')
            nb_tomatch++;
        if (!quoted && !dquoted && nb_tomatch && string[*idx] == ')')
            nb_tomatch--;

        if (!quoted && string[*idx] == '\\')
        {
            (*idx) += 2;
            continue;
        }

        if (!dquoted && string[*idx] == '\'')
            quoted = !quoted;

        if (!quoted && string[*idx] == '\"')
            dquoted = !dquoted;

        (*idx)++;
    }

    if (string[*idx] != ')')
        return EXPAND_ERROR;

    vd->end = string + *idx;

    return EXPAND_OK;
}

static enum expansion_status quote_sub_case(char *string, size_t *idx,
                                            struct var_delim *vd)
{
    vd->start = string + *idx;
    bool quoted = false;
    bool dquoted = false;
    while (quoted || dquoted || string[*idx] != '`')
    {
        if (!quoted && string[*idx] == '\\')
        {
            (*idx) += 2;
            continue;
        }

        if (!dquoted && string[*idx] == '\'')
            quoted = !quoted;

        if (!quoted && string[*idx] == '\"')
            dquoted = !dquoted;

        (*idx)++;
    }

    if (string[*idx] != '`')
        return EXPAND_ERROR;

    vd->end = string + *idx;

    return EXPAND_OK;
}

static enum expansion_status get_variable_as_str(char *string, size_t *idx,
                                                 struct var_delim *vd,
                                                 bool *subshell)
{
    if (string[*idx] == '{')
    {
        (*idx)++;

        vd->start = string + *idx;
        while (is_valid(string[*idx]))
            (*idx)++;

        if (string[*idx] != '}')
            return EXPAND_ERROR;

        vd->end = string + *idx;
    }
    else if (string[*idx] == '(')
    {
        (*idx)++;
        if (par_sub_case(string, idx, vd) != EXPAND_OK)
            return EXPAND_ERROR;
        *subshell = true;
    }
    else if (string[*idx] == '`')
    {
        (*idx)++;
        if (quote_sub_case(string, idx, vd) != EXPAND_OK)
            return EXPAND_ERROR;
        *subshell = true;
    }
    else
    {
        vd->start = string + *idx;

        while (is_valid(string[*idx]))
            (*idx)++;

        vd->end = string + *idx;
    }

    return EXPAND_OK;
}

static enum expansion_status call_for_sub(char *string, size_t *idx, char **res,
                                          char *cpy)
{
    char *val;
    if (string[*idx] == '`')
    {
        (*idx)++;
        char *sub_res = calloc(1, sizeof(char));
        if (expand_word(cpy, &sub_res) != EXPAND_OK)
        {
            free(sub_res);
            return EXPAND_ERROR;
        }
        val = calls_in_subshell(sub_res);
        append_value(val, res);
        free(val);
        free(sub_res);
    }
    else
    {
        val = calls_in_subshell(cpy);
        char *new_val = escape_special_chars(val);
        append_value(new_val, res);
        free(val);
        free(new_val);
    }

    return EXPAND_OK;
}

enum expansion_status expand_variable(char *string, size_t *idx, char **res)
{
    char *val;
    bool subshell = false;

    if (is_single_special(string[*idx]))
    {
        char tmp[2];
        tmp[0] = string[*idx];
        tmp[1] = 0;

        val = get_special_var(tmp);
        append_value(val, res);

        (*idx)++;

        return EXPAND_OK;
    }

    struct var_delim vd;

    if (get_variable_as_str(string, idx, &vd, &subshell) == EXPAND_ERROR)
        return EXPAND_ERROR;

    char *start = vd.start;
    char *end = vd.end;

    size_t len = end - start;
    char *cpy = calloc(len + 1, sizeof(char));
    strncpy(cpy, string + *idx - len, len);

    if (string[*idx] == '}' || string[*idx] == ')')
        (*idx)++;

    if (subshell)
    {
        if (call_for_sub(string, idx, res, cpy) != EXPAND_OK)
        {
            free(cpy);
            return EXPAND_ERROR;
        }
    }
    else
    {
        val = get_special_var(cpy);
        if (val)
            append_value(val, res);
        else if ((val = get_var(cpy)))
            append_value(val, res);
        else if ((val = get_other_special(cpy)))
        {
            append_value(val, res);
            free(val);
        }
        else if ((val = get_env_var(cpy)))
        {
            append_value(val, res);
            free(val);
        }
    }

    free(cpy);

    return EXPAND_OK;
}
