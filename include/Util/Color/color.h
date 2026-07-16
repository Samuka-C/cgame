#ifndef CGAME_COLOR
#define CGAME_COLOR

#include <cstdint>

/**
 * @brief stores the data about a color (with transparency)
 */
class Color
{
private:
    uint8_t R;
    uint8_t G;
    uint8_t B;
    uint8_t A;
public:
    Color(int red, int green, int blue, int alpha);
    Color(int red, int green, int blue);
    Color(float red, float green, float blue, float alpha);
    Color(float red, float green, float blue);

    int get_red_int();
    float get_red_float();

    int get_green_int();
    float get_green_float();

    int get_blue_int();
    float get_blue_float();

    int get_alpha_int();
    float get_alpha_float();
};

#endif
