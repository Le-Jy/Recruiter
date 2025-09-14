#pragma once
#include "exist.hh"

template <class T>
bool Exist<T>::operator()(T arg)
{
    return !args_.insert(arg).second;
}
