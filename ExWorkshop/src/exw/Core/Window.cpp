/*  Window.cpp
*   Version: 1.1 (2022.07.23)
*
*   Contributor
*       Arime-chan
*/
#include "exwpch.h"
#include "Window.h"

#include "exw\Utils\Logger.h"

#ifdef EXW_PLATFORM_WINDOWS
#include "Platform\Windows\WindowsGLFWWindow.h"
#endif

namespace exw
{
    refs::Scoped<Window> Window::create(const WindowProperties& _props)
    {
        #ifdef EXW_PLATFORM_WINDOWS
        return refs::create_scoped<WindowsGLFWWindow>(_props);
        #else
        EXW_ASSERT_CORE(false, "Could not create Window on unsupported platform.");
        return nullptr;
        #endif
    }

}
