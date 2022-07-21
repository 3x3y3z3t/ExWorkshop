/*  Window.cpp
*   Version: 1.0 (2022.07.21)
*
*   Contributor
*       Arime-chan
*/
#include "exwpch.h"
#include "Window.h"

#include "ExWorkshop\Utils\Logger.h"

#ifdef EXW_PLATFORM_WINDOW
#include "Platform\Windows\WindowsGLFWWindow.h"
#endif // EXW_PLATFORM_WINDOW

namespace exw
{
    refs::Scoped<Window> Window::create(const WindowProperties& _props)
    {
        #ifdef EXW_PLATFORM_WINDOW
        return refs::create_scoped<WindowsGLFWWindow>(_props);
        #else
        EXW_CORE_LOG_CRITICAL("Could not create Window on unsupported platform."); // TODO: assert;
        return nullptr;
        #endif // EXW_PLATFORM_WINDOW
    }

}
