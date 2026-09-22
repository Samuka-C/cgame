#ifndef CGAME_COLOR
#define CGAME_COLOR

#include <cstdint>
#include <string>

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

    Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);
public:
    #pragma region get methods
    std::string toString() const;

    int get_red_int() const;
    float get_red_float() const;

    int get_green_int() const;
    float get_green_float() const;

    int get_blue_int() const;
    float get_blue_float() const;

    int get_alpha_int() const;
    float get_alpha_float() const;

    #pragma endregion

    #pragma region static color pickers

    /**
     * @brief Create a color from its RGB values
     * 
     * @param red from 0 to 255
     * @param green from 0 to 255
     * @param blue from 0 to 255
     */
    static Color fromRGB(int red, int green, int blue);

    /**
     * @brief Create a color from its RGB values. plus the alpha value
     * 
     * @param red from 0 to 255
     * @param green from 0 to 255
     * @param blue from 0 to 255
     * @param alpha from 0 to 255
     */
    static Color fromRGB(int red, int green, int blue, int alpha);

    /**
     * @brief Create a color from its RGB values
     * 
     * @param red from 0.0 to 1.0
     * @param green from 0.0 to 1.0
     * @param blue from 0.0 to 1.0
     */
    static Color fromRGB(float red, float green, float blue);

    /**
     * @brief Create a color from its RGB values. plus the alpha value
     * 
     * @param red from 0.0 to 1.0
     * @param green from 0.0 to 1.0
     * @param blue from 0.0 to 1.0
     * @param alpha from 0.0 to 1.0
     */
    static Color fromRGB(float red, float green, float blue, float alpha);

    /**
     * @brief Create a color from its HSV values
     * 
     * @param hue from 0 to 360
     * @param saturation from 0.0 to 1.0
     * @param value from 0.0 to 1.0
     */
    static Color fromHSV(float hue, float saturation, float value);

    /**
     * @brief Create a color from its HSV values. plus the alpha value
     * 
     * @param hue from 0 to 360
     * @param saturation from 0.0 to 1.0
     * @param value from 0.0 to 1.0
     * @param alpha from 0.0 to 1.0
     */
    static Color fromHSV(float hue, float saturation, float value, float alpha);

    #pragma endregion

    #pragma region colors

    static const Color white;
    static const Color black;
    static const Color red;
    static const Color green;
    static const Color blue;

    #pragma endregion
};

#endif
