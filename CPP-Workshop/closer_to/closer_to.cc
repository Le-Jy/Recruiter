#include "closer_to.hh"

CloserTo::CloserTo(int i)
    : i_(i)
{}

int abs(int a)
{
    if (a > 0)
        return a;
    return a * -1;
}

bool CloserTo::operator()(int a, int b) const
{
    if (abs(a - i_) == abs(b - i_))
    {
        if (a < b)
            return true;
        else
            return false;
    }
    return (abs(a - i_) < abs(b - i_));
}
