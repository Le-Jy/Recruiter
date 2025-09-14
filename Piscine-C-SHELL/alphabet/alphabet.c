#include <stdio.h>

int main(void)
{
    for (int i = 97; i < 122; i++)
    {
        putchar(i);
        putchar(' ');
    }
    putchar('z');
    putchar('\n');
}
