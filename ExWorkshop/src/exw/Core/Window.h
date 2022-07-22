/*  Window.h
*   Version: 1.0 (2022.07.21)
*
*   Contributor
*       Arime-chan
*/
#pragma once
#include "exwpch.h"

#include "exw\Common.h"
#include "exw\Events\Event.h"

namespace exw
{
    struct WindowProperties
    {
        std::string Title;
        uint32_t Width = 0;
        uint32_t Height = 0;

        WindowProperties(const std::string& _title = "ExWorkshop", uint32_t _width = 1600, uint32_t _height = 900)
            : Title(_title), Width(_width), Height(_height)
        {}
    };

    class Window
    {
    public:
        using EventCallbackFunc = std::function<void(events::Event&)>;

        virtual ~Window() = default;

        static refs::Scoped<Window> create(const WindowProperties& _prop = WindowProperties());

        virtual void update() = 0;

        virtual bool is_vsync() const = 0;
        virtual uint32_t get_width() const = 0;
        virtual uint32_t get_height() const = 0;
        virtual void* get_native_window() const = 0;

        virtual void set_vsync(bool _enable) = 0;
        virtual void set_event_callback(const EventCallbackFunc& _callback) = 0;
    };

}
