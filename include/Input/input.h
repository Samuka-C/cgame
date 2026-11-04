#ifndef CGAME_INPUT
#define CGAME_INPUT

#include <UI/window.h>
#include <Util/Math/vector.h>

using namespace cgame::ui;

namespace cgame::input
{

#pragma region keys

enum class KeyboardKey
{
    // Characters

    A = GLFW_KEY_A,
    B = GLFW_KEY_B,
    C = GLFW_KEY_C,
    D = GLFW_KEY_D,
    E = GLFW_KEY_E,
    F = GLFW_KEY_F,
    G = GLFW_KEY_G,
    H = GLFW_KEY_H,
    I = GLFW_KEY_I,
    J = GLFW_KEY_J,
    K = GLFW_KEY_K,
    L = GLFW_KEY_L,
    M = GLFW_KEY_M,
    N = GLFW_KEY_N,
    O = GLFW_KEY_O,
    P = GLFW_KEY_P,
    Q = GLFW_KEY_Q,
    R = GLFW_KEY_R,
    S = GLFW_KEY_S,
    T = GLFW_KEY_T,
    U = GLFW_KEY_U,
    V = GLFW_KEY_V,
    W = GLFW_KEY_W,
    X = GLFW_KEY_X,
    Y = GLFW_KEY_Y,
    Z = GLFW_KEY_Z,

    // Numbers (not key pad)

    N1 = GLFW_KEY_1,
    N2 = GLFW_KEY_2,
    N3 = GLFW_KEY_3,
    N4 = GLFW_KEY_4,
    N5 = GLFW_KEY_5,
    N6 = GLFW_KEY_6,
    N7 = GLFW_KEY_7,
    N8 = GLFW_KEY_8,
    N9 = GLFW_KEY_9,
    N0 = GLFW_KEY_0,

    // Special keys

    ENTER      = GLFW_KEY_ENTER,
    ESC        = GLFW_KEY_ESCAPE, 
    BACKSPACE  = GLFW_KEY_BACKSPACE,
    TAB        = GLFW_KEY_TAB, 
    SPACE      = GLFW_KEY_SPACE,
    MINUS      = GLFW_KEY_MINUS,         // - and _
    EQUAL      = GLFW_KEY_EQUAL,         // = and +
    LEFTBRACE  = GLFW_KEY_LEFT_BRACKET,  // [ and {
    RIGHTBRACE = GLFW_KEY_RIGHT_BRACKET, // ] and }
    BACKSLASH  = GLFW_KEY_BACKSLASH,     // \ and |
    SEMICOLON  = GLFW_KEY_SEMICOLON,     // ; and :
    APOSTROPHE = GLFW_KEY_APOSTROPHE,    // ' and "
    GRAVE      = GLFW_KEY_GRAVE_ACCENT,  // ` and ~
    COMMA      = GLFW_KEY_COMMA,         // , and <
    PERIOD     = GLFW_KEY_PERIOD,        // . and >
    SLASH      = GLFW_KEY_SLASH,         // / and ?
    CAPSLOCK   = GLFW_KEY_CAPS_LOCK,
    LSHIFT     = GLFW_KEY_LEFT_SHIFT,
    RSHIFT     = GLFW_KEY_RIGHT_SHIFT,
    LCONTROL   = GLFW_KEY_LEFT_CONTROL,
    RCONTROL   = GLFW_KEY_RIGHT_CONTROL,
    LALT       = GLFW_KEY_LEFT_ALT,
    RALT       = GLFW_KEY_RIGHT_ALT,
    LSUPER     = GLFW_KEY_LEFT_SUPER,    // Windows key, or Command key (for mac)
    RSUPER     = GLFW_KEY_RIGHT_SUPER,   // ^

    // F keys

    F1  = GLFW_KEY_F1,
    F2  = GLFW_KEY_F2,
    F3  = GLFW_KEY_F3,
    F4  = GLFW_KEY_F4,
    F5  = GLFW_KEY_F5,
    F6  = GLFW_KEY_F6,
    F7  = GLFW_KEY_F7,
    F8  = GLFW_KEY_F8,
    F9  = GLFW_KEY_F9,
    F10 = GLFW_KEY_F10,
    F11 = GLFW_KEY_F11,
    F12 = GLFW_KEY_F12,
    F13 = GLFW_KEY_F13,
    F14 = GLFW_KEY_F14,
    F15 = GLFW_KEY_F15,
    F16 = GLFW_KEY_F16,
    F17 = GLFW_KEY_F17,
    F18 = GLFW_KEY_F18,
    F19 = GLFW_KEY_F19,
    F20 = GLFW_KEY_F20,
    F21 = GLFW_KEY_F21,
    F22 = GLFW_KEY_F22,
    F23 = GLFW_KEY_F23,
    F24 = GLFW_KEY_F24,

    // Keys above arrow keys

    PRINTSRC   = GLFW_KEY_PRINT_SCREEN,
    SCROLLLOCK = GLFW_KEY_SCROLL_LOCK, 
    PAUSE      = GLFW_KEY_PAUSE,

    INSERT     = GLFW_KEY_INSERT, 
    HOME       = GLFW_KEY_HOME,
    PAGEUP     = GLFW_KEY_PAGE_UP, 
    DELETE     = GLFW_KEY_DELETE,
    END        = GLFW_KEY_END, 
    PAGEDOWN   = GLFW_KEY_PAGE_DOWN,

    // Arrow keys

    RIGHT = GLFW_KEY_RIGHT, 
    LEFT  = GLFW_KEY_LEFT,
    DOWN  = GLFW_KEY_DOWN, 
    UP    = GLFW_KEY_UP,

    // Key Pad

    NUMLOCK    = GLFW_KEY_NUM_LOCK,
    KPDOT      = GLFW_KEY_KP_DECIMAL,
    KPSLASH    = GLFW_KEY_KP_DIVIDE, 
    KPASTERISK = GLFW_KEY_KP_MULTIPLY,
    KPMINUS    = GLFW_KEY_KP_SUBTRACT, 
    KPPLUS     = GLFW_KEY_KP_ADD, 
    KPENTER    = GLFW_KEY_KP_ENTER,

    KPN1 = GLFW_KEY_KP_1, 
    KPN2 = GLFW_KEY_KP_2,
    KPN3 = GLFW_KEY_KP_3,
    KPN4 = GLFW_KEY_KP_4, 
    KPN5 = GLFW_KEY_KP_5,
    KPN6 = GLFW_KEY_KP_6, 
    KPN7 = GLFW_KEY_KP_7, 
    KPN8 = GLFW_KEY_KP_8, 
    KPN9 = GLFW_KEY_KP_9, 
    KPN0 = GLFW_KEY_KP_0,
};

enum class MouseButton
{
    LBUTTON = GLFW_MOUSE_BUTTON_LEFT,
    RBUTTON = GLFW_MOUSE_BUTTON_RIGHT,
    MBUTTON = GLFW_MOUSE_BUTTON_MIDDLE,
};

#pragma endregion

#pragma region get input state

/**
 * @brief tells if a key is being pressed down.
 * 
 * @attention returns the state of the key on the currently focused window. if there are no focused windows, returns false.
 * 
 * @param key the keyboard key being verified.
 */
bool isKeyPressed(KeyboardKey key);

/**
 * @brief tells if a key is being pressed down.
 * 
 * @attention the returned state of the key might be different from reality if the window provided is not in focus.
 * 
 * @param key the keyboard key being verified.
 * 
 * @param window the window where the last state of the key is pulled from.
 */
bool isKeyPressed(KeyboardKey key, Window& window);

/**
 * @brief tells if a mouse button is being pressed down.
 * 
 * @attention returns the state of the key on the currently focused window. if there are no focused windows, returns false.
 * 
 * @param button the mouse button being verified.
 */
bool isMouseKeyPressed(MouseButton button);

/**
 * @brief tells if a mouse button is being pressed down.
 * 
 * @attention the returned state of the key might be different from reality if the window provided is not in focus.
 * 
 * @param button the mouse button being verified.
 * 
 * @param window the window where the last state of the mouse is pulled from.
 */
bool isMouseKeyPressed(MouseButton button, Window& window);

/**
 * @brief returns the mouse position. relative to the window.
 * 
 * @param window the window to pull the mouse location.
 * 
 * @param overrideMode If not set, the mouse coordinates will follow the coordinate system of the window
 */
Vec2d getMousePos(Window& window, WindowCoordinateSystemMode overrideMode = WindowCoordinateSystemMode::None);

#pragma endregion

}

#endif