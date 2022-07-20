/*  KeyEvent.h
*   Version: 1.0 (2022.07.21)
*
*   Contributor
*       Arime-chan
*/
#pragma once
#include "exwpch.h"

#include "Event.h"
#include "KeyCodes.h"

namespace exw
{
    namespace events
    {
        class KeyEvent : public Event
        {
        protected:
            KeyEvent(const Keys::KeyCode _keycode)
                : m_Key_code(_keycode)
            {}

        public:
            EVENT_CLASS_CATEGORY(EventCategory_Input | EventCategory_Keyboard)

            Keys::KeyCode get_key_code() const { return m_Key_code; }

        protected:
            Keys::KeyCode m_Key_code;
        };

        class KeyPressedEvent : public KeyEvent
        {
        public:
            KeyPressedEvent(const Keys::KeyCode _keycode, int _repeatCount = 0)
                : KeyEvent(_keycode), m_Repeat_count(_repeatCount)
            {}

            EVENT_CLASS_TYPE(EventType::KeyPressed)

            bool is_repeated() const { return m_Repeat_count > 0; }
            int get_repeat_count() const { return m_Repeat_count; }

            std::string to_string() const override
            {
                std::stringstream ss;
                ss << "KeyPressedEvent: " << m_Key_code << " (x" << m_Repeat_count << ")";
                return ss.str();
            }

        private:
            int m_Repeat_count = 0;
        };

        class KeyReleasedEvent : public KeyEvent
        {
        public:
            KeyReleasedEvent(const Keys::KeyCode _keycode)
                : KeyEvent(_keycode)
            {}

            EVENT_CLASS_TYPE(EventType::KeyReleased)

            std::string to_string() const override
            {
                std::stringstream ss;
                ss << "KeyReleasedEvent: " << m_Key_code;
                return ss.str();
            }
        };

        class KeyTypedEvent : public KeyEvent
        {
        public:
            KeyTypedEvent(const Keys::KeyCode _keycode)
                : KeyEvent(_keycode)
            {}

            EVENT_CLASS_TYPE(EventType::KeyTyped)

            std::string to_string() const override
            {
                std::stringstream ss;
                ss << "KeyTypedEvent: " << m_Key_code;
                return ss.str();
            }
        };

    }
}
