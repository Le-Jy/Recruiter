#include "count_words.h"

int main(int argc, char **argv)
{
    if (argc != 2)
        return -1;
    return count_words(argv[1]);
}
