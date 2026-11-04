#include <Input/input.h>
#include <Logger/logger.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace cgame::input
{

bool isKeyPressed(Window window, KeyboardKey key)
{
    return glfwGetKey(window.getGLFWPointer(), static_cast<int>(key));
}

bool isMouseKeyPressed(Window window, MouseButton button)
{
    return glfwGetMouseButton(window.getGLFWPointer(), static_cast<int>(button));
}

}
