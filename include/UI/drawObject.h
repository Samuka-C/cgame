#ifndef CGAME_DRAW_OBJECT
#define CGAME_DRAW_OBJECT

#include <Util/Vector/vector.h>
#include <Util/Angle/angle.h>
#include <list>

/**
 * @brief a abstract class for objects that can be drawn in a window
 */
class DrawObject
{
private:
    std::list<Vec2d> vertices;
    Vec2d center;
public:

    /**
     * @brief rotates all vertices around the center a given angle.
     */
    void rotate(Angle angle);

    /**
     * @brief moves all vertices and the center.
     */
    void move(Vec2d delta);
};

#endif