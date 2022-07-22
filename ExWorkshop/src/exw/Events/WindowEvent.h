/*  WindowEvent.h
*   Version: 1.0 (2022.07.21)
*
*   Contributor
*       Arime-chan
*/
#pragma once

#include "Event.h"

namespace exw
{
    namespace events
    {
        class WindowResizedEvent : public Event
        {
        public:
            WindowResizedEvent(uint32_t _width, uint32_t _height)
                : m_Width(_width), m_Height(_height)
            {}

            EVENT_CLASS_TYPE(EventType::WindowResized)
            EVENT_CLASS_CATEGORY(EventCategory_Application)

            uint32_t get_width() const { return m_Width; }
            uint32_t get_height() const { return m_Height; }

            std::string to_string() const override
            {
                std::stringstream ss;
                ss << "WindowResizedEvent: " << m_Width << " x " << m_Height;
                return ss.str();
            }

        private:
            uint32_t m_Width = 0U;
            uint32_t m_Height = 0U;
        };

        class WindowClosedEvent : public Event
        {
        public:
            WindowClosedEvent() = default;

            EVENT_CLASS_TYPE(EventType::WindowClosed)
            EVENT_CLASS_CATEGORY(EventCategory_Application)
        };

    }
}
