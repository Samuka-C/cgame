#include <UI/drawObject.h>

void DrawObject::rotate(Angle angle)
{
    for (auto& vertex : vertices)
    {
        auto centerVertexVector = vertex - center;
        vertex = centerVertexVector.rotate(angle) + center;
    }
}
