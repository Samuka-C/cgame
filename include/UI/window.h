#ifndef CGAME_WINDOW
#define CGAME_WINDOW

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Util/Color/color.h>

#include <string>
#include <atomic>

/**
 * @brief A window object that is the interface between the program and the user
 */
class Window
{
private:
    #pragma region attributes

    std::string title;
    int width;
    int height;
    GLFWwindow* glfw_window_ptr;
    std::atomic<bool> running;
    GLuint shaderProgram;

    #pragma endregion

    #pragma region private methods

    /**
     * @brief function called in a special thread responsible for starting the window,
     * starting the rendering thread, calling pollEvents() while it's running 
     * and finally calling close() when the window is closed.
     */
    void manage_window();

    /**
     * @brief function called in a special thread responsible for calling update() in the window.
     */
    void render_window();

    /**
     * @brief method that is called in a loop after the window is started until it's closed.
     * 
     * @param frameTimeMiliseconds time in miliseconds between the last call of update()
     */
    virtual void update(int frameTimeMiliseconds);

    /**
     * @brief tells if the window was closed.
     * 
     * @returns true if it was closed. false otherwise
     */
    bool should_close();

    /**
     * @brief resets the context of the window to allow it 
     * to run in different threads than the one it was created.
     */
    void reset_context();

    #pragma endregion

public:
    #pragma region constructors and destructors

    /**
     * @brief creates a window object
     * 
     * @attention doesn't actually start the window. for that, use start()
     */
    Window(std::string title, int width, int height);

    ~Window();

    #pragma endregion

    #pragma region get methods

    std::string getTitle() const;

    int getWidth() const;

    int getHeight() const;

    bool isRunning() const;

    #pragma endregion

    #pragma region public methods

    /**
     * @brief starts the windows and sets the glfw context
     * 
     * @attention should be called from the main thread!
     */
    void start();

    void draw_triangle();

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

    #pragma endregion

    #pragma region static methods

    /**
     * @brief starts the glfw module, allowing the creation of windows
     * 
     * @returns true if it started the glfw module correctly. false otherwise.
     */
    static bool start_glfw();

    /**
     * @brief terminates the glfw module.
     */
    static void terminate_glfw();

    /**
     * @brief polls events related to the glfw windows
     */
    static void pollEvents();

    /**
     * @brief clears the GLFW context on the current thread.
     */
    static void clearGLFWContext();

    /**
     * @brief tells if any window (created by this class) is currently running.
     */
    static bool isAnyWindowRunning();

    #pragma endregion
};

#endif