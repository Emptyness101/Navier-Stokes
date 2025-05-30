#include "vec2.h"

vec2::vec2(double _x, double _y) : x(_x), y(_y) {}
vec2::vec2() : x(0), y(0) {}

vec2 vec2::operator-(vec2 other)
{
    vec2 res;
    res.x = this->x - other.x;
    res.y = this->y - other.y;
    return res;
}

vec2 vec2::operator+(vec2 other)
{
    vec2 res;
    res.x = this->x + other.x;
    res.y = this->y + other.y;
    return res;
}

vec2 vec2::operator+(double other)
{
    vec2 res;
    res.x = this->x + other;
    res.y = this->y + other;
    return res;
}

vec2& vec2::operator+=(const vec2& other)
{
    x += other.x;
    y += other.y;
    return *this;
}

vec2 vec2::operator*(double d)
{
    vec2 res;
    res.x = this->x * d;
    res.y = this->y * d;
    return res;
}

vec2& vec2::operator*=(const double& other)
{
    x *= other;
    y *= other;
    return *this;
}


