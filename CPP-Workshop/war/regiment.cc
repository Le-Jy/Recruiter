#include "regiment.hh"

#include <functional>
#include <vector>

void Regiment::join_by(Regiment& r)
{
    while (!r.regiment_.empty())
    {
        regiment_.push_back(std::reference_wrapper<Soldier>(r.regiment_.at(0)));
        r.regiment_.erase(r.regiment_.begin());
    }
}

std::size_t Regiment::count() const
{
    return this->regiment_.size();
}

void Regiment::add_soldier(Soldier& s)
{
    regiment_.push_back(std::reference_wrapper<Soldier>(s));
}

void Regiment::print_state() const
{
    for (auto s : this->regiment_)
        s.get().print_state();
}

void Regiment::scream() const
{
    for (auto s : this->regiment_)
        s.get().scream();
}
