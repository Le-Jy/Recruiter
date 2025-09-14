#include "bomb.hh"

#include <iostream>
#include <stdexcept>

Bomb::Bomb(int ticks)
{
    if (ticks <= 0)
        throw std::runtime_error("pas bien");
    max_ticks_ = ticks;
    count_ = 0;
}

void Bomb::tick()
{
    if (count_ + 1 > max_ticks_)
        throw std::runtime_error("should have already explods");
    if (count_ % 2 == 0)
        std::cout << "Tic!\n";
    else
        std::cout << "Tac!\n";
    count_++;
}

bool Bomb::has_exploded() const
{
    return (count_ >= max_ticks_);
}
