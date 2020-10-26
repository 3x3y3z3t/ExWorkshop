// ;
#pragma once

#include "Event.h"

namespace exw
{
    namespace event
    {
        class WindowCloseEvent : public Event
        {
        public:
            WindowCloseEvent() = default;

        public:
            EVENT_TYPE_INFO_DEFAULT_IMPL(WindowClose)
            EVENT_CATEGORY_INFO_DEFAULT_IMPL(EventCategoryApplication)
        };

        class WindowResizeEvent : public Event
        {
        private:
            uint32_t m_Width;
            uint32_t m_Height;

        public:
            WindowResizeEvent(uint32_t _width, uint32_t _height)
                : m_Width(_width), m_Height(_height)
            {}

        public:
            EVENT_TYPE_INFO_DEFAULT_IMPL(WindowResize)
            EVENT_CATEGORY_INFO_DEFAULT_IMPL(EventCategoryApplication)

            uint32_t get_width() const { return m_Width; }
            uint32_t get_height() const { return m_Height; }

            std::string to_string() const override
            {
                std::stringstream ss;
                ss << "WindowResizeEvent: -> (" << m_Width << ", " << m_Height << ")";
                return ss.str();
            }
        };
    }
}
