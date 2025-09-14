#include "game.hh"

#include <iostream>
#include <memory>
#include <stdexcept>

void Game::add_player(const std::string& name, size_t nb_presses)
{
    this->players_.push_back(Player(name, nb_presses));
}

void Game::play(int bomb_ticks)
{
    if (this->players_.size() < 2)
        throw std::runtime_error("To few players");
    auto bazuka = std::make_unique<Bomb>(bomb_ticks);
    this->players_.at(0).set_bomb(std::move(bazuka));
    size_t i = 0;
    while (true)
    {
        this->players_.at(i).press_bomb();
        if (this->players_.at(i).is_dead())
        {
            std::cout << this->players_.at(i).get_name() << " has exploded.\n";
            return;
        }
        if (i + 1 < this->players_.size())
        {
            this->players_.at(i).pass_bomb(this->players_.at(i + 1));
            i++;
        }
        else
        {
            this->players_.at(i).pass_bomb(this->players_.at(0));
            i = 0;
        }
    }
}
