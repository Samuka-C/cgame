#include <Logger/logger.h>
#include <Util/Color/color.h>

#include <cstdint>
#include <cmath>

#pragma region helper methods

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

float fix_angle(float angle)
{
    while (angle < 0)
    {
        angle += 360;
    }

    while (angle > 360)
    {
        angle -= 360;
    }

    return angle;
}

#pragma endregion

#pragma region constructor

Color::Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
    R = from_int(red);
    G = from_int(green);
    B = from_int(blue);
    A = from_int(alpha);
}

#pragma endregion

#pragma region get methods

std::string Color::toString() const
{
    return std::to_string(R) + ", " + std::to_string(G) + ", " + std::to_string(B) + ", " + std::to_string(A);
}

int Color::get_red_int() const
{
    return to_int(R);
}

float Color::get_red_float() const
{
    return to_float(R);
}

int Color::get_green_int() const
{
    return to_int(G);
}

float Color::get_green_float() const
{
    return to_float(G);
}

int Color::get_blue_int() const
{
    return to_int(B);
}

float Color::get_blue_float() const
{
    return to_float(B);
}

int Color::get_alpha_int() const
{
    return to_int(A);
}

float Color::get_alpha_float() const
{
    return to_float(A);
}

#pragma endregion

#pragma region static color pickers

Color Color::fromRGB(int red, int green, int blue)
{
    return Color::fromRGB(red, green, blue, 255);
}

Color Color::fromRGB(int red, int green, int blue, int alpha)
{
    return Color(from_int(red), from_int(green), from_int(blue), from_int(alpha));
}

Color Color::fromRGB(float red, float green, float blue)
{
    return Color::fromRGB(red, green, blue, 1.0f);
}

Color Color::fromRGB(float red, float green, float blue, float alpha)
{
    return Color(from_float(red), from_float(green), from_float(blue), from_float(alpha));
}

Color Color::fromHSV(float hue, float saturation, float value)
{
    return Color::fromHSV(hue, saturation, value, 1.0f);
}

Color Color::fromHSV(float hue, float saturation, float value, float alpha)
{
    // based on formula found on https://www.rapidtables.com/convert/color/hsv-to-rgb.html

    hue = fix_angle(hue);
    
    float red, green, blue;
    float C = value * saturation;
    float X = C * (1 - std::abs(std::fmod(hue / 60, 2) - 1));
    float m = value - C;

    int range = std::trunc(hue / 60);
    switch (range)
    {
    case 0:
        red = C;
        green = X;
        blue = 0;
        break;
    case 1:
        red = X;
        green = C;
        blue = 0;
        break;
    case 2:
        red = 0;
        green = C;
        blue = X;
        break;
    case 3:
        red = 0;
        green = X;
        blue = C;
        break;
    case 4:
        red = X;
        green = 0;
        blue = C;
        break;
    case 5:
        red = C;
        green = 0;
        blue = X;
        break;
    default:
        break;
    }

    red += m;
    green += m;
    blue += m;

    return Color::fromRGB(red, green, blue, alpha);
}

#pragma endregion

#pragma region colors

const Color Color::white = Color::fromRGB(255, 255, 255);
const Color Color::black = Color::fromRGB(  0,   0,   0);
const Color Color::red   = Color::fromRGB(255,   0,   0);
const Color Color::green = Color::fromRGB(  0, 255,   0);
const Color Color::blue  = Color::fromRGB(  0,   0, 255);

#pragma endregion
