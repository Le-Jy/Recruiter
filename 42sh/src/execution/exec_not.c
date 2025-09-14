#include "exec_not.h"

int visit_not(int return_code)
{
    return return_code ? 0 : 1;
}
