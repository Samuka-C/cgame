#ifndef WINDOW_CGAME
#define WINDOW_CGAME

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Util/Color/color.h>

#include <string>
#include <atomic>

/**
 * @brief starts the glfw module, allowing the creation of windows
 * 
 * @returns true if it started the glfw module correctly. false otherwise.
 */
bool start_glfw();

/**
 * @brief terminates the glfw module.
 */
void terminate_glfw();

/**
 * @brief polls events related to the glfw windows
 */
void pollEvents();

/**
 * @brief clears the GLFW context on the current thread.
 */
void clearGLFWContext();

/**
 * @brief A window object that is the interface between the program and the user
 */
class Window
{
private:
    std::string title;
    int width;
    int height;
    GLFWwindow* glfw_window_ptr;
    std::atomic<bool> running;

    void loop();

    /**
     * @brief method that is called in a loop after the window is started until it's closed.
     * 
     * @param frameTimeMiliseconds time in miliseconds between the last call of update()
     */
    virtual void update(int frameTimeMiliseconds);

public:
    /**
     * @brief creates a window object
     * 
     * @attention doesn't actually start the window. for that, use start()
     */
    Window(std::string title, int width, int height);

    std::string getTitle() const;

    int getWidth() const;

    int getHeight() const;

    bool isRunning() const;

    /**
     * @brief starts the windows and sets the glfw context
     * 
     * @attention should be called from the main thread!
     */
    void start();

    /**
     * @brief use in:
     * ```
     * while (windowA.loop_condition())
     * {
     *     loop methods...
     * }
     * ```
     */
    bool loop_condition();

    /**
     * @brief resets the context of the window to allow it 
     * to run in different threads than the one it was created.
     */
    void reset_context();

    /**
     * @brief draws a color in the background of the window
     * 
     * @param red red channel of the color from 0 to 1
     * @param green red channel of the color from 0 to 1
     * @param blue red channel of the color from 0 to 1
     * @param alpha red channel of the color from 0 to 1
     */
    void draw_background(Color color);

    /**
     * @brief closes the window
     * 
     * @attention should be called from the main thread!
     */
    void close();
};

#endif