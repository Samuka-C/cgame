#include <UI/window.h>
#include <Logger/logger.h>
#include <UI/shaders/shaderLoader.h>

#include <mutex>
#include <chrono>
#include <thread>
#include <list>
#include <cmath>

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

    // sets the window object as the user pointer for the window pointer
    glfwSetWindowUserPointer(glfw_window_ptr, this);

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

    glfwSetFramebufferSizeCallback(
        glfw_window_ptr,
        window_resized
    );

    auto vertexShader = loadShader("src/UI/shaders/vertexShader.glsl", GL_VERTEX_SHADER);
    auto fragmentShader  = loadShader("src/UI/shaders/fragmentShader.glsl", GL_FRAGMENT_SHADER);

    shaderProgram = assembleShaderProgram({vertexShader, fragmentShader});

    while (!this->should_close())
    {
        if (resized)
        {
            glViewport(0, 0, width, height);
            resized = false;
        }

        auto currentTime = std::chrono::steady_clock::now();
        
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastTime).count();
        update(duration);

        // swap buffers to draw the frame
        glfwSwapBuffers(glfw_window_ptr);

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

Vec2d Window::convert_coordinates(Vec2d point)
{
    auto WindowCenter = Vec2d(width / 2, height / 2);

    switch (coordinateMode)
    {
    case WindowCoordinateSystemMode::BottomLeft:
        point -= WindowCenter;
        break;
    case WindowCoordinateSystemMode::BottomRight:
        point.x = width - point.x;
        point -= WindowCenter;
        break;
    case WindowCoordinateSystemMode::TopLeft:
        point.y = height - point.y;
        point -= WindowCenter;
        break;
    case WindowCoordinateSystemMode::TopRight:
        point.x = width - point.x;
        point.y = height - point.y;
        point -= WindowCenter;
        break;
    }

    return Vec2d(2 * point.x / width, 2 * point.y / height);
}

void Window::window_resized(GLFWwindow* glfw_window_ptr, int width, int height)
{
    Window* window = static_cast<Window*>(glfwGetWindowUserPointer(glfw_window_ptr));

    window->width = width;
    window->height = height;

    window->resized = true;
}

#pragma endregion

#pragma region constructors and destructors

Window::Window(std::string title, int width, int height)
{
    this->title = title;
    this->width = width;
    this->height = height;

    glfw_window_ptr = nullptr;
    running = false;
    resized = false;
    coordinateMode = WindowCoordinateSystemMode::TopLeft;
    shaderProgram = 0;

    allWindows.push_front(this);
}

Window::~Window()
{
    allWindows.remove(this);
    glDeleteProgram(shaderProgram);
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

#pragma region set methods

void Window::set_title(const std::string& newTitle)
{
    title = newTitle;
    glfwSetWindowTitle(glfw_window_ptr, title.c_str());
}

void Window::set_size(int width, int height)
{
    if (width <= 0 or height <= 0)
    {
        log_error("new width (%d) and height (%d) are not valid!", width, height);
        return;
    }

    this->width = width;
    this->height = height;

    glfwSetWindowSize(glfw_window_ptr, width, height);

    resized = true;
}

void Window::set_coordinate_system(WindowCoordinateSystemMode newMode)
{
    coordinateMode = newMode;
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

void Window::draw_solid_color_object(SolidColorObject object)
{
    int number_vertices = object.get_vertices().size();

    double vertices[2 * number_vertices]; // each vertice has 2 doubles
    int index = 0;
    for (auto vertex : object.get_vertices())
    {
        auto ndcVertex = convert_coordinates(vertex);

        vertices[index++] = ndcVertex.x;
        vertices[index++] = ndcVertex.y;
    }

    unsigned int VertexArrayObjectId, VertexBufferObjectId;

    // generate the Vertex Array Object
    glGenVertexArrays(1, &VertexArrayObjectId);

    // select current Vertex Array Object
    glBindVertexArray(VertexArrayObjectId);

    // generate the Vertex Buffer Object
    glGenBuffers(1, &VertexBufferObjectId);

    // select current Vertex Buffer Object
    glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObjectId);

    // use the vertex and fragment shader
    glUseProgram(shaderProgram);

    // set the color in the fragment shader
    auto colorLocation = glGetUniformLocation(shaderProgram, "fragmentColor");

    glUniform4f(
        colorLocation, 
        object.get_color().get_red_float(),
        object.get_color().get_green_float(),
        object.get_color().get_blue_float(),
        object.get_color().get_alpha_float()
    );

    // load vertices in VBO
    glBufferData(
        GL_ARRAY_BUFFER, 
        sizeof(vertices), 
        vertices, 
        GL_STATIC_DRAW
    );

    // tell GL how to read the vertices
    glVertexAttribPointer(
        0,                 // attribute location
        2,                 // 2 coordinates per vertice, x and y
        GL_DOUBLE,         // vertices are double
        GL_FALSE,          // normalization
        2 * sizeof(double),// size of each vertice
        nullptr            // offset
    );

    // enable attribute location
    glEnableVertexAttribArray(0);

    // draw thw triangles
    glDrawArrays(GL_TRIANGLES, 0, number_vertices);

    // delete the VBO and VAO
    glDeleteBuffers(1, &VertexBufferObjectId);
    glDeleteVertexArrays(1, &VertexArrayObjectId);
}

void Window::draw_background(Color color)
{
    glClearColor(
        color.get_red_float(), 
        color.get_green_float(), 
        color.get_blue_float(), 
        color.get_alpha_float());
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::update_width_height()
{
    glfwGetWindowSize(glfw_window_ptr, &width, &height);
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
