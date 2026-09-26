#ifndef CGAME_ANGLE
#define CGAME_ANGLE

namespace cgame::util::angle
{

extern const double PI;

class Angle
{
private:
    double angleDegrees;

    Angle(double angleDegrees);
public:

    #pragma region get methods

    /**
     * @brief returns the value in degrees of the current angle
     */
    double degrees() const;

    /**
     * @brief returns the value in radians of the current angle
     */
    double radians() const;

    /**
     * @brief sin of the angle
     */
    double sin() const;

    /**
     * @brief cossine of the angle
     */
    double cos() const;

    /**
     * @brief tangent of the angle
     */
    double tan() const;

    #pragma endregion

    #pragma region static methods

    /**
     * @brief returns a angle from a value in degrees
     */
    static Angle degrees(double value);

    /**
     * @brief returns a angle from a value in radians
     */
    static Angle radians(double value);

    /**
     * @brief returns the angle which sin is the value provided
     */
    static Angle asin(double value);

    /**
     * @brief returns the angle which cossine is the value provided
     */
    static Angle acos(double value);

    /**
     * @brief returns the angle which tangent is the value provided
     */
    static Angle atan(double value);

    #pragma endregion

    #pragma region class operators

    Angle& operator+=(const Angle& other);

    Angle& operator-=(const Angle& other);

    #pragma endregion
};

#pragma region operators

Angle operator+(const Angle& first, const Angle& second);

Angle operator-(const Angle& first, const Angle& second);

Angle operator*(const Angle& angle, double value);

Angle operator*(double value, const Angle& angle);

Angle operator/(const Angle& angle, double value);

bool operator==(const Angle& first, const Angle& second);

#pragma endregion

}

#endif