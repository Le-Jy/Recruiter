#pragma once

#include <set>
template <class T>
class Exist
{
public:
    bool operator()(T arg);

private:
    std::set<T> args_;
};

#include "exist.hxx"
