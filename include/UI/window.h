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

    /**
     * @brief use in:
     * ```
     * if (windowA.loop_condition())
     * {
     *     loop methods...
     * }
     * ```
     */
    bool loop_condition();

    /**
     * @brief draws a color in the background of the window
     * 
     * @param red red channel of the color from 0 to 1
     * @param green red channel of the color from 0 to 1
     * @param blue red channel of the color from 0 to 1
     * @param alpha red channel of the color from 0 to 1
     */
    void draw_background(float red, float green, float blue, float alpha);

    /**
     * @brief polls keyboard and mouse events
     */
    void pollEvents();
};

#endif