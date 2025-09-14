#pragma once
#include "singleton.hh"

template <typename T>
T& Singleton<T>::instance()
{
    static T a = T();
    return a;
}
