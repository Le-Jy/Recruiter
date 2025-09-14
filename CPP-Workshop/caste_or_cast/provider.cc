#include "provider.hh"

#include <iostream>

#include "ant.hh"
#include "nurturer.hh"
#include "queen.hh"
#include "worker.hh"

void Provider::work()
{
    if (!(stage_ == DevelopmentStage::ADULT))
        return;
    float to_eat = food_stock_ - static_cast<int>(food_stock_);
    food_level_ += to_eat;
    food_stock_ -= to_eat;
    harvestFood();
    Worker::work();
}
void Provider::transferFood(Nurturer& nurturer)
{
    if (food_stock_ >= 1)
    {
        std::cout << "Transferring food.\n";
        nurturer.increment_food_stock_by(static_cast<int>(food_stock_));
        food_stock_ -= static_cast<int>(food_stock_);
    }
}

bool Provider::communicate(std::weak_ptr<Ant> wk_receiver)
{
    if (!Ant::communicate(wk_receiver))
        return false;
    std::cout << "Provider initiates communication.\n";
    if (dynamic_cast<const Provider*>(wk_receiver.lock().get()))
        return true;
    if (dynamic_cast<const Queen*>(wk_receiver.lock().get()))
        return true;
    Nurturer* tmp = dynamic_cast<Nurturer*>(wk_receiver.lock().get());
    if (!dynamic_cast<const Nurturer*>(wk_receiver.lock().get()))
        return false;
    transferFood(*tmp);
    return true;
}

void Provider::harvestFood()
{
    std::cout << "Harvested " << luck_ << " food.\n";
    float tmp = (luck_ - static_cast<int>(luck_)) / 2;
    this->food_stock_ += luck_;
    this->food_level_ -= tmp;
}
