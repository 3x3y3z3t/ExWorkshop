// ;
#pragma once

#include "Event.h"
#include "exw\input\MouseButtonCodes.h"

namespace exw
{
    namespace event
    {
        class MouseButtonEvent : public Event
        {
        protected:
            MouseButtonEvent(const MouseButtons _button)
                : m_Button(_button)
            {}

        public:
            EVENT_CATEGORY_INFO_DEFAULT_IMPL(EventCategoryInput | EventCategoryMouse | EventCategoryMouseButton)

            MouseButtons get_button() const { return m_Button; }

        protected:
            MouseButtons m_Button;
        };

        class MouseButtonPressedEvent : public MouseButtonEvent
        {
        public:
            MouseButtonPressedEvent(const MouseButtons _button)
                : MouseButtonEvent(_button)
            {}

        public:
            EVENT_TYPE_INFO_DEFAULT_IMPL(MouseButtonPressed)

            std::string to_string() const override
            {
                std::stringstream ss;
                ss << "MouseButtonPressedEvent: btn(" << m_Button << ")";
                return ss.str();
            }
        };

        class MouseButtonReleasedEvent : public MouseButtonEvent
        {
        public:
            MouseButtonReleasedEvent(const MouseButtons _button)
                : MouseButtonEvent(_button)
            {}

        public:
            EVENT_TYPE_INFO_DEFAULT_IMPL(MouseButtonReleased)

            std::string to_string() const override
            {
                std::stringstream ss;
                ss << "MouseButtonReleasedEvent: btn(" << m_Button << ")";
                return ss.str();
            }
        };

        class MouseMovedEvent : public Event
        {
        public:
            MouseMovedEvent(const float _x, const float _y)
                : m_X(_x), m_Y(_y)
            {}

        public:
            EVENT_TYPE_INFO_DEFAULT_IMPL(MouseMoved)
            EVENT_CATEGORY_INFO_DEFAULT_IMPL(EventCategoryInput | EventCategoryMouse)

            float get_x() const { return m_X; }
            float get_y() const { return m_Y; }

            std::string to_string() const override
            {
                std::stringstream ss;
                ss << "MouseMovedEvent: (" << m_X << ", " << m_Y << ")";
                return ss.str();
            }

        private:
            float m_X;
            float m_Y;
        };

        class MouseScrolledEvent : public Event
        {
        public:
            MouseScrolledEvent(const float _offsX, const float _offsY)
                : m_Offs_x(_offsX), m_Offs_y(_offsY)
            {}

        public:
            EVENT_TYPE_INFO_DEFAULT_IMPL(MouseScrolled)
            EVENT_CATEGORY_INFO_DEFAULT_IMPL(EventCategoryInput | EventCategoryMouse)

            float get_x_offset() const { return m_Offs_x; }
            float get_y_offset() const { return m_Offs_y; }

            std::string to_string() const override
            {
                std::stringstream ss;
                ss << "MouseScrolledEvent: (";
                if (m_Offs_x >= 0)
                    ss << "+";
                ss << m_Offs_x << ", ";
                if (m_Offs_y >= 0)
                    ss << "+";
                ss << m_Offs_y << ")";
                return ss.str();
            }

        private:
            float m_Offs_x;
            float m_Offs_y;
        };
    }
}
