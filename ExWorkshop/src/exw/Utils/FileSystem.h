/*  FileSystem.h
*   Version: 1.0 (2022.07.25)
*
*   Contributor
*       Arime-chan
*/
#pragma once
#include "exwpch.h"

namespace exw
{
    namespace utils
    {
        class FileDialogs
        {
        public:
            static std::string open_file(const char* _filter);
            static std::string save_file(const char* _filter);
        };

    }
}
