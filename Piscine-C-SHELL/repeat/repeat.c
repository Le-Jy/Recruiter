#include <stdio.h>

int main(int argc, char **argv)
{
    if (argc == 3)
    {
        char c = *argv[2];
        argv++;
        char *s = *argv;
        for (; c > '0'; c--)
        {
            puts(s);
        }
        return 0;
    }
    return 1;
}
