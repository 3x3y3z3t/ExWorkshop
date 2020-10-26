// ;
#include "expch.h"
#include "WindowsWindow.h"

#include "exw\events\Events.h"

namespace exw
{
    static uint8_t s_GLFWwindow_count = 0U;

    WindowsWindow::WindowsWindow(const WindowProperties& _properties)
    {
        init(_properties);
    }

    WindowsWindow::~WindowsWindow()
    {
        shutdown();
    }

    void WindowsWindow::update()
    {
        glfwPollEvents();
    }

    bool WindowsWindow::is_vsync_set() const
    {
        return m_Data.vsync;
    }

    void WindowsWindow::set_vsync(bool _enabled)
    {
        if (_enabled)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);

        m_Data.vsync = _enabled;
    }

    void WindowsWindow::init(const WindowProperties& _properties)
    {
        m_Data.title = _properties.title;
        m_Data.width = _properties.width;
        m_Data.height = _properties.height;

        if (s_GLFWwindow_count == 0)
        {
            int stat = glfwInit();
            EXW_ASSERT(stat, "GLFW initialization failure.");
        }

        m_Window = glfwCreateWindow((int)_properties.width, (int)_properties.height, _properties.title.c_str(), nullptr, nullptr);
        ++s_GLFWwindow_count;

        glfwSetWindowUserPointer(m_Window, &m_Data);
        set_vsync(true); // to save your GPU :))

        glfwSetWindowSizeCallback(m_Window, [] (GLFWwindow* _window, int _width, int _height)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(_window);
            data.width = _width;
            data.height = _height;

            event::WindowResizeEvent evt(_width, _height);
            data.callback(evt);
        });

        glfwSetWindowCloseCallback(m_Window, [] (GLFWwindow* _window)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(_window);

            event::WindowCloseEvent evt;
            data.callback(evt);
        });

        glfwSetKeyCallback(m_Window, [] (GLFWwindow* _window, int _key, int _scancode, int _action, int _modifiers)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(_window);

            switch (_action)
            {
                case GLFW_PRESS:
                {
                    event::KeyPressedEvent evt(_key, 0);
                    data.callback(evt);
                    break;
                }
                case GLFW_RELEASE:
                {
                    event::KeyReleasedEvent evt(_key);
                    data.callback(evt);
                    break;
                }
                case GLFW_REPEAT:
                {
                    event::KeyPressedEvent evt(_key, 1);
                    data.callback(evt);
                    break;
                }
            }
        });

        glfwSetCharCallback(m_Window, [] (GLFWwindow* _window, uint32_t _keycode)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(_window);

            event::KeyTypedEvent evt(static_cast<Keys>(_keycode));
            data.callback(evt);
        });

        glfwSetMouseButtonCallback(m_Window, [] (GLFWwindow* _window, int _button, int _action, int _modifiers)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(_window);

            switch (_action)
            {
                case GLFW_PRESS:
                {
                    event::MouseButtonPressedEvent evt(static_cast<MouseButtons>(_button));
                    data.callback(evt);
                    break;
                }
                case GLFW_RELEASE:
                {
                    event::MouseButtonPressedEvent evt(static_cast<MouseButtons>(_button));
                    data.callback(evt);
                    break;
                }
            }
        });

        glfwSetScrollCallback(m_Window, [] (GLFWwindow* _window, double _xOffs, double _yOffs)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(_window);

            event::MouseScrolledEvent evt((float)_xOffs, (float)_yOffs);
            data.callback(evt);
        });

        glfwSetCursorPosCallback(m_Window, [] (GLFWwindow* _window, double _xPos, double _yPos)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(_window);

            event::MouseMovedEvent evt((float)_xPos, (float)_yPos);
            data.callback(evt);
        });
    }

    void WindowsWindow::shutdown()
    {
        glfwDestroyWindow(m_Window);
        --s_GLFWwindow_count;

        if (s_GLFWwindow_count == 0)
        {
            glfwTerminate();
        }
    }
}
