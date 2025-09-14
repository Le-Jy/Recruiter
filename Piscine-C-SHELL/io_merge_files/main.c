#include <stdio.h>

#include "merge_files.h"

int main(int argc, char **argv)
{
    if (argc != 3)
        return 1;
    return merge_files(argv[1], argv[2]);
}
