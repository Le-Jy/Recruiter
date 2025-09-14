#include <stdlib.h>
#include <unistd.h>

int rotx(int x, char *c)
{
    if (*c >= 'a' && *c <= 'z')
    {
        *c = (*c - 'a' + x + 26);
        while (*c < 0)
            *c += 26;
        *c = *c % 26 + 'a';
    }
    else if (*c >= 'A' && *c <= 'Z')
    {
        *c = (*c - 'A' + x + 26);
        while (*c < 0)
            *c += 26;
        *c = *c % 26 + 'A';
    }
    else if (*c >= '0' && *c <= '9')
    {
        *c = *c - '0' + x + 10;
        while (*c < 0)
            *c += 10;
        *c = *c % 10 + '0';
    }
    if (write(STDOUT_FILENO, c, 1))
        return 1;
    return 0;
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return 0;
    char c[1];
    int r = read(STDIN_FILENO, c, 1);
    if (r < 0)
        return 1;
    while (r != 0)
    {
        rotx(atoi(argv[1]), c);
        r = read(STDIN_FILENO, c, 1);
        if (r < 0)
            return 1;
    }
    return 0;
}
