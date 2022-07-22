/*  MouseEvent.h
*   Version: 1.1 (2022.07.22)
*
*   Contributor
*       Arime-chan
*/
#pragma once

#include "Event.h"
#include "KeyCodes.h"

#pragma warning(disable:26812)
namespace exw
{
    namespace events
    {
        class MouseButtonEvent : public Event
        {
        protected:
            MouseButtonEvent(const MouseBtn::MouseBtnCode _btncode)
                : m_Button_code(_btncode)
            {}

        public:
            EVENT_CLASS_CATEGORY(EventCategory_Input | EventCategory_Mouse | EventCategory_MouseBtn)

            MouseBtn::MouseBtnCode get_key_code() const { return m_Button_code; }

        protected:
            MouseBtn::MouseBtnCode m_Button_code;
        };

        class MouseButtonPressedEvent : public MouseButtonEvent
        {
        public:
            MouseButtonPressedEvent(const MouseBtn::MouseBtnCode _btncode, int _repeatCount = 0)
                : MouseButtonEvent(_btncode), m_Repeat_count(_repeatCount)
            {}

            EVENT_CLASS_TYPE(EventType::MouseButtonPressed)

            bool is_repeated() const { return m_Repeat_count > 0; }
            int get_repeat_count() const { return m_Repeat_count; }

            std::string to_string() const override
            {
                std::stringstream ss;
                ss << "MouseButtonPressedEvent: " << m_Button_code << " (x" << m_Repeat_count << ")";
                return ss.str();
            }

        private:
            int m_Repeat_count = 0;
        };

        class MouseButtonReleasedEvent : public MouseButtonEvent
        {
        public:
            MouseButtonReleasedEvent(const MouseBtn::MouseBtnCode _btncode)
                : MouseButtonEvent(_btncode)
            {}

            EVENT_CLASS_TYPE(EventType::MouseButtonReleased)

            std::string to_string() const override
            {
                std::stringstream ss;
                ss << "MouseButtonReleasedEvent: " << m_Button_code;
                return ss.str();
            }
        };

        class MouseButtonClickedEvent : public MouseButtonEvent
        {
        public:
            MouseButtonClickedEvent(const MouseBtn::MouseBtnCode _btncode, int _clickCount = 1)
                : MouseButtonEvent(_btncode), m_Click_count(_clickCount)
            {}

            EVENT_CLASS_TYPE(EventType::MouseButtonClicked)

            std::string to_string() const override
            {
                std::stringstream ss;
                ss << "MouseButtonClickedEvent: " << m_Button_code << " (x" << m_Click_count<< ")";
                return ss.str();
            }

        private:
            int m_Click_count = 0;
        };

        class MouseMovedEvent : public Event
        {
        public:
            MouseMovedEvent(const float _x, const float _y)
                : m_Cursor_x(_x), m_Cursor_y(_y)
            {}

            EVENT_CLASS_TYPE(EventType::MouseMoved)
            EVENT_CLASS_CATEGORY(EventCategory_Input | EventCategory_Mouse)

            float get_x() const { return m_Cursor_x; }
            float get_y() const { return m_Cursor_x; }

            std::string to_string() const override
            {
                std::stringstream ss;
                ss << "MouseMovedEvent: (" << m_Cursor_x << ", " << m_Cursor_y << ")";
                return ss.str();
            }

        private:
            float m_Cursor_x = 0.0f;
            float m_Cursor_y = 0.0f;
        };

        class MouseScrolledEvent : public Event
        {
        public:
            MouseScrolledEvent(const float _offsX, const float _offsY)
                : m_Offs_x(_offsX), m_Offs_y(_offsY)
            {}

            EVENT_CLASS_TYPE(EventType::MouseScrolled)
            EVENT_CLASS_CATEGORY(EventCategory_Input | EventCategory_Mouse)

            float get_offset_x() const { return m_Offs_x; }
            float get_offset_y() const { return m_Offs_y; }

            std::string to_string() const override
            {
                std::stringstream ss;
                ss << "MouseScrolledEvent: (" << m_Offs_x << ", " << m_Offs_y << ")";
                return ss.str();
            }

        private:
            float m_Offs_x = 0.0f;
            float m_Offs_y = 0.0f;
        };

    }
}
#pragma warning(restore:26812)
