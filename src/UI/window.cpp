#include <UI/window.h>
#include <Logger/logger.h>

#include <mutex>
#include <chrono>
#include <thread>

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
    log_debug("contexto resetado para a thread atual (%d) sem janela", std::this_thread::get_id());
}

void Window::update(float frameTimeSeconds)
{

}

Window::Window(std::string title, int width, int height)
{
    this->title = title;
    this->width = width;
    this->height = height;
}

std::string Window::getTitle() const
{
    return title;
}

int Window::getWidth() const
{
    return width;
}

int Window::getHeight() const
{
    return height;
}

bool Window::isRunning() const
{
    return running;
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

    running = true;
    std::thread loop_thread(&Window::loop, this);
    loop_thread.detach();
}

void Window::loop()
{
    auto start = std::chrono::steady_clock::now();
    std::chrono::_V2::steady_clock::time_point end;

    reset_context();
    log_debug("contexto resetado para a thread atual (%d) na janela %s", std::this_thread::get_id(), title.c_str());

    while (this->loop_condition())
    {
        end = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        float timeSeconds = (float)duration.count() / 1000;
        update(timeSeconds);
        start = std::chrono::steady_clock::now();
    }

    log_debug("finished looping for window %s", title.c_str());

    running = false;
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
    glfwDestroyWindow(glfw_window_ptr);
    glfw_window_ptr = nullptr;
}
