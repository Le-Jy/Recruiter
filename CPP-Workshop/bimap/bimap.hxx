#pragma once
#include "bimap.hh"

template <typename Lhs, typename Rhs>
bool Bimap<Lhs, Rhs>::insert(const Lhs& vl, const Rhs& vr)
{
    if (lhs_.insert(std::pair<Lhs, Rhs>(vl, vr)).second)
    {
        if (rhs_.insert(std::pair<Rhs, Lhs>(vr, vl)).second)
            return true;
        lhs_.erase(vl);
    }
    return false;
}

template <typename Lhs, typename Rhs>
bool Bimap<Lhs, Rhs>::insert(const Rhs& vr, const Lhs& vl)
{
    if (rhs_.insert(std::pair<Rhs, Lhs>(vr, vl)).second)
    {
        if (lhs_.insert(std::pair<Lhs, Rhs>(vl, vr)).second)
            return true;
        rhs_.erase(vr);
    }
    return false;
}

template <typename Lhs, typename Rhs>
std::size_t Bimap<Lhs, Rhs>::erase(const Lhs& vl)
{
    if (find(vl) != lhs_.end())
    {
        rhs_.erase(lhs_.find(vl)->second);
        lhs_.erase(vl);
        return 1;
    }
    return 0;
}

template <typename Lhs, typename Rhs>
std::size_t Bimap<Lhs, Rhs>::erase(const Rhs& vr)
{
    if (find(vr) != rhs_.end())
    {
        lhs_.erase(rhs_.find(vr)->second);
        rhs_.erase(vr);
        return 1;
    }
    return 0;
}

template <typename Lhs, typename Rhs>
typename std::map<Lhs, Rhs>::const_iterator
Bimap<Lhs, Rhs>::find(const Lhs& vl) const
{
    return lhs_.find(vl);
}

template <typename Lhs, typename Rhs>
typename std::map<Rhs, Lhs>::const_iterator
Bimap<Lhs, Rhs>::find(const Rhs& vr) const
{
    return rhs_.find(vr);
}

template <typename Lhs, typename Rhs>
std::size_t Bimap<Lhs, Rhs>::size() const
{
    return lhs_.size();
}

template <typename Lhs, typename Rhs>
void Bimap<Lhs, Rhs>::clear()
{
    lhs_.clear();
    rhs_.clear();
}

template <typename Lhs, typename Rhs>
const typename std::map<Lhs, Rhs>& Bimap<Lhs, Rhs>::get_lhs() const
{
    return lhs_;
}

template <typename Lhs, typename Rhs>
const typename std::map<Rhs, Lhs>& Bimap<Lhs, Rhs>::get_rhs() const
{
    return rhs_;
}
