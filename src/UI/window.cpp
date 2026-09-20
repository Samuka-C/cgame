#include <UI/window.h>
#include <Logger/logger.h>

#include <mutex>
#include <chrono>
#include <thread>
#include <list>

static std::atomic<bool> glfw_initialized = false;
static std::atomic<bool> glad_initialized = false;
static std::mutex glfw_window_creation_mutex;
static std::list<Window*> allWindows = {};

#pragma region private methods

void Window::manage_window()
{
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

    std::thread loop_thread(&Window::render_window, this);
    loop_thread.detach();

    while (running)
    {
        pollEvents();
    }

    close();
}

void Window::render_window()
{
    auto lastTime = std::chrono::steady_clock::now();

    reset_context();

    while (!this->should_close())
    {
        auto currentTime = std::chrono::steady_clock::now();
        
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastTime).count();
        update(duration);

        lastTime = currentTime;
    }

    running = false;
}

void Window::update(int frameTimeMiliseconds)
{
    // override this method to make it do something
}

bool Window::should_close()
{
    return glfwWindowShouldClose(glfw_window_ptr);
}

void Window::reset_context()
{
    glfwMakeContextCurrent(glfw_window_ptr);
}

#pragma endregion

#pragma region constructors and destructors

Window::Window(std::string title, int width, int height)
{
    this->title = title;
    this->width = width;
    this->height = height;
    this->glfw_window_ptr = nullptr;
    this->running = false;

    allWindows.push_front(this);
}

Window::~Window()
{
    allWindows.remove(this);
}

#pragma endregion

#pragma region get methods

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

#pragma endregion

#pragma region public methods

void Window::start()
{
    if (!glfw_initialized)
    {
        log_error("Tried to create a new window without initializing GLFW!. use start_glfw()");
        return;
    }

    running = true;
    std::thread manage_thread(&Window::manage_window, this);
    manage_thread.detach();
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

#pragma endregion

#pragma region static methods

bool Window::start_glfw()
{
    if (!glfw_initialized)
    {
        if (!glfwInit())
        {
            log_error("Failed to initialize GLFW");
            return false;
        }

        glfw_initialized = true;
    }

    if (!glad_initialized)
    {
        GLFWwindow* dummy_window_ptr;

        {
            // can't create more than window at the same time!
            std::scoped_lock lock(glfw_window_creation_mutex);

            dummy_window_ptr = glfwCreateWindow(1, 1, "GLAD", nullptr, nullptr);
        }

        if (!dummy_window_ptr)
        {
            const char* description;
            int code = glfwGetError(&description);

            log_error(
                "Failed to start window: %d - %s",
                code,
                description ? description : "Unknown error"
            );

            return false;
        }

        glfwMakeContextCurrent(dummy_window_ptr);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            log_error("Failed to load GLAD methods");

            glfwMakeContextCurrent(nullptr);
            glfwDestroyWindow(dummy_window_ptr);
            return false;
        }

        glfwMakeContextCurrent(nullptr);
        glfwDestroyWindow(dummy_window_ptr);
        glad_initialized = true;
    }

    return true;
}

void Window::terminate_glfw()
{
    glfwTerminate();
    glfw_initialized = false;
}

void Window::pollEvents()
{
    glfwPollEvents();
}

void Window::clearGLFWContext()
{
    glfwMakeContextCurrent(nullptr);
}

bool Window::isAnyWindowRunning()
{
    for (auto window : allWindows)
    {
        if (window->isRunning())
            return true;
    }

    return false;
}

#pragma endregion
