#ifndef IO_H
#define IO_H

#include <stdio.h>

FILE *get_stream_from_string(const char *script);

/**
 * @brief Get the current char from file without moving the cursor.
 *
 * @param file The file descriptor.
 * @return The current char.
 */
int io_peek(FILE *file);

/**
 * @brief Get the current char from file and moves the cursor to the next char.
 *
 * @param file The file descriptor.
 * @return The current char.
 */
int io_pop(FILE *file);

/**
 * @brief Return the file descriptor corresponding to the input stream.
 * Detect the Verbose options and sets it to its right value if needed.
 *
 * @param argc Number of arguments.
 * @param argv Array of arguments.
 * @return The newly created file descriptor.
 */
FILE *get_input_stream(int argc, char *argv[]);

#endif /* ! IO_H */
