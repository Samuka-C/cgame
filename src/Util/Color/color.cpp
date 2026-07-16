#include <Logger/logger.h>
#include <Util/Color/color.h>

#include <cstdint>

uint8_t from_float(float value)
{
    if (value < 0.0f)
    {
        log_error("value: %f is negative", value);
        return (uint8_t)0;
    }

    if (value > 1.0f)
    {
        log_error("value: %f is greater than one", value);
        return (uint8_t)(0xFF);
    }

    return (uint8_t)(0xFF * value); 
}

uint8_t from_int(int value)
{
    if (value < 0)
    {
        log_error("value: %d is negative", value);
        return (uint8_t)0;
    }

    if (value > 255)
    {
        log_error("value: %d is greater than 255", value);
        return (uint8_t)(0xFF);
    }

    return (uint8_t)(value); 
}

int to_int(uint8_t value)
{
    return (int)value;
}

float to_float(uint8_t value)
{
    return (float)value / 0xFF;
}

Color::Color(int red, int green, int blue, int alpha)
{
    R = from_int(red);
    G = from_int(green);
    B = from_int(blue);
    A = from_int(alpha);
}

Color::Color(int red, int green, int blue)
{
    R = from_int(red);
    G = from_int(green);
    B = from_int(blue);
    A = (uint8_t)(0xFF);
}

Color::Color(float red, float green, float blue, float alpha)
{
    R = from_float(red);
    G = from_float(green);
    B = from_float(blue);
    A = from_float(alpha);
}

Color::Color(float red, float green, float blue)
{
    R = from_float(red);
    G = from_float(green);
    B = from_float(blue);
    A = (uint8_t)(0xFF);
}

int Color::get_red_int()
{
    return to_int(R);
}

float Color::get_red_float()
{
    return to_float(R);
}

int Color::get_green_int()
{
    return to_int(G);
}

float Color::get_green_float()
{
    return to_float(G);
}

int Color::get_blue_int()
{
    return to_int(B);
}

float Color::get_blue_float()
{
    return to_float(B);
}

int Color::get_alpha_int()
{
    return to_int(A);
}

float Color::get_alpha_float()
{
    return to_float(A);
}
