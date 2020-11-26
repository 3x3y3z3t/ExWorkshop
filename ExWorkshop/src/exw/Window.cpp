// ;
#include "expch.h"
#include "exw\Window.h"

#ifdef EXW_PLATFORM_WINDOWS
#include "platform\windows\WindowsWindow.h"
#endif

namespace exw
{
    refs::scope<Window> Window::create(const WindowProperties& _properties)
    {
        #ifdef EXW_PLATFORM_WINDOWS
            return refs::create_scoped<WindowsWindow>(_properties);
        #else
            EXW_ASSERT(false, "Unknown platform.");
            return nullptr;
        #endif
    }
}
