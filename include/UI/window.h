#ifndef WINDOW_CGAME
#define WINDOW_CGAME

#include <glad/glad.h>
#include <GLFW/glfw3.h>

/**
 * @brief starts the glfw module, allowing the creation of windows
 * 
 * @returns true if it started the glfw module correctly. false otherwise.
 */
bool start_glfw();

/**
 * @brief terminates the glfw module.
 * 
 * @returns true if it terminated the glfw module correctly. false otherwise.
 */
bool terminate_glfw();

/**
 * @brief A window object that is the interface between the program and the user
 */
class Window
{
private:
    GLFWwindow* glfw_window_ptr;
public:
    Window(const char* title, int width, int height);
};

/*
while (!glfwWindowShouldClose(window))
{
    glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);
    glfwPollEvents();
}
*/

#endif