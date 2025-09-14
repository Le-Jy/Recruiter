#include <stdio.h>

int append_file(const char *file_in, const char *content)
{
    FILE *file_in_open = fopen(file_in, "a");
    if (!file_in_open)
        return -1;
    if (fprintf(file_in_open, "%s", content) < 0)
        return -1;
    fclose(file_in_open);
    return 0;
}
