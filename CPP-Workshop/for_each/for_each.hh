#pragma once
#include "for_each.hxx"
template <class InputIt, class UnaryFunction>
constexpr UnaryFunction my_foreach(InputIt first, InputIt last, UnaryFunction f)
{
    for (; first != last; ++first)
        f(*first);

    return f;
}
