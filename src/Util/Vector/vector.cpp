#include <Util/Vector/vector.h>

#include <cmath>

Vec2d::Vec2d(double x, double y)
{
    this->x = x;
    this->y = y;
}

#pragma region get methods

double Vec2d::absolute() const
{
    return std::sqrt(x * x + y * y);
}

Vec2d Vec2d::direction() const
{
    auto abs = absolute();
    return Vec2d(x / abs, y / abs);
}

Vec2d Vec2d::rotate(Angle angle) const
{
    // you can't escape linear transformations
    return Vec2d(
        x * angle.cos() + y * -angle.sin(),
        x * angle.sin() + y * angle.cos()
    );
}

#pragma endregion

#pragma region operators

Vec2d& Vec2d::operator+=(const Vec2d& other)
{
    x += other.x;
    y += other.y;
    return *this;
}

Vec2d& Vec2d::operator-=(const Vec2d& other)
{
    x -= other.x;
    y -= other.y;
    return *this;
}

Vec2d operator+(const Vec2d& first, const Vec2d& second)
{
    return Vec2d(first.x + second.x, first.y + second.y);
}

Vec2d operator-(const Vec2d& first, const Vec2d& second)
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

bool operator==(const Vec2d& first, const Vec2d& second)
{
    return first.x == second.x and first.y == second.y;
}

#pragma endregion
