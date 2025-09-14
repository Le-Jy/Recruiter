#include <stdio.h>

int my_isspace(char c)
{
    if (c == ' ')
        return 1;
    else if (c == '\t')
        return 1;
    else if (c == '\n')
        return 1;
    return 0;
}

int count_words(const char *file_in)
{
    FILE *fi = fopen(file_in, "r");
    if (!fi)
        return -1;
    int c = 0;
    int space_before = 1;
    int counter = 0;
    while ((c = fgetc(fi)) > -1)
    {
        while (my_isspace(c))
        {
            c = fgetc(fi);
            space_before = 1;
            if (c == -1)
                return counter;
        }
        if (!my_isspace(c) && c != -1 && space_before)
        {
            counter++;
            space_before = 0;
        }
    }
    fclose(fi);
    return counter;
}
