// ;
#pragma once
#include "expch.h"

#pragma region Platform Detection

#ifdef _WIN32
    #ifdef _WIN64
        #define EXW_PLATFORM_WINDOWS
    #else
        #error "Windows x86 build is not supported"
    #endif
#else
    #error "Unsupported platform"
#endif

#pragma endregion

#ifdef EXW_DBG
    #if defined(EXW_PLATFORM_WINDOWS)
        #define EXW_DEBUGBREAK() __debugbreak()
    #elif defined(EXW_PLATFORM_LINUX)
        #include <signal.h>
        #define EXW_DEBUGBREAK() raise(SIGTRAP)
    #else
        #error "Platform doesn't support debugbreak"
    #endif
    //#define EXW_ENABLE_ASSERTS
#else
    #define EXW_DEBUGBREAK() 
#endif

#define EXW_EXPAND(_x) _x
#define EXW_STRINGIFY(_x) #_x

#define BIT(_x) (1 << _x)
#define BIT_AT(_integer, _pos) ((_integer >> _pos) % 2)
#define TEST(_integer, _pos) (BIT_AT(_integer, _pos) != 0)

#define IS_FLAG_SET(_flags, _flag) ((_flags & _flag) != 0)

#define EXW_BIND_EVENT_FUNCTION(_func) [this](auto&&... _args) -> decltype(auto) { return this->_func(std::forward<decltype(_args)>(_args)...); }

#define this_typeid_name() typeid(*this).name()


#ifdef EXW_ENABLE_ASSERTS
    #define EXW_ASSERT(_x, ...) { if(!(_x)) { EXW_LOG_ERROR("Assertion failed: {0}", __VA_ARGS__); EXW_DEBUGBREAK(); } }
#else
    #define EXW_ASSERT(_x, ...)
#endif

namespace exw
{
    namespace refs
    {
        template<typename T>
        using scope = std::unique_ptr<T>;

        template<typename T, typename ... Args>
        constexpr scope<T> create_scoped(Args&& ... _args) { return std::make_unique<T>(std::forward<Args>(_args)...); }

        template<typename T>
        using ref = std::shared_ptr<T>;

        template<typename T, typename ... Args>
        constexpr ref<T> create_ref(Args&& ... _args) { return std::make_shared<T>(std::forward<Args>(_args)...); }
    }
}
