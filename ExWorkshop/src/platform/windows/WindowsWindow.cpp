// ;
#include "expch.h"
#include "WindowsWindow.h"

#include "exw\events\Events.h"
#include "exw\graphics\Renderer.h"

namespace exw
{
    static uint8_t s_GLFWwindow_count = 0U;

    static void glfw_error_callback(int _errCode, const char* _message) { EXW_LOG_ERROR("GLFW error {0}: {1}", _errCode, _message); }

    WindowsWindow::WindowsWindow(const WindowProperties& _properties)
    {
        EXW_PROFILE_FUNCTION();
        init(_properties);
    }

    WindowsWindow::~WindowsWindow()
    {
        EXW_PROFILE_FUNCTION();
        shutdown();
    }

    void WindowsWindow::update()
    {
        EXW_PROFILE_FUNCTION();
        glfwPollEvents();
        m_Context->swap_buffers();
    }

    bool WindowsWindow::is_vsync_set() const
    {
        return m_Data.vsync;
    }

    void WindowsWindow::set_vsync(bool _enabled)
    {
        EXW_PROFILE_FUNCTION();
        if (_enabled)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);

        m_Data.vsync = _enabled;
    }

    void WindowsWindow::init(const WindowProperties& _properties)
    {
        EXW_PROFILE_FUNCTION();
        m_Data.title = _properties.title;
        m_Data.width = _properties.width;
        m_Data.height = _properties.height;

        EXW_LOG_INFO("Creating window \"{0}\" ({1}, {2}) at default position..", _properties.title, _properties.width, _properties.height);

        if (s_GLFWwindow_count == 0)
        {
            int stat = glfwInit();
            EXW_ASSERT(stat, "GLFW initialization failure.");
            glfwSetErrorCallback(glfw_error_callback);
        }

        #if EXW_DBG
        if (graphics::Renderer::get_render_api() == graphics::RenderAPI::API::OpenGL)
            glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
        #endif

        m_Window = glfwCreateWindow((int)_properties.width, (int)_properties.height, _properties.title.c_str(), nullptr, nullptr);
        ++s_GLFWwindow_count;

        m_Context = graphics::GraphicsContext::create(m_Window);
        m_Context->init();

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
                    event::KeyPressedEvent evt(static_cast<Keys::KeyCode>(_key), 0);
                    data.callback(evt);
                    break;
                }
                case GLFW_RELEASE:
                {
                    event::KeyReleasedEvent evt(static_cast<Keys::KeyCode>(_key));
                    data.callback(evt);
                    break;
                }
                case GLFW_REPEAT:
                {
                    event::KeyPressedEvent evt(static_cast<Keys::KeyCode>(_key), 1);
                    data.callback(evt);
                    break;
                }
            }
        });

        glfwSetCharCallback(m_Window, [] (GLFWwindow* _window, uint32_t _keycode)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(_window);

            event::KeyTypedEvent evt(_keycode);
            data.callback(evt);
        });

        glfwSetMouseButtonCallback(m_Window, [] (GLFWwindow* _window, int _button, int _action, int _modifiers)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(_window);

            switch (_action)
            {
                case GLFW_PRESS:
                {
                    event::MouseButtonPressedEvent evt(static_cast<MouseButtons::ButtonCode>(_button));
                    data.callback(evt);
                    break;
                }
                case GLFW_RELEASE:
                {
                    event::MouseButtonPressedEvent evt(static_cast<MouseButtons::ButtonCode>(_button));
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



        //int ww = 0, hh = 0;
        //GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        //glfwGetMonitorPhysicalSize(monitor, &ww, &hh);
        //EXW_LOG_DEBUG("PhysicalScale = ({0}, {1})", ww, hh);
        //float fw = 0, fh = 0;
        //glfwGetMonitorContentScale(monitor, &fw, &fh);
        //EXW_LOG_DEBUG("ContentScale =  ({0}, {1})", fw, fh);
        //glfwGetWindowContentScale(m_Window, &fw, &fh);
        //EXW_LOG_DEBUG("WindowScale =   ({0}, {1})", fw, fh);



    }

    void WindowsWindow::shutdown()
    {
        EXW_PROFILE_FUNCTION();
        glfwDestroyWindow(m_Window);
        --s_GLFWwindow_count;

        if (s_GLFWwindow_count == 0)
        {
            glfwTerminate();
        }
    }
}
