/*  Common.h
*   Version: 1.3 (2022.07.23)
*
*   Contributor
*       Arime-chan
*/
#pragma once

#include <memory>

#pragma region Platform Detection
#ifdef _WIN32
    #ifdef _WIN64
        #define EXW_PLATFORM_WINDOWS
    #else
        #error "x86 builds are not supported."
    #endif
#elif defined(__APPLE__) || defined(__MACH__)
    #include <TargetConditionals.h>
    /*  TARGET_OS_MAC exists on all the platforms so we must check all of them (in this order)
    * to ensure that we're running on MAC  and not some other Apple platform
    */
    #if TARGET_IPHONE_SIMULATOR == 1
        #error "iOS simulator is not supported."
    #elif TARGET_OS_IPHONE == 1
        #define EXW_PLATFORM_IOS
        #error "iOS is not supported."
    #elif TARGET_OS_MAC == 1
        #define EXW_PLATFORM_MACOS
        #error "MacOS is not supported."
    #else
        #error "Unknown Apple platform is not supported."
    #endif
#elif defined(__ANDROID__)
    // we have to check __ANDROID__ before __linux__ since android is based on the linux kernel, it has __linux__ defined;
    #define EXW_PLATFORM_ANDROID
    #error "Android is not supported."
#elif defined(__linux__)
    #define EXW_PLATFORM_LINUX
    #error "Linux is not supported."
#else
    #error "Unknown platform is not supported."
#endif
#pragma endregion

#define IS_FLAG_SET(_flags, _flag)      (_flags & _flag) != 0

#define EXW_EXPAND(x)           x
#define EXW_STRINGIFY(x)        #x

#pragma region Assertion/Debug
#ifdef EXW_DBG
    #if defined(EXW_PLATFORM_WINDOWS)
        #define EXW_DEBUGBREAK() __debugbreak()
    #elif defined(EXW_PLATFORM_LINUX)
        #include <signal.h>
        #define EXW_DEBUGBREAK() raise(SIGTRAP)
    #else
        #error "This platform doesn't support debugbreak."
    #endif
    #define EXW_ENABLE_ASSERT
#else
    #define EXW_DEBUGBREAK()
#endif

#define EXW_INTERNAL_ASSERT_IMPL(_type, _check, _msg, ...)  { if (!(_check)) {EXW_LOG##_type##ERROR(_msg, __VA_ARGS__); EXW_DEBUGBREAK(); } }
#define EXW_INTERNAL_ASSERT_WITH_MSG(_type, _check, ...)    EXW_INTERNAL_ASSERT_IMPL(_type, _check, "Assertion failed: {0}", __VA_ARGS__)
#define EXW_INTERNAL_ASSERT_NO_MSG(_type, _check)                                                                                                                       \
    EXW_INTERNAL_ASSERT_IMPL(_type, _check, "Assertion failed: {0} ({1} @{2})", EXW_STRINGIFY(_check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

#define EXW_INTERNAL_ASSERT_GET_MACRO_NAME(_arg1, _arg2, _macro, ...)   _macro
#define EXW_INTERNAL_ASSERT_GET_MACRO(...)   EXW_EXPAND(EXW_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, EXW_INTERNAL_ASSERT_WITH_MSG, EXW_INTERNAL_ASSERT_NO_MSG))

#define EXW_ASSERT_CORE(...)    EXW_EXPAND(EXW_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__))
#define EXW_ASSERT(...)         EXW_EXPAND(EXW_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__))
#pragma endregion


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
