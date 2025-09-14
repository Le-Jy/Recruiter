#include "int_container.hh"

#include <iostream>
#include <memory>
#include <optional>

MyIntContainer::MyIntContainer(size_t size)
    : current_size_(0)
    , max_size_(size)
    , elems_(std::make_unique<int[]>(size))
{}

void MyIntContainer::print() const
{
    size_t index = 0;
    while (index < current_size_)
    {
        std::cout << elems_[index];
        if (index < current_size_ - 1)
            std::cout << " | ";
        index++;
    }
    std::cout << '\n';
}

size_t MyIntContainer::get_len() const
{
    return current_size_;
}

bool MyIntContainer::add(int elem)
{
    if (current_size_ == max_size_)
        return false;
    elems_[current_size_++] = elem;
    return true;
}

std::optional<int> MyIntContainer::pop()
{
    if (current_size_ != 0)
    {
        return elems_[--current_size_];
    }
    return std::nullopt;
}

std::optional<int> MyIntContainer::get(size_t position) const
{
    if (position < current_size_)
    {
        return elems_[position];
    }
    return std::nullopt;
}

std::optional<size_t> MyIntContainer::find(int elem) const
{
    size_t res = 0;
    while (res < current_size_ && elems_[res] != elem)
        res++;
    if (res < current_size_)
        return res;
    return std::nullopt;
}

void MyIntContainer::sort()
{
    for (size_t i = 0; i < current_size_; i++)
    {
        for (size_t j = 0; j < current_size_ - i - 1; j++)
        {
            if (elems_[j] > elems_[j + 1])
            {
                std::swap(elems_[j], elems_[j + 1]);
            }
        }
    }
}

bool MyIntContainer::is_sorted() const
{
    size_t i = 0;
    if (current_size_ == 0)
        return true;
    while (i + 1 < current_size_ && elems_[i] <= elems_[i + 1])
        i++;
    return i == current_size_ - 1;
}
