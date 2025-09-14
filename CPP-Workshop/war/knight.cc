#include "knight.hh"

#include <iostream>
Knight::Knight()
    : Soldier(20, 5)
{}
void Knight::scream() const
{
    std::cout << "Be quick or be dead!\n";
}
