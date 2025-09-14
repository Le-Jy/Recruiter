#include "my_c_tail.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void stdintail(unsigned int n)
{
    int size = 0;
    int nb_lines = 0;
    char *buffer = malloc(sizeof(char) * 8);
    if (!buffer)
        return;
    while (read(STDIN_FILENO, buffer + size, 1))
    {
        if (buffer[size] == '\n' || nb_lines == 0)
            nb_lines++;
        size++;

        if (size % 8 == 0)
        {
            buffer = realloc(buffer, size + 8);
            if (!buffer)
                return;
        }
    }
    int end = size - 1;
    size_t count = 0;
    while (end >= 0 && (count < n || buffer[end] != '\n'))
    {
        if (buffer[end] == '\n')
            count++;
        end--;
    }
    if (end < -1)
    {
        free(buffer);
        return;
    }
    for (int i = end + 1; i < size; i++)
    {
        write(STDOUT_FILENO, buffer + i, 1);
    }
    free(buffer);
}
