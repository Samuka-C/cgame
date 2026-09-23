#include <Logger/logger.h>
#include <UI/drawObject.h>

#include <cmath>

std::list<Vec2d> DrawObject::get_vertices() const
{
    return vertices;
}

void DrawObject::rotate(Angle angle)
{
    for (auto& vertex : vertices)
    {
        auto centerVertexVector = vertex - center;
        vertex = centerVertexVector.rotate(angle) + center;
    }
}

void DrawObject::move(Vec2d delta)
{
    center += delta;

    for (auto& vertex : vertices)
    {
        vertex += delta;
    }
}

void DrawObject::move(double deltaX, double deltaY)
{
    move(Vec2d(deltaX, deltaY));
}

void DrawObject::set_position(Vec2d newPosition)
{
    auto delta = newPosition - center;

    move(delta);
}

void DrawObject::set_position(double newPositionX, double newPositionY)
{
    set_position(Vec2d(newPositionX, newPositionY));
}

Color SolidColorObject::get_color() const
{
    return color;
}

std::list<Vec2d> create_equilateral_triangle(double sideLength)
{
    std::list<Vec2d> vertices = {};

    auto radius = sideLength / std::sqrt(3);
    auto angle = Angle::degrees(90);

    for (int i = 0; i < 3; i++)
    {
        auto vertex = Vec2d(radius * angle.cos(), radius * angle.sin());
        vertices.push_front(vertex);

        angle += Angle::degrees(120);
    }

    return vertices;
}

EquilateralTriangle::EquilateralTriangle(double sideLength, Color color) : SolidColorObject(
    create_equilateral_triangle(sideLength),
    Vec2d(0, 0),
    color
)
{
}
