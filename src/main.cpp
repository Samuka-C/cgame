#include <UI/window.h>
#include <Logger/logger.h>

#include <thread>
#include <atomic>
#include <cmath>

const Color red = Color::fromHSV(15, 1, 0.85);
const Color green = Color::fromHSV(100, 0.7, 0.67);
const Color blue = Color::fromHSV(220, 0.6, 1);

class ColorWindow : public Window
{
private:
    Color color;
    float angle = 0.0f;
    float angleV = 0.0f;

    float t = 0.0f;

    void update(int frameTimeMiliseconds) override
    {
        t += (float)frameTimeMiliseconds / 1000;

        angleV = std::sin(10 * t) / 10;
        angle += angleV * frameTimeMiliseconds; 

        draw_background(color);
        draw_triangle(0.2 + (1 + std::cos(angle)) / 4, angle, Color::green);
    }

public:
    ColorWindow(std::string title, int width, int height, Color color) : Window(title, width, height), color(color)
    {

    }
};

int main()
{
    Window::start_glfw();

    ColorWindow red_window("red", 800, 800, red);

    red_window.start();

    while (Window::isAnyWindowRunning());

    Window::terminate_glfw();

    return 0;
}
