#include <UI/window.h>
#include <Logger/logger.h>

#include <thread>
#include <atomic>

const Color red = Color::fromHSV(15, 1, 0.85);
const Color green = Color::fromHSV(100, 0.7, 0.67);
const Color blue = Color::fromHSV(220, 0.6, 1);

class ColorWindow : public Window
{
private:
    Color color;

    void update(int frameTimeMiliseconds) override
    {
        draw_background(color);
    }

public:
    ColorWindow(std::string title, int width, int height, Color color) : Window(title, width, height), color(color)
    {

    }
};

int main()
{
    start_glfw();

    ColorWindow red_window("red", 800, 600, red);
    ColorWindow green_window("green", 800, 600, green);
    ColorWindow blue_window("blue", 800, 600, blue);

    red_window.start();
    green_window.start();
    blue_window.start();

    while (red_window.isRunning() || green_window.isRunning() || blue_window.isRunning())
    {
        pollEvents();

        // TODO: find a way to close windows automatically 
        if (!red_window.isRunning())
            red_window.close();

        if (!green_window.isRunning())
            green_window.close();

        if (!blue_window.isRunning())
            blue_window.close();
    }

    terminate_glfw();

    return 0;
}
