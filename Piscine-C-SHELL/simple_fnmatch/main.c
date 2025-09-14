#include "simple_fnmatch.h"

int main(void)
{
    return simple_fnmatch("a*bc", "adddbcbbbbbc");
}
