#include <stddef.h>
#include <stdio.h>

int reverse_content(const char *file_in, const char *file_out)
{
    FILE *fi = fopen(file_in, "r");
    FILE *fo = fopen(file_out, "w");
    if (!fi || !fo)
        return -1;
    long back = 1;
    char c = 0;
    fseek(fi, -back, SEEK_END);
    while ((c = fgetc(fi)) > 0)
    {
        fputc(c, fo);
        back++;
        if (fseek(fi, -back, SEEK_END) == -1)
            break;
    }
    fclose(fo);
    fclose(fi);
    return 0;
}
