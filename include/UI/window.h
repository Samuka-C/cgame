#ifndef CGAME_WINDOW
#define CGAME_WINDOW

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Util/Color/color.h>
#include <UI/drawObject.h>

#include <string>
#include <atomic>

namespace cgame::ui
{

enum class WindowCoordinateSystemMode
{
    /**
     * @attention can't be used for the mode of windows, only for checks. 
     */
    None,

    /**
     * @brief the 0, 0 starts at the bottom left corner with positive X to the right and positive Y to the top
     */
    BottomLeft,

    /**
     * @brief the 0, 0 starts at the bottom right corner with positive X to the left and positive Y to the top
     */
    BottomRight,

    /**
     * @brief the 0, 0 starts at the center with positive X to the right and positive Y to the top
     */
    Center,

    /**
     * @brief the 0, 0 starts at the top left with positive X to the right and positive Y to the bottom
     */
    TopLeft,

    /**
     * @brief the 0, 0 starts at the top right with positive X to the left and positive Y to the bottom
     */
    TopRight
};

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
    std::atomic<bool> resized;
    std::atomic<bool> focused;
    GLuint shaderProgram;
    WindowCoordinateSystemMode coordinateMode;

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

    /**
     * @brief converts a point in window coordinates (in pixels) to NDC
     */
    Vec2d convert_coordinates(Vec2d point);

    /**
     * @brief called when the window is resized
     */
    static void window_resized(GLFWwindow* glfw_window_ptr, int width, int height);

    /**
     * @brief called when the window is focused or unfocused. 
     */
    static void window_change_focus(GLFWwindow* glfw_window_ptr, int focused);

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

    bool isFocused() const;

    GLFWwindow* getGLFWPointer() const;

    WindowCoordinateSystemMode getCoordinateSystem() const;

    #pragma endregion

    #pragma region set methods

    /**
     * @brief set the title of the window
     */
    void set_title(const std::string& newTitle);

    /**
     * @brief change the size of the window
     */
    void set_size(int width, int height);

    /**
     * @brief changes how the object coordinates are interpreted 
     * and which point of the window the objects will be attached to when resizing the window
     */
    void set_coordinate_system(WindowCoordinateSystemMode newMode);

    #pragma endregion

    #pragma region public methods

    /**
     * @brief starts the windows and sets the glfw context
     * 
     * @attention should be called from the main thread!
     */
    virtual void start();

    void draw_solid_color_object(SolidColorObject object);

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
     * @brief update the values of the width and height the the current width and height of the window
     */
    void update_width_height();

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

    /**
     * @brief returns a pointer to the currently focused window.
     * 
     * @return NULL if there are no windows (created by this class) focused
     */
    static Window* getFocusedWindow();

    /**
     * @brief converts a coordinate from one system to another
     * 
     * @param modeFrom the coordinate system of coordsFrom
     * 
     * @param modeTo the coordinate system to convert to
     * 
     * @param coordsFrom the coordinates to convert
     * 
     * @param width width of the window
     * 
     * @param height height of the window
     * 
     * @return a Vec2d coresponding to coordsFrom in the modeTo system
     */
    static Vec2d convertCoordinates(WindowCoordinateSystemMode modeFrom, WindowCoordinateSystemMode modeTo, Vec2d coordsFrom, int width, int height);

    #pragma endregion
};

}

#endif