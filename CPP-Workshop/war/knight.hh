#pragma once
#include "soldier.hh"
class Knight : public Soldier
{
public:
    Knight();
    virtual void scream() const override;

private:
    int hp = 20;
    int damage = 5;
};
