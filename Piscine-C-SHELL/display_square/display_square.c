#include <stdio.h>

void display_square(int width)
{
    if (width <= 0)
        return;
    if (width == 1)
    {
        putchar('*');
        putchar('\n');
        return;
    }
    if (width % 2 == 0)
        width++;
    for (int i = 0; i < width; i++)
    {
        int j = 0;
        for (; j < width; j++)
        {
            if (i == 0 || i == width - 1)
            {
                putchar('*');
            }
            else if ((j == 0 || j == width - 1) && i % 2 == 0)
            {
                putchar('*');
            }
            else if (i % 2 != 1)
            {
                putchar(' ');
            }
        }
        if (j == width - 1 || i % 2 == 1)
            putchar('\n');
    }
    putchar('\n');
}
