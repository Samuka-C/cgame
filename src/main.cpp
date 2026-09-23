#include <UI/window.h>
#include <Logger/logger.h>

#include <thread>
#include <atomic>
#include <cmath>

class ColorWindow : public Window
{
private:
    Color color;
    float t = 0.0f;
    Angle angularSpeed = Angle::degrees(180);
    SolidColorObject shape;

    void update(int frameTimeMiliseconds) override
    {
        auto deltaTimeSeconds = (float)frameTimeMiliseconds / 1000;
        t += deltaTimeSeconds;
        shape.rotate(angularSpeed * deltaTimeSeconds);

        draw_background(color);
        draw_soild_color_object(shape);
    }

public:
    ColorWindow(std::string title, int width, int height, Color color) : 
        Window(title, width, height), 
        color(color), 
        shape(EquilateralTriangle(260, Color::black))
    {
        set_coordinate_system(WindowCoordinateSystemMode::Center);
        shape.set_position(30, -90);
    }   
};

int main()
{
    Window::start_glfw();

    ColorWindow red_window("red", 800, 800, Color::white);

    red_window.start();

    while (Window::isAnyWindowRunning());

    Window::terminate_glfw();

    return 0;
}
