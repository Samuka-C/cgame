#include <Util/Math/angle.h>

#include <cmath>

namespace cgame::util::math
{

const double PI = 2 * std::acos(0);

Angle::Angle(double angleDegrees)
{
    this->angleDegrees = angleDegrees;
}

#pragma region get methods

double Angle::degrees() const
{
    return angleDegrees;
}

double Angle::radians() const
{
    return PI * angleDegrees / 180;
}

double Angle::sin() const
{
    return std::sin(radians());
}

double Angle::cos() const
{
    return std::cos(radians());
}

double Angle::tan() const
{
    return std::tan(radians());
}

#pragma endregion

#pragma region static methods

Angle Angle::degrees(double value)
{
    return Angle(value);
}

Angle Angle::radians(double value)
{
    return Angle::degrees(180 * value / PI);
}

Angle Angle::asin(double value)
{
    return Angle::radians(std::asin(value));
}

Angle Angle::acos(double value)
{
    return Angle::radians(std::acos(value));
}

Angle Angle::atan(double value)
{
    return Angle::radians(std::atan(value));
}

#pragma endregion

#pragma region operators

Angle& Angle::operator+=(const Angle& other)
{
    this->angleDegrees += other.angleDegrees;
    return *this;
}

Angle& Angle::operator-=(const Angle& other)
{
    this->angleDegrees -= other.angleDegrees;
    return *this;
}

Angle operator+(const Angle& first, const Angle& second)
{
    return Angle::degrees(first.degrees() + second.degrees());
}

Angle operator-(const Angle& first, const Angle& second)
{
    return Angle::degrees(first.degrees() - second.degrees());
}

Angle operator*(const Angle& angle, double value)
{
    return Angle::degrees(angle.degrees() * value);
}

Angle operator*(double value, const Angle& angle)
{
    return Angle::degrees(angle.degrees() * value);
}

Angle operator/(const Angle& angle, double value)
{
    return Angle::degrees(angle.degrees() / value);
}

bool operator==(const Angle& first, const Angle& second)
{
    return first.degrees() == second.degrees();
}

#pragma endregion

}
