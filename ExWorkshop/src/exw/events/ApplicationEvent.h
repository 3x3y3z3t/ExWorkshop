// ;
#pragma once

#include "Event.h"

namespace exw
{
    namespace event
    {
        class AppTickEvent : public Event
        {
        public:
            AppTickEvent() = default;

        public:
            EVENT_TYPE_INFO_DEFAULT_IMPL(AppTick)
            EVENT_CATEGORY_INFO_DEFAULT_IMPL(EventCategoryApplication)
        };

        class AppUpdateEvent : public Event
        {
        public:
            AppUpdateEvent() = default;

        public:
            EVENT_TYPE_INFO_DEFAULT_IMPL(AppUpdate)
            EVENT_CATEGORY_INFO_DEFAULT_IMPL(EventCategoryApplication)
        };

        class AppRenderEvent : public Event
        {
        public:
            AppRenderEvent() = default;

        public:
            EVENT_TYPE_INFO_DEFAULT_IMPL(AppTick)
            EVENT_CATEGORY_INFO_DEFAULT_IMPL(EventCategoryApplication)
        };
    }
}
