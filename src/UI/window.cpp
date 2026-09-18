#include <UI/window.h>
#include <Logger/logger.h>

#include <mutex>

static bool glfw_initialized = false;
static std::mutex glfw_window_creation_mutex;

bool start_glfw()
{
    glfwInit();
    glfw_initialized = true;
    return true;
}

bool terminate_glfw()
{
    glfwTerminate();
    glfw_initialized = false;
    return true;
}

void pollEvents()
{
    glfwPollEvents();
}

void resetContext()
{
    glfwMakeContextCurrent(nullptr);
}

Window::Window(std::string title, int width, int height)
{
    this->title = title;
    this->width = width;
    this->height = height;
}

void Window::start()
{
    if (!glfw_initialized)
    {
        log_error("Tried to create a new window without initializing GLFW!. use start_glfw()");
        return;
    }

    {
        // can't create more than window at the same time!
        std::scoped_lock lock(glfw_window_creation_mutex);

        glfw_window_ptr = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    }

    if (!glfw_window_ptr)
    {
        const char* description;
        int code = glfwGetError(&description);

        log_error(
            "Failed to start window: %d - %s",
            code,
            description ? description : "Unknown error"
        );

        return;
    }

    glfwMakeContextCurrent(glfw_window_ptr);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        log_error("Failed to load GL methods");
        return;
    }
}

bool Window::loop_condition()
{
    return !glfwWindowShouldClose(glfw_window_ptr);
}

void Window::reset_context()
{
    glfwMakeContextCurrent(glfw_window_ptr);
}

void Window::draw_background(Color color)
{
    glClearColor(
        color.get_red_float(), 
        color.get_green_float(), 
        color.get_blue_float(), 
        color.get_alpha_float());
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(glfw_window_ptr);
}

void Window::close()
{
    glfwSetWindowShouldClose(glfw_window_ptr, GLFW_TRUE);
}
