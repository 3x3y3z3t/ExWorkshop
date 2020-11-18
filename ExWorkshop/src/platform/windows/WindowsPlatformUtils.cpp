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
            CHAR currentDir[256] = { 0 };
            GetCurrentDirectoryA(256, currentDir);
            CHAR szFile[260] = { 0 };

            OPENFILENAMEA ofn;
            ZeroMemory(&ofn, sizeof(OPENFILENAME));

            ofn.lStructSize = sizeof(OPENFILENAME);
            ofn.hwndOwner = glfwGetWin32Window((GLFWwindow*)Application::get().get_window().get_native_window());
            ofn.lpstrFilter = _filter;
            ofn.nFilterIndex = 1UL;
            ofn.lpstrFile = szFile;
            ofn.nMaxFile = sizeof(szFile);
            ofn.lpstrInitialDir = currentDir;
            //ofn.lpstrTitle = NULL;
            ofn.Flags = OFN_FILEMUSTEXIST
                | OFN_NOCHANGEDIR
                | OFN_OVERWRITEPROMPT
                | OFN_PATHMUSTEXIST;
            ofn.lpstrDefExt = std::strchr(_filter, '\0') + 1;

            if (GetOpenFileNameA(&ofn) == TRUE)
            {
                return ofn.lpstrFile;
            }

            return std::string();
        }

        std::string FileDialogs::save_file(const char* _filter)
        {
            CHAR currentDir[256] = { 0 };
            GetCurrentDirectoryA(256, currentDir);
            CHAR szFile[260] = { 0 };

            OPENFILENAMEA ofn;
            ZeroMemory(&ofn, sizeof(OPENFILENAME));

            ofn.lStructSize = sizeof(OPENFILENAME);
            ofn.hwndOwner = glfwGetWin32Window((GLFWwindow*)Application::get().get_window().get_native_window());
            ofn.lpstrFilter = _filter;
            ofn.nFilterIndex = 1UL;
            ofn.lpstrFile = szFile;
            ofn.nMaxFile = sizeof(szFile);
            ofn.lpstrInitialDir = currentDir;
            //ofn.lpstrTitle = NULL;
            ofn.Flags = OFN_NOCHANGEDIR
                | OFN_OVERWRITEPROMPT
                | OFN_PATHMUSTEXIST;
            ofn.lpstrDefExt = std::strchr(_filter, '\0') + 1;

            if (GetSaveFileNameA(&ofn) == TRUE)
            {
                return ofn.lpstrFile;
            }

            return std::string();
        }
    }
}
