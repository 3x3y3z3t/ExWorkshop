// ;
#pragma once
//#include "expch.h"

#include <memory>

#pragma region Platform Detection

#if defined(_WIN32)
    #ifdef _WIN64
        #define EXW_PLATFORM_WINDOWS
    #else
        #error "Windows x86 build is not supported"
    #endif
#elif defined(__APPLE__) || defined(__MACH__)
    #include <TargetConditionals.h>
    /* TARGET_OS_MAC exists on all the platforms so we must check all of them (in
     * this order) to ensure that we're running on MAC and not some other Apple
     * platform.
     */
    #if TARGET_IPHONE_SIMULATOR == 1
        #error "IOS simulator build is not supported"
    #elif TARGET_OS_IPHONE == 1
        #define EXW_PLATFORM_IOS
        #error "IOS build is not supported"
    #elif TARGET_OS_MAC == 1
        #define EXW_PLATFORM_MACOS
        #error "MacOS build is not supported"
    #else
        #error "Unknown Apple platform"
    #endif
/* We also have to check __ANDROID__ before __linux__ since android is based on
 * the linux kernel so it has __linux__ defined
 */
#elif defined(__ANDROID__)
    #define EXW_PLATFORM_ANDROID
    #error "Android build is not supported"
#elif defined(__linux__)
    #define EXW_PLATFORM_LINUX
    #error "Linux build is not supported"
#else
    #error "Unknown platform"
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
    #define EXW_ENABLE_ASSERTS
#else
    #define EXW_DEBUGBREAK() 
#endif

#define EXW_EXPAND(_x)                      _x
#define EXW_STRINGIFY(_x)                   #_x

#define BIT(_x)                             (1 << _x)
#define BIT_AT(_integer, _pos)              ((_integer >> _pos) % 2)
#define TEST(_integer, _pos)                (BIT_AT(_integer, _pos) != 0)

#define IS_FLAG_SET(_flags, _flag)          ((_flags & _flag) != 0)

#define EXW_BIND_EVENT_FUNCTION(_func)      [this](auto&&... _args) -> decltype(auto) { return this->_func(std::forward<decltype(_args)>(_args)...); }

#define this_typeid_name()                  typeid(*this).name()

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

#include "exw\utils\Log.h"

#ifdef EXW_ENABLE_ASSERTS

    #pragma region Assert Utils
    /////---------------------------------------------------------------------------
    /* Alteratively we could use the same "default" message for both "WITH_MSG" and
     * "NO_MSG" and provide support for custom formatting by concatenating the
     * formatting string instead of having the format inside the default message.
     */
    #define EXW_INTERNAL_ASSERT_IMPL(_type, _check, _msg, ...)              { if(!(_check)) { EXW_LOG##_type##ERROR(_msg, __VA_ARGS__); EXW_DEBUGBREAK(); } }

    #define EXW_INTERNAL_ASSERT_WITH_MSG(_type, _check, ...)                EXW_INTERNAL_ASSERT_IMPL(_type, _check, "Assertion failed: {0}", __VA_ARGS__)
    #define EXW_INTERNAL_ASSERT_NO_MSG(_type, _check)                       EXW_INTERNAL_ASSERT_IMPL(_type, _check, "Assertion '{0}' failed at {1}:{2}", EXW_STRINGIFY(_check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

    #define EXW_INTERNAL_ASSERT_GET_MACRO_NAME(_arg1, _arg2, _macro, ...)   _macro
    #define EXW_INTERNAL_ASSERT_GET_MACRO(...)                              EXW_EXPAND(EXW_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, EXW_INTERNAL_ASSERT_WITH_MSG, EXW_INTERNAL_ASSERT_NO_MSG))
    #pragma endregion

    // Currently accepts at least the condition and one additional parameter (the message) being optional
    #ifdef EXW_CORE_LIB
        //#define EXW_ASSERT(...)    EXW_EXPAND(EXW_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__))
        #define EXW_ASSERT(...)     EXW_EXPAND(EXW_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__))
    #else
        #define EXW_ASSERT(...)     EXW_EXPAND(EXW_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__))
    #endif
#else
    #define EXW_ASSERT(...)
#endif
