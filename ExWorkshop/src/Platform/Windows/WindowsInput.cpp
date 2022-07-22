/*  WindowsInput.cpp
*   Version: 1.0 (2022.07.22)
*
*   Contributor
*       Arime-chan
*/
#include "exwpch.h"

#include "exw\Core\Application.h"
#include "exw\Core\Input.h"

#include <GLFW\glfw3.h>

namespace exw
{
    bool exw::Input::is_key_pressed(Keys::KeyCode _key)
    {
        auto* window = static_cast<GLFWwindow*>(Application::get().get_window().get_native_window());
        auto state = glfwGetKey(window, static_cast<int32_t>(_key));
        return state == GLFW_PRESS;
    }

    bool Input::is_mouse_btn_pressed(MouseBtn::MouseBtnCode _btn)
    {
        auto* window = static_cast<GLFWwindow*>(Application::get().get_window().get_native_window());
        auto state = glfwGetMouseButton(window, static_cast<int32_t>(_btn));
        return state == GLFW_PRESS;
    }

    std::pair<float, float> Input::get_cursor_pos()
    {
        auto* window = static_cast<GLFWwindow*>(Application::get().get_window().get_native_window());
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        return { (float)x, (float)y };
    }
}
