#include "complex.h"

int main(void)
{
    struct complex a;
    a.real = 1.;
    a.img = 1.;
    print_complex(neg_complex(a));
}
