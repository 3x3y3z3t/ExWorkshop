/*  Common.h
*   Version: 1.0 (2022.07.19)
*
*   Contributor
*       Arime-chan
*/

#pragma once

#include <memory>

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
