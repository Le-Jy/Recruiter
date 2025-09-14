#include "adapt_legacy_rectangle.hh"

#include <cmath>
#include <iostream>

AdaptLegacyRectangle::AdaptLegacyRectangle(LegacyRectangle& rect)
    : rect_(rect)
{}

AdaptLegacyRectangle::~AdaptLegacyRectangle()
{}

void AdaptLegacyRectangle::print() const
{
    std::cout << "x: " << this->rect_.get_x1() << ' '
              << "y: " << this->rect_.get_y1() << '\n';
    std::cout << "height: "
              << std::abs(this->rect_.get_y2() - this->rect_.get_y1()) << '\n';
    std::cout << "width: "
              << std::abs(this->rect_.get_x2() - this->rect_.get_x1()) << '\n';
}

unsigned AdaptLegacyRectangle::area() const
{
    return this->rect_.compute_area();
}
