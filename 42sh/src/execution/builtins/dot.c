#define _POSIX_C_SOURCE 200809L

#include "dot.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../../lexer/lexer.h"
#include "../../main_loop.h"

#define MAX_PATH_LENGTH 1024

char *find_file_in_path(const char *filename)
{
    char *path_env = getenv("PATH");
    if (path_env == NULL)
    {
        return NULL;
    }

    char *path_copy = strdup(path_env);
    if (path_copy == NULL)
    {
        perror("strdup");
        exit(EXIT_FAILURE);
    }

    char *path_token = strtok(path_copy, ":");
    while (path_token != NULL)
    {
        char file_path[MAX_PATH_LENGTH];
        snprintf(file_path, sizeof(file_path), "%s/%s", path_token, filename);

        if (access(file_path, F_OK) == 0)
        {
            free(path_copy);
            return strdup(file_path);
        }

        path_token = strtok(NULL, ":");
    }

    free(path_copy);
    return NULL;
}

int command_dot(struct command *cmd)
{
    char *filename = strdup(cmd->command_line[1]);

    if (strchr(filename, '/') != NULL)
    {
        if (access(filename, R_OK) == -1)
        {
            fprintf(stderr, "dot: file is not readable\n");
            free(filename);
            return 1;
        }
    }
    else
    {
        char *found_file = find_file_in_path(filename);
        if (found_file == NULL)
        {
            fprintf(stderr, "dot: file not found in PATH\n");
            free(filename);
            return 1;
        }
        free(filename);
        filename = found_file;
    }

    FILE *fd = fopen(filename, "r");
    if (fd == NULL)
    {
        perror("fopen");
        free(filename);
        return 1;
    }

    struct lexer *lexer = new_lexer(fd);
    if (!lexer)
    {
        free(filename);
        fclose(fd);
        return 1;
    }

    parse_execute_loop(lexer);

    free_lexer(lexer);
    free(filename);

    fclose(fd);

    return 0;
}
