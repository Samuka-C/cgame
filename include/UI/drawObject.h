#ifndef CGAME_DRAW_OBJECT
#define CGAME_DRAW_OBJECT

#include <Util/Vector/vector.h>
#include <Util/Angle/angle.h>
#include <Util/Color/color.h>
#include <list>

/**
 * @brief a abstract class for objects that can be drawn in a window
 */
class DrawObject
{
private:
    std::list<Vec2d> vertices;
    Vec2d center;

protected:
    DrawObject(std::list<Vec2d> vertices, Vec2d center) : vertices(vertices), center(center)
    {}

public:

    /**
     * @brief returns the list of vertices of the object
     */
    std::list<Vec2d> get_vertices() const;

    /**
     * @brief rotates all vertices around the center a given angle.
     */
    void rotate(Angle angle);

    /**
     * @brief moves the object a specified distance in each axis
     */
    void move(Vec2d delta);

    /**
     * @brief moves the object a specified distance in each axis
     */
    void move(double deltaX, double deltaY);

    /**
     * @brief moves the object to a new position
     */
    void set_position(Vec2d newPosition);

    /**
     * @brief moves the object to a new position
     */
    void set_position(double newPositionX, double newPositionY);
};

/**
 * @brief a abstract class for objects that have one solid color
 */
class SolidColorObject : public DrawObject
{
private:
    Color color;

protected:
    SolidColorObject(std::list<Vec2d> vertices, Vec2d center, Color color) : DrawObject(vertices, center), color(color)
    {}

public:

    /**
     * @brief returns the color of the object
     */
    Color get_color() const;
};

/**
 * @brief a equilateral triangle
 */
class EquilateralTriangle : public SolidColorObject
{
public:

    /**
     * @brief creates a equilateral triangle with center 0, 0
     */
    EquilateralTriangle(double sideLength, Color color);
};

class Rectangle : public SolidColorObject
{
public:

    /**
     * @brief creates a rectangle with center 0, 0
     */
    Rectangle(double width, double height, Color color);

    /**
     * @brief creates a rectangle with center 0, 0
     */
    Rectangle(Vec2d dimensions, Color color);
};

#endif