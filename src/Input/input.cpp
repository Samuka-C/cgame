#include <Input/input.h>
#include <Logger/logger.h>

#include <GLFW/glfw3.h>
#include <unordered_map>

namespace cgame::input
{

static std::unordered_map<GLFWwindow*, KeyPressCallbackMethod> keyCallbacks;
static std::unordered_map<GLFWwindow*, MousePressCallbackMethod> mouseButtonCallbacks;
static std::unordered_map<GLFWwindow*, CursorMoveCallbackMethod> cursorMoveCallbacks;
static std::unordered_map<GLFWwindow*, Vec2d> lastMousePositions;

#pragma region get input state

bool isKeyPressed(KeyboardKey key)
{
    auto window = Window::getFocusedWindow();

    if (window == NULL)
        return false;

    return isKeyPressed(key, *window);
}

bool isKeyPressed(KeyboardKey key, Window& window)
{
    return glfwGetKey(window.getGLFWPointer(), static_cast<int>(key));
}

bool isMouseKeyPressed(MouseButton button)
{
    auto window = Window::getFocusedWindow();

    if (window == NULL)
        return false;

    return isMouseKeyPressed(button, *window);
}

bool isMouseKeyPressed(MouseButton button, Window& window)
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

#pragma endregion

#pragma region set callback methods

void setKeyPressCallback(Window& window, KeyPressCallbackMethod callback)
{
    if (callback == NULL)
    {
        glfwSetCursorPosCallback(window.getGLFWPointer(), NULL);
        return;
    }

    keyCallbacks[window.getGLFWPointer()] = callback;

    auto callbackGLFW = [](GLFWwindow* glfw_window_ptr, int key, int scancode, int action, int mods)
    {
        if (!keyCallbacks.contains(glfw_window_ptr))
            return;

        auto callback = keyCallbacks[glfw_window_ptr];

        Window* window = static_cast<Window*>(glfwGetWindowUserPointer(glfw_window_ptr));

        callback(*window, static_cast<KeyboardKey>(key), static_cast<KeyPressAction>(action), mods);
    };

    glfwSetKeyCallback(window.getGLFWPointer(), callbackGLFW);
}

void setMousePressCallback(Window& window, MousePressCallbackMethod callback)
{
    if (callback == NULL)
    {
        glfwSetCursorPosCallback(window.getGLFWPointer(), NULL);
        return;
    }

    mouseButtonCallbacks[window.getGLFWPointer()] = callback;

    auto callbackGLFW = [](GLFWwindow* glfw_window_ptr, int button, int action, int mods)
    {
        if (!mouseButtonCallbacks.contains(glfw_window_ptr))
            return;

        auto callback = mouseButtonCallbacks[glfw_window_ptr];

        Window* window = static_cast<Window*>(glfwGetWindowUserPointer(glfw_window_ptr));

        callback(*window, static_cast<MouseButton>(button), static_cast<KeyPressAction>(action), mods);
    };

    glfwSetMouseButtonCallback(window.getGLFWPointer(), callbackGLFW);
}

void setMouseMoveCallback(Window& window, CursorMoveCallbackMethod callback)
{
    if (callback == NULL)
    {
        glfwSetCursorPosCallback(window.getGLFWPointer(), NULL);
        return;
    }

    cursorMoveCallbacks[window.getGLFWPointer()] = callback;

    auto callbackGLFW = [](GLFWwindow* glfw_window_ptr, double xPos, double yPos)
    {
        if (!cursorMoveCallbacks.contains(glfw_window_ptr))
            return;

        auto callback = cursorMoveCallbacks[glfw_window_ptr];

        Window* window = static_cast<Window*>(glfwGetWindowUserPointer(glfw_window_ptr));

        auto currentMousePosition = Vec2d(xPos, yPos);
        currentMousePosition = Window::convertCoordinates(
            WindowCoordinateSystemMode::TopLeft,
            window->getCoordinateSystem(),
            currentMousePosition,
            window->getWidth(),
            window->getHeight()
        );

        if (!lastMousePositions.contains(glfw_window_ptr))
        {
            lastMousePositions[glfw_window_ptr] = currentMousePosition;
        }

        auto lastMousePosition = lastMousePositions[glfw_window_ptr];

        lastMousePositions[glfw_window_ptr] = currentMousePosition;

        callback(*window, lastMousePosition, currentMousePosition);
    };

    glfwSetCursorPosCallback(window.getGLFWPointer(), callbackGLFW);
}

#pragma endregion

}
