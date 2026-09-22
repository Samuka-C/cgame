#include <Util/Vector/vector.h>

#include <cmath>

Vec2d::Vec2d(double x, double y)
{
    this->x = x;
    this->y = y;
}

double Vec2d::absolute() const
{
    return std::sqrt(x * x + y * y);
}

Vec2d Vec2d::direction() const
{
    auto abs = absolute();
    return Vec2d(x / abs, y / abs);
}

Vec2d operator+(const Vec2d& first, const Vec2d& second)
{
    return Vec2d(first.x + second.x, first.y + second.y);
}

Vec2d operator+(const Vec2d& first, const Vec2d& second)
{
    return Vec2d(first.x - second.x, first.y - second.y);
}

Vec2d operator*(const Vec2d& vector, double value)
{
    return Vec2d(vector.x * value, vector.y * value);
}

Vec2d operator*(double value, const Vec2d& vector)
{
    return Vec2d(vector.x * value, vector.y * value);
}
