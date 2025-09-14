#include "lakes.h"

static void replace_lakes(char **map, int i, int j)
{
    map[i][j] = '#';
    if (map[i][j + 1] == '.')
        replace_lakes(map, i, j + 1);
    if (map[i][j - 1] == '.')
        replace_lakes(map, i, j - 1);
    if (map[i + 1][j] == '.')
        replace_lakes(map, i + 1, j);
    if (map[i - 1][j] == '.')
        replace_lakes(map, i - 1, j);
}

int lakes(char **map, int width, int height)
{
    int lakes_counter = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (map[i][j] == '.')
            {
                replace_lakes(map, i, j);
                lakes_counter++;
            }
        }
    }
    return lakes_counter;
}
