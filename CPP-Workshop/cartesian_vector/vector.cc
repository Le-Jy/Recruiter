#include "vector.hh"

Vector::Vector(double x, double y)
    : x_(x)
    , y_(y)
{}

double Vector::get_x() const
{
    return x_;
}

double Vector::get_y() const
{
    return y_;
}

Vector& Vector::operator+=(const Vector& rhs)
{
    x_ += rhs.x_;
    y_ += rhs.y_;
    return *this;
}

Vector& Vector::operator-=(const Vector& rhs)
{
    x_ -= rhs.x_;
    y_ -= rhs.y_;
    return *this;
}

Vector& Vector::operator*=(double scalar)
{
    x_ *= scalar;
    y_ *= scalar;
    return *this;
}

Vector operator+(const Vector& lhs, const Vector& rhs)
{
    return Vector(lhs.x_ + rhs.x_, lhs.y_ + rhs.y_);
}

Vector operator-(const Vector& lhs, const Vector& rhs)
{
    return Vector(lhs.x_ - rhs.x_, lhs.y_ - rhs.y_);
}

Vector operator*(const Vector& lhs, double scalar)
{
    return Vector(lhs.x_ * scalar, lhs.y_ * scalar);
}

Vector operator*(double scalar, const Vector& rhs)
{
    return Vector(scalar * rhs.x_, scalar * rhs.y_);
}

double operator*(const Vector& lhs, const Vector& rhs)
{
    return lhs.x_ * rhs.x_ + lhs.y_ * rhs.y_;
}
