/*  Common.h
*   Version: 1.3 (2022.08.24)
*
*   Contributor
*       Arime-chan
*/
#pragma once

#define EXW_PLATFORM_WINDOW

#include <memory>

#define IS_FLAG_SET(_flags, _flag)      (_flags & _flag) != 0

#define EXW_STRINGIFY(x)        #x

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

#define EXW_ASSERT_CORE(_x, ...) if (!(_x)) EXW_LOG_CORE_CRITICAL(__VA_ARGS__)
#define EXW_ASSERT_CORE(_x) if (!(_x)) EXW_LOG_CORE_CRITICAL("Assertion false")