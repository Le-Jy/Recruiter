#pragma once
#include "is_prime.hh"

constexpr bool is_prime(unsigned n)
{
    if (n <= 1)
        return false;
    if (n <= 3)
        return true;
    if (n % 2 == 0 || n % 3 == 0)
        return false;
    for (unsigned i = 5; i * i <= n; i++)
    {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    return true;
}
