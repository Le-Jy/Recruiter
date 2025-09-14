#define _POSIX_C_SOURCE 200809L

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int count_lines(const char *file_out)
{
    FILE *fi = fopen(file_out, "r");
    char *lineptr = NULL;
    int lines = 0;
    size_t nb_bytes = 0;
    while (getline(&lineptr, &nb_bytes, fi) != -1)
        lines++;
    if (lineptr)
        free(lineptr);
    fclose(fi);
    return lines;
}

int insert_line(const char *file_in, const char *file_out, const char *content,
                size_t n)
{
    FILE *fi = fopen(file_in, "r");
    FILE *fo = fopen(file_out, "w");

    if (!fi || !fo)
        return -1;
    char *lineptr = NULL;
    int lines = 0;
    size_t nb_bytes = 0;
    while (n > 0 && (getline(&lineptr, &nb_bytes, fi)) != -1)
    {
        fputs(lineptr, fo);
        lines++;
        n--;
    }

    while (n > 0)
    {
        fputs("\n", fo);
        n--;
        lines++;
    }
    fputs(content, fo);
    while ((getline(&lineptr, &nb_bytes, fi)) != -1)
    {
        fputs(lineptr, fo);
        lines++;
    }
    if (lineptr)
        free(lineptr);
    fclose(fi);
    fclose(fo);
    return count_lines(file_out);
}
