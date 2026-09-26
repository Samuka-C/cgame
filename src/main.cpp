#include <UI/window.h>
#include <Logger/logger.h>

#include <thread>
#include <atomic>
#include <cmath>
#include <algorithm>

class PongWindow : public Window
{
private:
    Color color;
    float t = 0.0f;
    Angle angularSpeed = Angle::degrees(180);
    SolidColorObject rightPaddle;
    SolidColorObject leftPaddle;
    SolidColorObject ball;
    Vec2d ballSpeed;

    void update(int frameTimeMiliseconds) override
    {
        auto deltaTimeSeconds = (float)frameTimeMiliseconds / 1000;
        t += deltaTimeSeconds;

        auto width = getWidth();
        auto height = getHeight();

        if (ball.get_position().x <= 50 and ballSpeed.x < 0)
        {
            ballSpeed.x *= -1;
        }

        if (ball.get_position().x >= width - 50 and ballSpeed.x > 0)
        {
            ballSpeed.x *= -1;
        }

        if (ball.get_position().y <= 30 and ballSpeed.y < 0)
        {
            ballSpeed.y *= -1;
        }

        if (ball.get_position().y >= height - 30 and ballSpeed.y > 0)
        {
            ballSpeed.y *= -1;
        }

        auto deltaBall = ballSpeed * deltaTimeSeconds;
        ball.move(deltaBall);

        auto paddleY = std::clamp<double>(ball.get_position().y, 100, height - 100);

        leftPaddle.set_position(10, paddleY);
        rightPaddle.set_position(width - 10, paddleY);

        draw_background(color);
        draw_solid_color_object(rightPaddle);
        draw_solid_color_object(leftPaddle);
        draw_solid_color_object(ball);
    }

public:
    PongWindow(std::string title, int width, int height, Color color) : 
        Window(title, width, height), 
        color(color), 
        rightPaddle(Rectangle(20, 200, Color::black)),
        leftPaddle(Rectangle(20, 200, Color::black)),
        ball(RegularPolygon(30, 12, Color::black)),
        ballSpeed(Vec2d(400, 800))
    {
        set_coordinate_system(WindowCoordinateSystemMode::TopLeft);
        leftPaddle.set_position(10, height / 2);
        rightPaddle.set_position(width - 10, height / 2);
        ball.set_position(width / 2, height / 2);
    }   
};

int main()
{
    Window::start_glfw();

    PongWindow pong("AI pong", 800, 800, Color::white);

    pong.start();

    while (Window::isAnyWindowRunning());

    Window::terminate_glfw();

    return 0;
}
