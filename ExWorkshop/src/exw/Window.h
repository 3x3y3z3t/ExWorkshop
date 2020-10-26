// ;
#pragma once

#include "exw\Common.h"
#include "exw\events\Event.h"

namespace exw
{
    struct WindowProperties
    {
        std::string title;
        uint32_t width;
        uint32_t height;

        WindowProperties(const std::string& _title = "Exw", uint32_t _width = 1280U, uint32_t _height = 720U)
            : title(_title), width(_width), height(_height)
        {}
    };

    class Window
    {
    public:
        using EventCallbackFunction = std::function<void(event::Event&)>;

    public:
        virtual ~Window() = default;

    public:
        virtual void update() = 0;

        virtual bool is_vsync_set() const = 0;
        virtual uint32_t get_width() const = 0;
        virtual uint32_t get_height() const = 0;
        virtual void* get_native_window() const = 0;

        virtual void set_event_callback(const EventCallbackFunction& _callback) = 0;
        virtual void set_vsync(bool _enabled) = 0;

        static refs::scope<Window> create(const WindowProperties& _properties = WindowProperties());
    };
}
