// ;
#include "expch.h"
#include "exw\utils\PlatformUtils.h"

#include "exw\Application.h"

#include <commdlg.h>
#include <GLFW\glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW\glfw3native.h>

namespace exw
{
    namespace utils
    {
        std::string FileDialogs::open_file(const char* _filter)
        {
            OPENFILENAMEA ofn;
            ZeroMemory(&ofn, sizeof(OPENFILENAME));

            CHAR buffer[256];
            if (GetCurrentDirectoryA(256, buffer) > 0UL)
            {
                ofn.lpstrInitialDir = buffer;
            }

            CHAR szFile[260] = { 0 };
            
            ofn.lStructSize = sizeof(OPENFILENAME);
            ofn.hwndOwner = glfwGetWin32Window((GLFWwindow*)Application::get().get_window().get_native_window());
            ofn.lpstrFile = szFile;
            ofn.nMaxFile = sizeof(szFile);
            ofn.lpstrFilter = _filter;
            ofn.nFilterIndex = 1UL;
            ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
            if (GetOpenFileNameA(&ofn) == TRUE)
            {
                return ofn.lpstrFile;
            }

            return std::string();
        }

        std::string FileDialogs::save_file(const char* _filter)
        {
            OPENFILENAMEA ofn;
            ZeroMemory(&ofn, sizeof(OPENFILENAME));

            CHAR buffer[256];
            if (GetCurrentDirectoryA(256, buffer) > 0UL)
            {
                ofn.lpstrInitialDir = buffer;
            }

            CHAR szFile[260] = { 0 };

            ofn.lStructSize = sizeof(OPENFILENAME);
            ofn.hwndOwner = glfwGetWin32Window((GLFWwindow*)Application::get().get_window().get_native_window());
            ofn.lpstrFile = szFile;
            ofn.nMaxFile = sizeof(szFile);
            ofn.lpstrFilter = _filter;
            ofn.nFilterIndex = 1UL;
            ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
            if (GetSaveFileNameA(&ofn) == TRUE)
            {
                return ofn.lpstrFile;
            }

            return std::string();
        }
    }
}
