#include "builder.hh"

#include <memory>

#include "components.hh"

Car Builder::get_car() const
{
    auto res = Car();
    res.wheels_ = std::array<std::unique_ptr<Wheel>, 4>();
    res.wheels_[0] = get_wheel();
    res.wheels_[1] = get_wheel();
    res.wheels_[2] = get_wheel();
    res.wheels_[3] = get_wheel();
    res.engine_ = get_engine();
    res.body_ = get_body();
    return res;
};

std::unique_ptr<Wheel> JeepBuilder::get_wheel() const
{
    return std::make_unique<Wheel>(22);
}
std::unique_ptr<Engine> JeepBuilder::get_engine() const
{
    return std::make_unique<Engine>(400);
}
std::unique_ptr<Body> JeepBuilder::get_body() const
{
    return std::make_unique<Body>("SUV");
}

std::unique_ptr<Wheel> NissanBuilder::get_wheel() const
{
    return std::make_unique<Wheel>(16);
}
std::unique_ptr<Engine> NissanBuilder::get_engine() const
{
    return std::make_unique<Engine>(85);
}
std::unique_ptr<Body> NissanBuilder::get_body() const
{
    return std::make_unique<Body>("hatchback");
}
