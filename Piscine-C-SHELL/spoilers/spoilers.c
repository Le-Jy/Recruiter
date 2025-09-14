#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int last_elements(int fid, char *c)
{
    off_t back = 1;
    if (lseek(fid, -back, SEEK_END) == -1)
    {
        write(STDERR_FILENO, "File is not long enough\n", 24);
        return 1;
    }
    c++;
    int is_to_short = 1;
    int r = read(fid, c, 1);
    if (r < 0)
        return 1;
    back++;
    while (r)
    {
        if (!isspace(*c))
        {
            is_to_short++;
            if (is_to_short == 3)
            {
                return 0;
            }
            c--;
        }
        if (lseek(fid, -back, SEEK_END) == -1 && is_to_short)
        {
            write(STDERR_FILENO, "File is not long enough\n", 24);
            return 1;
        }
        r = read(fid, c, 1);
        if (r < 0)
            return 1;
        back++;
    }
    if (is_to_short)
        write(STDERR_FILENO, "File is not long enough\n", 24);
    return 1;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        write(STDERR_FILENO, "Invalid number of arguments\n", 28);
        return 1;
    }
    int fid = open(argv[1], O_RDONLY);
    if (fid < 0)
    {
        write(STDERR_FILENO, "Could not open file\n", 20);
        return 1;
    }
    char c[2] = { 0 };
    int res = last_elements(fid, c);
    if (!res)
    {
        if (write(STDOUT_FILENO, c, 2) < 0)
            return 1;
        if (write(STDOUT_FILENO, "\n", 1) < 0)
            return 1;
        return 0;
    }
    close(fid);
    return res;
}
