#define _POSIX_C_SOURCE 200809L

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int replace_line(const char *file_in, const char *file_out, const char *content,
                 size_t n)
{
    FILE *fi = fopen(file_in, "r");
    FILE *fo = fopen(file_out, "w");

    if (!fi || !fo)
        return -1;
    char *lineptr = NULL;
    size_t nb_bytes = 0;
    while (n > 0 && (getline(&lineptr, &nb_bytes, fi)) != -1)
    {
        fputs(lineptr, fo);
        n--;
    }
    if (n == 0)
    {
        fputs(content, fo);
        getline(&lineptr, &nb_bytes, fi);
        while ((getline(&lineptr, &nb_bytes, fi)) != -1)
        {
            fputs(lineptr, fo);
        }
    }
    else
    {
        if (lineptr)
            free(lineptr);
        fclose(fi);
        fclose(fo);
        return 1;
    }
    if (lineptr)
        free(lineptr);
    fclose(fi);
    fclose(fo);
    return 0;
}

int main(void)
{
    replace_line("file_in", "file_out", "Replace the 3rd\n", 2);
}
