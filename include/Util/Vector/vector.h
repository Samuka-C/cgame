#ifndef CGAME_VECTOR
#define CGAME_VECTOR

class Vec2d
{
public:
    double x;
    double y;

    Vec2d(double x, double y);

    #pragma region get methods

    /**
     * @brief returns the size of the vector
     */
    double absolute() const;

    /**
     * @brief returns a new vector with size 1 with the same direction as this vector
     */
    Vec2d direction() const;

    #pragma endregion
};

#pragma region operators

Vec2d operator+(const Vec2d& first, const Vec2d& second);

Vec2d operator-(const Vec2d& first, const Vec2d& second);

Vec2d operator*(const Vec2d& vector, double value);

Vec2d operator*(double value, const Vec2d& vector);

bool operator==(const Vec2d& first, const Vec2d& second);

#pragma endregion

#endif