#include "assassin.hh"

#include <iostream>

#include "soldier.hh"

Assassin::Assassin()
    : Soldier(10, 9)
{}

void Assassin::scream() const
{
    std::cout << "Out of the shadows!\n";
}
