#include <UI/window.h>
#include <Logger/logger.h>

static bool glfw_initialized = false;

bool start_glfw()
{
    glfwInit();

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        return false;

    glfw_initialized = true;
    return true;
}

bool terminate_glfw()
{
    glfwTerminate();
    glfw_initialized = false;
    return true;
}

Window::Window(const char* title, int width, int height)
{
    if (!glfw_initialized)
    {
        log_error("Tried to create a new window without initializing GLFW!. use start_glfw()");
        return;
    }

    glfw_window_ptr = glfwCreateWindow(width, height, title, nullptr, nullptr);

    glfwMakeContextCurrent(glfw_window_ptr);
}
