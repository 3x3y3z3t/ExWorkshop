// ;
#include "expch.h"
#include "exw\input\Input.h"

#include "exw\Application.h"

#include <GLFW\glfw3.h>

namespace exw
{
    std::unordered_map<uint16_t, InputKey> Input::s_Mapping;

    bool Input::is_key_pressed(Keys::KeyCode _key)
    {
        auto* window = static_cast<GLFWwindow*>(Application::get().get_window().get_native_window());
        auto state = glfwGetKey(window, static_cast<int32_t>(_key));
        return (state == GLFW_PRESS || state == GLFW_REPEAT);
    }

    bool Input::is_mouse_button_pressed(MouseButtons::ButtonCode _button)
    {
        auto* window = static_cast<GLFWwindow*>(Application::get().get_window().get_native_window());
        auto state = glfwGetMouseButton(window, static_cast<int32_t>(_button));
        return (state == GLFW_PRESS);
    }

    maths::vector2 Input::get_cursor_position()
    {
        auto* window = static_cast<GLFWwindow*>(Application::get().get_window().get_native_window());
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        return { (float)x, (float)y };
    }

    float Input::get_cursor_pos_x()
    {
        return get_cursor_position().x;
    }
    float Input::get_cursor_pos_y()
    {
        return get_cursor_position().y;
    }
}
