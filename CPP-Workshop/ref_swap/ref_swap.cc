#include "ref_swap.hh"

void ref_swap(int& a, int& b)
{
    int tmp = a;
    a = b;
    b = tmp;
}

void ptr_swap(int* a, int* b)
{
    if (a == nullptr || b == nullptr)
        return;
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
