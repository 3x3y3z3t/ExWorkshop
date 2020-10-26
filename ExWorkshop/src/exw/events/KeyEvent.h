// ;
#pragma once

#include "Event.h"
#include "exw\input\KeyCodes.h"

namespace exw
{
    namespace event
    {
        class KeyEvent : public Event
        {
        protected:
            KeyEvent(const Keys _keycode)
                : m_Keycode(_keycode)
            {}

        public:
            EVENT_CATEGORY_INFO_DEFAULT_IMPL(EventCategoryInput | EventCategoryKeyboard)

            Keys get_keycode() const { return m_Keycode; }

        protected:
            Keys m_Keycode;
        };

        class KeyPressedEvent : public KeyEvent
        {
        public:
            KeyPressedEvent(const Keys _keycode, const uint16_t _repeatCount)
                : KeyEvent(_keycode), m_Repeat_count(_repeatCount)
            {}

        public:
            EVENT_TYPE_INFO_DEFAULT_IMPL(KeyPressed)

            uint16_t get_repeat_count() const { return m_Repeat_count; }

            std::string to_string() const override
            {
                std::stringstream ss;
                ss << "KeyPressedEvent: -> " << m_Keycode << " (x" << m_Repeat_count << ")";
                return ss.str();
            }

        private:
            int m_Repeat_count;
        };

        class KeyReleasedEvent : public KeyEvent
        {
        public:
            KeyReleasedEvent(const Keys _keycode)
                : KeyEvent(_keycode)
            {}

        public:
            EVENT_TYPE_INFO_DEFAULT_IMPL(KeyPressed)

            std::string to_string() const override
            {
                std::stringstream ss;
                ss << "KeyReleasedEvent: -> " << m_Keycode;
                return ss.str();
            }
        };

        class KeyTypedEvent : public KeyEvent
        {
        public:
            KeyTypedEvent(const Keys _keycode)
                : KeyEvent(_keycode)
            {}

        public:
            EVENT_TYPE_INFO_DEFAULT_IMPL(KeyPressed)

            std::string to_string() const override
            {
                std::stringstream ss;
                ss << "KeyTypedEvent: -> " << m_Keycode;
                return ss.str();
            }
        };
    }
}
