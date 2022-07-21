/*  WindowsGLFWWindow.cpp
*   Version: 1.0 (2022.07.21)
*
*   Contributor
*       Arime-chan
*/
#include "exwpch.h"
#include "WindowsGLFWWindow.h"

#include "ExWorkshop\Events\KeyEvent.h"
#include "ExWorkshop\Events\MouseEvent.h"
#include "ExWorkshop\Events\WindowEvent.h"
#include "ExWorkshop\Utils\Logger.h"

namespace exw
{
    static uint8_t s_GLFT_window_count = 0Ui8;

    static void glfw_err_callback(int _error, const char* _description)
    {
        EXW_CORE_LOG_ERROR("GLFW Error {0}: {1}", _error, _description);
    }

    WindowsGLFWWindow::WindowsGLFWWindow(const WindowProperties& _props)
    {
        m_Data.Title = _props.Title;
        m_Data.Width = _props.Width;
        m_Data.Height = _props.Height;

        EXW_CORE_LOG_TRACE("Creating window..");
        EXW_CORE_LOG_TRACE("  Window name : {0}", _props.Title);
        EXW_CORE_LOG_TRACE("  Window size : {0} x {1}", _props.Width, _props.Height);

        if (s_GLFT_window_count == 0)
        {
            int status = glfwInit();
            // TODO: assert status;
            glfwSetErrorCallback(glfw_err_callback);
        }

        m_Native_window = glfwCreateWindow((int)_props.Width, (int)_props.Height, _props.Title.c_str(), nullptr, nullptr);
        ++s_GLFT_window_count;
        glfwSetWindowAttrib(m_Native_window, GLFW_RESIZABLE, GLFW_FALSE);


        //m_Context = GraphicsContext::create(m_Native_window);
        //m_Context->init();

        glfwSetWindowUserPointer(m_Native_window, &m_Data);
        //set_vsync(true); // vsync is enable by default;

        #pragma region GLFW Callbacks Setup
        glfwSetWindowSizeCallback(m_Native_window, [] (GLFWwindow* _window, int _width, int _height)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(_window);
            data.Width = _width;
            data.Height = _height;

            events::WindowResizedEvent event(_width, _height);
            data.EvtCallbackFunc(event);
        });

        glfwSetWindowCloseCallback(m_Native_window, [] (GLFWwindow* _window)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(_window);

            events::WindowClosedEvent event;
            data.EvtCallbackFunc(event);
        });

        glfwSetKeyCallback(m_Native_window, [] (GLFWwindow* _window, int _key, int _scancode, int _action, int _mods)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(_window);

            switch (_action)
            {
                case GLFW_PRESS:
                {
                    events::KeyPressedEvent event((Keys::KeyCode)_key, 0);
                    data.EvtCallbackFunc(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    events::KeyReleasedEvent event((Keys::KeyCode)_key);
                    data.EvtCallbackFunc(event);
                    break;
                }
                case GLFW_REPEAT:
                {
                    events::KeyPressedEvent event((Keys::KeyCode)_key, true);
                    data.EvtCallbackFunc(event);
                    break;
                }
            }
        });

        glfwSetCharCallback(m_Native_window, [] (GLFWwindow* _window, uint32_t _keycode)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(_window);

            events::KeyTypedEvent event((Keys::KeyCode)_keycode);
            data.EvtCallbackFunc(event);
        });

        glfwSetMouseButtonCallback(m_Native_window, [] (GLFWwindow* _window, int _button, int _action, int _mods)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(_window);

            switch (_action)
            {
                case GLFW_PRESS:
                {
                    events::MouseButtonPressedEvent event((MouseBtn::MouseBtnCode)_button);
                    data.EvtCallbackFunc(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    events::MouseButtonReleasedEvent event((MouseBtn::MouseBtnCode)_button);
                    data.EvtCallbackFunc(event);
                    break;
                }
            }
        });

        glfwSetCursorPosCallback(m_Native_window, [] (GLFWwindow* _window, double _x, double _y)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(_window);

            events::MouseMovedEvent event((float)_x, (float)_y);
            data.EvtCallbackFunc(event);
        });

        glfwSetScrollCallback(m_Native_window, [] (GLFWwindow* _window, double _offsX, double _offsY)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(_window);

            events::MouseScrolledEvent event((float)_offsX, (float)_offsY);
            data.EvtCallbackFunc(event);
        });
        #pragma endregion

        glClearColor(0.9f, 0.2f, 0.2f, 1.0f);

        EXW_CORE_LOG_TRACE("  >> Done.");
    }

    WindowsGLFWWindow::~WindowsGLFWWindow()
    {
        glfwDestroyWindow(m_Native_window);
        --s_GLFT_window_count;

        if (s_GLFT_window_count == 0)
            glfwTerminate();
    }

    void WindowsGLFWWindow::update()
    {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(m_Native_window);
    }

    bool WindowsGLFWWindow::is_vsync() const
    {
        return m_Data.Vsync;
    }

    void exw::WindowsGLFWWindow::set_vsync(bool _enable)
    {
        if (_enable)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);

        m_Data.Vsync = _enable;
    }

}