/*  Event.h
*   Version: 1.2 (2022.07.22)
*
*   Contributor
*       Arime-chan
*/
#pragma once
#include"exwpch.h"

#include "exw\Common.h"

#pragma warning(disable:26812)
namespace exw
{
    namespace events
    {
        #define EVENT_CLASS_TYPE(_type)                                                             \
            static EventType get_event_type_static() { return _type; }                              \
            virtual EventType get_event_type() const override { return get_event_type_static(); }   \
            virtual const char* get_event_name() const override { return #_type; }

        #define EVENT_CLASS_CATEGORY(_category)                                                     \
            virtual int get_category_flags() const override { return _category; }


        enum class EventType
        {
            None = 0,
            WindowResized, WindowMoved, WindowFocused, WindowLostFocus, WindowClosed,
            KeyPressed, KeyReleased, KeyTyped,
            MouseButtonPressed, MouseButtonReleased, MouseButtonClicked, MouseMoved, MouseScrolled
        };

        enum EventCategory : uint32_t
        {
            None = 0,
            EventCategory_Application = 1 << 0,
            EventCategory_Input =       1 << 1,
            EventCategory_Keyboard =    1 << 2,
            EventCategory_Mouse =       1 << 3,
            EventCategory_MouseBtn =    1 << 4,
        };

        /* Remember to implement requiired member function using EVENT_CLASS_TYPE and EVENT_CLASS_CATEGORY macro. */
        class Event
        {
        public:
            bool Handled = false;

            virtual ~Event() = default;

            virtual EventType get_event_type() const = 0;
            virtual const char* get_event_name() const = 0;
            virtual int get_category_flags() const = 0;

            virtual std::string to_string() const { return get_event_name(); }

            bool is_event_of_category(EventCategory _category)
            {
                return IS_FLAG_SET((uint32_t)get_category_flags(), (uint32_t)_category);
            }
        };

        class EventDispatcher
        {
        public:
            EventDispatcher(Event& _event)
                : m_Event(_event)
            {}

            template<typename T, typename Func>
            bool dispatch(const Func& _func)
            {
                if (m_Event.get_event_type() == T::get_event_type_static())
                {
                    m_Event.Handled |= _func(static_cast<T&>(m_Event));
                    return true;
                }

                return false;
            }

        private:
            Event& m_Event;
        };

    }
}

#pragma warning(default:26812)
