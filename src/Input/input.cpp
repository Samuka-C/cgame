#include <Input/input.h>
#include <Logger/logger.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace cgame::input
{

bool isKeyPressed(Window& window, KeyboardKey key)
{
    return glfwGetKey(window.getGLFWPointer(), static_cast<int>(key));
}

bool isMouseKeyPressed(Window& window, MouseButton button)
{
    return glfwGetMouseButton(window.getGLFWPointer(), static_cast<int>(button));
}

Vec2d getMousePos(Window& window, WindowCoordinateSystemMode overrideMode)
{
    Vec2d point(0, 0);
    glfwGetCursorPos(window.getGLFWPointer(), &point.x, &point.y);

    auto width = window.getWidth();
    auto height = window.getHeight();
    auto WindowCenter = Vec2d(width / 2, height / 2);

    auto mode = overrideMode != WindowCoordinateSystemMode::None ? overrideMode : window.getCoordinateSystem();

    switch (mode)
    {
    case WindowCoordinateSystemMode::BottomLeft:
        point.y = height - point.y;
        break;
    case WindowCoordinateSystemMode::BottomRight:
        point.x = width - point.x;
        point.y = height - point.y;
        break;
    case WindowCoordinateSystemMode::TopLeft:
        // default way glfwGetCursorPos returns coordinates
        break;
    case WindowCoordinateSystemMode::TopRight:
        point.x = width - point.x;
        break;
    case WindowCoordinateSystemMode::Center:
        point.y = height - point.y;
        point -= WindowCenter;
        break;
    }

    return point;
}

}
