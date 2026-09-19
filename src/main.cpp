#include <UI/window.h>
#include <Logger/logger.h>

#include <thread>
#include <atomic>

const Color blue = Color::fromHSV(220, 0.6, 1);
const Color red = Color::fromHSV(15, 1, 0.85);

void runWindow(Window& window, Color color, std::atomic<bool>& running)
{
    window.reset_context();

    while (window.loop_condition())
    {
        window.draw_background(color);
    }

    log_debug("closed window %s", window.getTitle().c_str());

    running = false;
}

int main()
{
    start_glfw();

    std::atomic<bool> blue_running = true;
    Window blue_window("blue", 800, 600);
    blue_window.start();

    std::atomic<bool> red_running = true;
    Window red_window("red", 800, 600);
    red_window.start();

    resetContext();

    std::thread blue_thread(runWindow, std::ref(blue_window), blue, std::ref(blue_running));
    std::thread red_thread(runWindow, std::ref(red_window), red, std::ref(red_running));

    while (blue_running || red_running)
    {
        pollEvents();

        if (!blue_running)
        {
            blue_window.close();
        }

        if (!red_running)
        {
            red_window.close();
        }
    }

    blue_thread.join();
    red_thread.join();

    terminate_glfw();

    return 0;
}
