/*  WindowsGLFWWindow.cpp
*   Version: 1.2 (2022.08.24)
*
*   Contributor
*       Arime-chan
*/
#pragma once

#include "exw\core\Window.h"
#include "exw\graphics\GraphicsContext.h"

#include <GLFW\glfw3.h>

namespace exw
{
    class WindowsGLFWWindow : public Window
    {
    public:
        WindowsGLFWWindow(const WindowProperties& _props);
        virtual ~WindowsGLFWWindow();

        virtual void initialize_graphics_context() override;

        virtual void update() override;

        virtual bool is_vsync() const override;
        virtual uint32_t get_width() const override { return m_Data.Width; }
        virtual uint32_t get_height() const override { return m_Data.Height; }
        virtual void* get_native_window() const override { return m_Native_window; }

        virtual void set_vsync(bool _enable) override;
        virtual void set_event_callback(const EventCallbackFunc& _callback) override { m_Data.EvtCallbackFunc = _callback; }

    private:
        GLFWwindow* m_Native_window = nullptr;
        refs::Scoped<graphics::GraphicsContext> m_Graphics_context;

        struct WindowData
        {
            std::string Title;
            uint32_t Width = 0;
            uint32_t Height = 0;
            bool Vsync = false;
            EventCallbackFunc EvtCallbackFunc;
        } m_Data;
    };

}
