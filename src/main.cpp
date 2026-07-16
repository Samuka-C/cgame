#include <UI/window.h>
#include <Logger/logger.h>

int main()
{
    start_glfw();

    Window new_window("test", 600, 800);

    while (new_window.loop_condition())
    {
        new_window.draw_background(Color(0.2f, 0.3f, 0.8f));
        new_window.pollEvents();
    }

    terminate_glfw();
}


