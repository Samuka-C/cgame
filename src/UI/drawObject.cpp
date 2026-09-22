#include <UI/drawObject.h>

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
