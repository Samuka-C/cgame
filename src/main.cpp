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
    float t = 0.0f;
    Angle angularSpeed = Angle::degrees(180);

    SolidColorObject shape = EquilateralTriangle(200, Color::blue);

    void update(int frameTimeMiliseconds) override
    {
        auto deltaTimeSeconds = (float)frameTimeMiliseconds / 1000;
        t += deltaTimeSeconds;
        shape.rotate(angularSpeed * deltaTimeSeconds);

        draw_background(color);
        draw_soild_color_object(shape);
    }

public:
    ColorWindow(std::string title, int width, int height, Color color) : Window(title, width, height), color(color)
    {
        shape = EquilateralTriangle(200, Color::blue);
        shape.set_position(width / 2, height / 2);
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
