#pragma once

class Soldier
{
public:
    Soldier();
    Soldier(int hp, int damage);
    virtual void attack(Soldier& s);
    virtual void print_state() const;
    virtual void scream() const;

private:
    int hp;
    int damage;
};
