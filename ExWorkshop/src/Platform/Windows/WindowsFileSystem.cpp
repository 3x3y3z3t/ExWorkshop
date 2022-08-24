/*  WindowFileSystem.cpp
*   Version: 1.0 (2022.07.25)
*
*   Contributor
*       Arime-chan
*/
#pragma once
#include "exwpch.h"
#include "exw\utils\FileSystem.h"

#include "exw\core\Application.h"

#include <commdlg.h> // include here because commdlg.h conflicted with includes in spdlog.h
#include <GLFW\glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

namespace exw
{
    namespace utils
    {
        std::string FileDialogs::open_file(const char* _filter)
        {
            OPENFILENAMEA ofn;
            ZeroMemory(&ofn, sizeof(OPENFILENAME));

            CHAR szFile[260] = { 0 };
            CHAR currentDir[256] = { 0 };

            ofn.lStructSize = sizeof(OPENFILENAME);
            ofn.hwndOwner = glfwGetWin32Window((GLFWwindow*)Application::get().get_window().get_native_window());
            ofn.lpstrFile = szFile;
            ofn.nMaxFile = sizeof(szFile);
            if (GetCurrentDirectoryA(256, currentDir))
                ofn.lpstrInitialDir = currentDir;
            ofn.lpstrFilter = _filter;
            ofn.nFilterIndex = 1;
            ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

            if (GetOpenFileNameA(&ofn) == TRUE)
                return ofn.lpstrFile;

            return std::string();
        }

        std::string FileDialogs::save_file(const char* _filter)
        {
            OPENFILENAMEA ofn;
            ZeroMemory(&ofn, sizeof(OPENFILENAME));

            CHAR szFile[260] = { 0 };
            CHAR currentDir[256] = { 0 };

            ofn.lStructSize = sizeof(OPENFILENAME);
            ofn.hwndOwner = glfwGetWin32Window((GLFWwindow*)Application::get().get_window().get_native_window());
            ofn.lpstrFile = szFile;
            ofn.nMaxFile = sizeof(szFile);
            if (GetCurrentDirectoryA(256, currentDir))
                ofn.lpstrInitialDir = currentDir;
            ofn.lpstrFilter = _filter;
            ofn.nFilterIndex = 1;
            ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
            ofn.lpstrDefExt = strchr(_filter, '\0') + 1;

            if (GetSaveFileNameA(&ofn) == TRUE)
                return ofn.lpstrFile;

            return std::string();
        }
    }
}
