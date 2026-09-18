#include <UI/window.h>
#include <Logger/logger.h>

#include <thread>

const Color blue = Color::fromHSV(220, 0.6, 1);
const Color red = Color::fromHSV(15, 1, 0.85);

void runWindow(const char* title, int width, int height, Color color)
{
    Window window(title, width, height);

    // The OpenGL context belongs to this thread.
    window.reset_context();

    while (window.loop_condition())
    {
        window.draw_background(color);
    }
}

int main()
{
    start_glfw();

    std::thread blue_thread(
        runWindow,
        "blue",
        600,
        800,
        blue
    );

    std::thread red_thread(
        runWindow,
        "red",
        600,
        800,
        red
    );

    blue_thread.join();
    red_thread.join();

    terminate_glfw();

    return 0;
}
