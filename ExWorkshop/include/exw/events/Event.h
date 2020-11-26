// ;
#pragma once
#include "expch.h"

#include "exw\Common.h"

namespace exw
{
    namespace event
    {
        enum class EventType
        {
            None = 0,
            WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
            AppTick, AppUpdate, AppRender,
            KeyPressed, KeyReleased, KeyTyped,
            MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled,
        };

        enum EventCategory
        {
            /* NOTICE: manage this carefully!! */
            None = 0,
            EventCategoryApplication =      BIT(0),
            EventCategoryInput =            BIT(1),
            EventCategoryKeyboard =         BIT(2),
            EventCategoryMouse =            BIT(3),
            EventCategoryMouseButton =      BIT(4),
        };

        #define EVENT_TYPE_INFO_DEFAULT_IMPL(_type)                                     \
            virtual EventType get_type() const override { return EventType::_type; }    \
            virtual const char* get_name() const override { return #_type; }            \
            static EventType type() { return EventType::_type; }

        #define EVENT_CATEGORY_INFO_DEFAULT_IMPL(_category)                             \
            virtual int get_category_flags() const override { return _category; }

        class Event
        {
        public:
            virtual ~Event() = default;

        public:
            inline bool is_category(EventCategory _category) const { return IS_FLAG_SET(get_category_flags(), _category); }

            virtual EventType get_type() const = 0;
            virtual const char* get_name() const = 0;
            virtual int get_category_flags() const = 0;

            virtual std::string to_string() const { return std::string("Event::").append(get_name()); }

        public:
            bool Handled = false;
        };

        class EventDispatcher
        {
        public:
            EventDispatcher(Event& _evt)
                : m_Event(_evt)
            {}

        public:
            template<typename T, typename Func>
            bool dispatch(const Func& _func)
            {
                if (m_Event.get_type() == T::type())
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

inline std::ostream& operator<<(std::ostream& _os, const exw::event::Event& _evt) { return _os << _evt.to_string(); }
