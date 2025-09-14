#include "player.hh"

#include <iostream>
#include <stdexcept>

Player::Player(const std::string& name, size_t nb_presses)
    : name_(name)
    , bomb_(nullptr)
    , nb_presses_(nb_presses)
{}

void Player::pass_bomb(Player& receiver)
{
    if (!bomb_ || receiver.has_bomb())
        throw std::runtime_error("pas bien");
    std::cout << this->get_name() << " passes the bomb to "
              << receiver.get_name() << ".\n";
    receiver.set_bomb(std::move(bomb_));
}

void Player::press_bomb()
{
    if (!this->has_bomb())
        throw std::runtime_error("no bombas");
    size_t i = 0;
    while (i < nb_presses_ && !bomb_->has_exploded())
    {
        i++;
        bomb_->tick();
    }
}

void Player::set_bomb(std::unique_ptr<Bomb> bomb)
{
    bomb_.swap(bomb);
}

const std::string& Player::get_name() const
{
    return this->name_;
}

bool Player::has_bomb() const
{
    return this->bomb_ != nullptr;
}

bool Player::is_dead() const
{
    return this->has_bomb() && this->bomb_->has_exploded();
}
