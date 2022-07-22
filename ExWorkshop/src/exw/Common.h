/*  Common.h
*   Version: 1.2 (2022.07.21)
*
*   Contributor
*       Arime-chan
*/
#pragma once

#define EXW_PLATFORM_WINDOW

#include <memory>

#define IS_FLAG_SET(_flags, _flag)      (_flags & _flag) != 0

namespace exw
{
    namespace refs
    {
        template<typename T>
        using Ref = std::shared_ptr<T>;

        template<typename T, typename ... Args>
        constexpr Ref<T> create_ref(Args&& ... _args)
        {
            return std::make_shared<T>(std::forward<Args>(_args)...);
        }

        template<typename T>
        using Scoped = std::unique_ptr<T>;

        template<typename T, typename ... Args>
        constexpr Scoped<T> create_scoped(Args&& ... _args)
        {
            return std::make_unique<T>(std::forward<Args>(_args)...);
        }

    }
}
