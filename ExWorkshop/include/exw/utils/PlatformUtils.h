// ;
#pragma once

#include "expch.h"

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
