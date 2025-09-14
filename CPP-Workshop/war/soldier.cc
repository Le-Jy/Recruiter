#include "soldier.hh"

#include <iostream>

Soldier::Soldier()
    : hp(15)
    , damage(3)
{}

Soldier::Soldier(int hp, int damage)
    : hp(hp)
    , damage(damage)
{}

void Soldier::attack(Soldier& s)
{
    s.hp -= this->damage;
}

void Soldier::print_state() const
{
    std::cout << "I have " << this->hp << " health points.\n";
}

void Soldier::scream() const
{
    std::cout << "No pity for losers!\n";
}
