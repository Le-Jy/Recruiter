#include <stdio.h>

int main(int argc, char **argv)
{
    if (argc <= 1)
    {
        printf("Hello World!\n");
    }
    else
    {
        argv++;
        for (; *argv; argv++)
        {
            printf("Hello %s!\n", *argv);
        }
    }
}
