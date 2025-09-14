#define _POSIX_C_SOURCE 200809L

#include "io.h"

#include <stdlib.h>
#include <string.h>

#include "../options/pretty_printer.h"
#include "../options/verbose.h"

#define handle_error(msg)                                                      \
    do                                                                         \
    {                                                                          \
        perror(msg);                                                           \
        exit(2);                                                               \
    } while (0)

/**
 * @brief Return the file descriptor containing the string.
 *
 * @param script The string.
 * @return The newly created file descriptor.
 */
FILE *get_stream_from_string(const char *script)
{
    FILE *file = NULL;

    if ((file = fmemopen((void *)script, strlen(script) + 1, "r")) == NULL)
    {
        handle_error("fmemopen");
    }

    fprintf(file, "%s", script);

    return file;
}

/**
 * @brief Return the file descriptor of the file.
 *
 * @param filename The name of the file.
 * @return The newly created file descriptor.
 */
static FILE *get_stream_from_file(const char *filename)
{
    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {
        handle_error("fopen");
    }

    return file;
}

int io_peek(FILE *file)
{
    int current = fgetc(file);
    ungetc(current, file);

    fflush(file);

    verbose("\033[0;37mpeek: \033[1;34m%c\n\033[0;37m", current);

    return current;
}

int io_pop(FILE *file)
{
    int current = fgetc(file);

    fflush(file);

    verbose("\033[0;37mpop: \033[1;34m%c\n\033[0;37m", current);

    return current;
}

FILE *get_input_stream(int argc, char *argv[])
{
    FILE *fd_stream = NULL;

    if (argc >= 2)
    {
        int i = 1;
        while (i < argc && argv[i][0] == '-')
        {
            if (strcmp(argv[i], "-c") == 0)
            {
                if (argc == i + 1)
                {
                    fprintf(stderr, "No script was given after -c option.\n");
                    fprintf(stderr,
                            "Usage: %s [OPTIONS] [SCRIPT] [ARGUMENTS ...]\n",
                            argv[0]);
                    return NULL;
                }
                fd_stream = get_stream_from_string(argv[i + 1]);
            }
            else if (strcmp(argv[i], "--verbose") == 0)
            {
                set_verbose(1);
            }
            else if (strcmp(argv[i], "--pretty-print") == 0)
            {
                set_pretty_print(1);
            }
            else
            {
                fprintf(stderr, "Invalid option : %s\n", argv[i]);
                fprintf(stderr,
                        "Usage: %s [OPTIONS] [SCRIPT] [ARGUMENTS ...]\n",
                        argv[0]);
                return NULL;
            }
            i++;
        }
        if (argc > i && fd_stream == NULL)
        {
            fd_stream = get_stream_from_file(argv[i]);
        }
    }
    if (fd_stream == NULL)
    {
        fd_stream = stdin;
    }

    verbose("******************************************************************"
            "*\n");
    verbose("******************************************************************"
            "*\n");
    verbose("\033[1;37mGetting stream from fd: %d\n\n\033[0;37m",
            fileno(fd_stream));

    return fd_stream;
}
