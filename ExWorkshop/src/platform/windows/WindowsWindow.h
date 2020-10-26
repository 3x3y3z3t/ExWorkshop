// ;
#pragma once

#include "exw\Window.h"

#include <GLFW\glfw3.h>

namespace exw
{
    class WindowsWindow : public Window
    {
    public:
        WindowsWindow(const WindowProperties& _properties);
        virtual ~WindowsWindow();

    public:
        void update() override;

        virtual bool is_vsync_set() const override;
        inline uint32_t get_width() const override { return m_Data.width; }
        inline uint32_t get_height() const override { return m_Data.height; }
        virtual void* get_native_window() const override { return m_Window; }

        virtual void set_event_callback(const EventCallbackFunction& _callback) override { m_Data.callback = _callback; }
        virtual void set_vsync(bool _enabled) override;
    private:
        virtual void init(const WindowProperties& _properties);
        virtual void shutdown();

    private:
        struct WindowData
        {
            std::string title;
            uint32_t width;
            uint32_t height;
            bool vsync;
            EventCallbackFunction callback;
        };

        GLFWwindow* m_Window;
        WindowData m_Data;
    };
}
