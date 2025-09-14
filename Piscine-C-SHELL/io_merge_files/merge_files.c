#define _POSIX_C_SOURCE 200809L

#include <stdio.h>

int merge_files(const char *file_1, const char *file_2)
{
    FILE *fp_file_1 = fopen(file_1, "a");
    if (!fp_file_1)
        return -1;
    FILE *fp_file_2 = fopen(file_2, "r");
    if (!fp_file_2)
        return -1;
    char c = fgetc(fp_file_2);
    if (c < 0)
    {
        fclose(fp_file_1);
        fclose(fp_file_2);
        return 0;
    }
    int w = fputc(c, fp_file_1);
    if (w < 0)
    {
        fclose(fp_file_2);
        fclose(fp_file_1);
        return -1;
    }
    while (c >= 0)
    {
        c = fgetc(fp_file_2);
        if (c < 0)
            break;
        w = fputc(c, fp_file_1);
        if (w < 0)
        {
            fclose(fp_file_1);
            fclose(fp_file_2);
            return -1;
        }
    }
    fclose(fp_file_1);
    fclose(fp_file_2);
    return 0;
}
