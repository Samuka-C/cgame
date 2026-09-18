#include <UI/window.h>
#include <Logger/logger.h>

#include <thread>

const Color blue = Color::fromHSV(220, 0.6, 1);
const Color red = Color::fromHSV(15, 1, 0.85);

void runWindow(Window& window, Color color)
{
    window.reset_context();

    while (window.loop_condition())
    {
        window.draw_background(color);
    }
}

int main()
{
    start_glfw();

    Window blue_window("blue", 800, 600);
    blue_window.start();
    Window red_window("red", 800, 600);
    red_window.start();
    resetContext();

    std::thread blue_thread(runWindow, std::ref(blue_window), blue);
    std::thread red_thread(runWindow, std::ref(red_window), red);

    while (blue_window.loop_condition() || red_window.loop_condition())
    {
        pollEvents();
    }

    blue_thread.join();
    red_thread.join();

    terminate_glfw();

    return 0;
}
