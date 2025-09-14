#include "exec_simple_command.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "../expansion/variables.h"
#include "../options/verbose.h"
#include "../utils/hash_map_funcdec/hash_map_funcdec.h"
#include "../utils/itoa/itoa.h"
#include "builtins/cd.h"
#include "builtins/dot.h"
#include "builtins/echo.h"
#include "builtins/exit.h"
#include "builtins/export.h"
#include "builtins/false.h"
#include "builtins/loop_interupt.h"
#include "builtins/true.h"
#include "builtins/unset.h"
#include "exec_element.h"
#include "exec_prefix.h"
#include "exec_shell_command.h"
#include "exec_word.h"

extern struct hash_map_funcdec *hash_map_funcdec;

/**
 * @brief Creates a new command structure and initializes its fields.
 *
 * @return A pointer to the new command structure.
 * @note The caller is responsible for freeing the allocated memory using
 * free_command().
 */
static struct command *create_command(void)
{
    struct command *cmd = calloc(1, sizeof(struct command));
    if (cmd == NULL)
    {
        exit(EXIT_FAILURE);
    }
    cmd->nb_param = 0;
    cmd->max_param = 1;
    cmd->command_line = calloc(cmd->max_param, sizeof(char *));
    return cmd;
}

static void end_param(struct command *cmd, char *param)
{
    cmd->nb_param++;
    if (cmd->nb_param > cmd->max_param)
    {
        cmd->max_param *= 2;
        cmd->command_line =
            realloc(cmd->command_line, cmd->max_param * sizeof(char *));
    }
    cmd->command_line[cmd->nb_param - 1] = param;
}

void free_command(struct command *cmd)
{
    int i = 0;
    while (cmd->command_line[i] != NULL)
    {
        free_word(cmd->command_line[i]);
        i++;
    }
    free(cmd->command_line);
    free(cmd);
}

/**
 * @brief Adds a parameter to the command structure.
 *
 * This function adds a parameter to the command structure.
 * If the number of parameters exceeds the maximum allocated, it dynamically
 * reallocates the memory.
 *
 * @param cmd Pointer to the command structure.
 * @param param Pointer to the parameter to be added.
 */
static void add_param(struct command *cmd, char *param)
{
    if (param)
    {
        cmd->nb_param++;
        if (cmd->nb_param > cmd->max_param)
        {
            cmd->max_param *= 2;
            cmd->command_line =
                realloc(cmd->command_line, cmd->max_param * sizeof(char *));
        }
        cmd->command_line[cmd->nb_param - 1] = param;
    }
}

static void set_func_variable(struct command *cmd)
{
    int i = 1;

    verbose("setting function variable\n");

    // set $1 ... $n
    while (cmd->command_line[i])
    {
        char *val = cmd->command_line[i];
        char *key = calloc(i + 1, sizeof(char));
        itoa(i, key);
        struct special_var current_var = { .key = key, .value = val };
        add_special_var(&current_var);
        free(key);

        i++;
    }

    // set $#
    char *value = calloc(i + 1, sizeof(char));
    itoa(i - 1, value);
    struct special_var current_var = { .key = "#", .value = value };
    add_special_var(&current_var);
    free(value);
}

static void unset_func_variable(struct command *cmd)
{
    int i = 1;

    verbose("setting function variable\n");

    // set $1 ... $n
    while (cmd->command_line[i])
    {
        char **val = calloc(2, sizeof(char *));
        val[0] = cmd->command_line[i];
        char *key = calloc(i + 1, sizeof(char));
        itoa(i, key);
        struct special_var current_var = { .key = key, .value = NULL };
        add_special_var(&current_var);
        free(key);
        free(val);

        i++;
    }

    char *val = "0";
    struct special_var current_var = { .key = "#", .value = val };
    add_special_var(&current_var);
}

int visit_simple_command(struct ast *ast, struct command *cmd)
{
    verbose("Visiting \033[1;37msimple_command\033[0;37m:\n");
    char *elem;
    int return_code = 0;
    for (struct ast **child = ast->children; *child != NULL; ++child)
    {
        switch ((*child)->type)
        {
        case AST_PREFIX:
            return_code = visit_prefix(*child);
            break;
        case AST_WORD:
            add_param(cmd, visit_word(*child));
            break;
        case AST_ELEMENT:
            elem = visit_element(*child, &return_code);
            add_param(cmd, elem);
            if (return_code == -2)
            {
                verbose("redirection error detected\n");
                return 1;
            }
            break;
        default:
            return 1;
        }
        verbose("\n");
    }

    return return_code;
}

/**
 * @brief Executes a command using fork and execvp.
 *
 * @param cmd Pointer to the command structure containing the command to be
 * executed.
 * @return The exit status of the executed command.
 */
static int exec_fork(struct command *cmd)
{
    int pid = fork();
    if (pid == 0)
    {
        execvp(cmd->command_line[0], cmd->command_line);
        exit(127);
    }
    else
    {
        int exit_status = 0;
        int status = 0;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
        {
            exit_status = WEXITSTATUS(status);
            if (exit_status == 127)
            {
                fprintf(stderr, "%s: exec failed\n", cmd->command_line[0]);
                return exit_status;
            }
        }

        fflush(stdout);

        return exit_status;
    }
}

/**
 * @brief Executes one of our built-in command.
 *
 * @param cmd Pointer to the command structure containing the command to be
 * executed.
 * @return 0 if the built-in command is executed successfully, 1 if the command
 * is not a recognized built-in.
 */
static int exec_builtin(struct command *cmd)
{
    if (strcmp(cmd->command_line[0], "echo") == 0)
    {
        return command_echo(cmd->command_line);
    }
    else if (strcmp(cmd->command_line[0], "true") == 0)
    {
        return command_true();
    }
    else if (strcmp(cmd->command_line[0], "false") == 0)
    {
        return command_false();
    }
    else if (strcmp(cmd->command_line[0], "exit") == 0)
    {
        command_exit(cmd);
    }
    else if (strcmp(cmd->command_line[0], "cd") == 0)
    {
        return command_cd(cmd);
    }
    else if (strcmp(cmd->command_line[0], "export") == 0)
    {
        return command_export(cmd);
    }
    else if (strcmp(cmd->command_line[0], "break") == 0)
    {
        return command_break(cmd);
    }
    else if (strcmp(cmd->command_line[0], "continue") == 0)
    {
        return command_continue(cmd);
    }
    else if (strcmp(cmd->command_line[0], ".") == 0)
    {
        return command_dot(cmd);
    }
    else if (strcmp(cmd->command_line[0], "unset") == 0)
    {
        return command_unset(cmd);
    }
    return 1;
}

static int is_builtin(struct command *cmd)
{
    int res = 0;
    if (cmd->command_line[0] != NULL
        && (strcmp(cmd->command_line[0], "true") == 0
            || strcmp(cmd->command_line[0], "false") == 0
            || strcmp(cmd->command_line[0], "echo") == 0
            || strcmp(cmd->command_line[0], "exit") == 0
            || strcmp(cmd->command_line[0], "export") == 0
            || strcmp(cmd->command_line[0], "continue") == 0
            || strcmp(cmd->command_line[0], "break") == 0
            || strcmp(cmd->command_line[0], ".") == 0
            || strcmp(cmd->command_line[0], "unset") == 0
            || strcmp(cmd->command_line[0], "cd") == 0))
    {
        res = 1;
    }

    return res;
}

int exec_simple_command(struct ast *ast)
{
    if (is_exit_found())
    {
        return 1;
    }
    struct command *cmd = create_command();
    int returncode = visit_simple_command(ast, cmd);
    if (returncode != 0)
    {
        free_command(cmd);
        return returncode;
    }

    // Struct command cmd must be NULL terminated
    end_param(cmd, NULL);

    verbose("Executing command line: \"");
    for (int i = 0; cmd->command_line[i] != NULL; i++)
    {
        if (i != 0)
            verbose(" ");
        verbose("\033[0;32m%s\033[0;37m", cmd->command_line[i]);
    }
    verbose("\"\n");

    int return_value = 0;
    struct ast *func;
    if (cmd->command_line[0] != NULL
        && (func = hash_map_funcdec_get(hash_map_funcdec, cmd->command_line[0]))
            != NULL)
    {
        set_func_variable(cmd);
        return_value = visit_shell_command(func);
        unset_func_variable(cmd);
    }
    else if (is_builtin(cmd))
    {
        return_value = exec_builtin(cmd);
        fflush(stdout);
    }
    else if (cmd->command_line[0] != NULL)
    {
        return_value = exec_fork(cmd);
    }

    char *val = calloc(1, 5 * sizeof(char));
    itoa(return_value, val);
    struct special_var current_var = { .key = "?", .value = val };
    modify_special_var(&current_var);
    free(val);

    free_command(cmd);

    return return_value;
}
