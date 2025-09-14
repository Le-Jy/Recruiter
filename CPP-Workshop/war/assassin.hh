#pragma once
#include "soldier.hh"
class Assassin : public Soldier
{
public:
    Assassin();
    virtual void scream() const override;

private:
    int hp;
    int damage;
};
