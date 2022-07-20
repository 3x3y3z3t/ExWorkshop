/*  Common.h
*   Version: 1.1 (2022.07.21)
*
*   Contributor
*       Arime-chan
*/

#pragma once

#include <memory>

#define IS_FLAG_SET(_flags, _flag)      (_flags & _flag) != 0

namespace exw
{
    template<typename T>
    using ref = std::shared_ptr<T>;

    template<typename T, typename ... Args>
    constexpr ref<T> create_ref(Args&& ... _args)
    {
        return std::make_shared<T>(std::forward<Args>(_args)...);
    }

}
