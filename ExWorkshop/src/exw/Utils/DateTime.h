/*  DateTime.h
*   Version: 1.0 (2022.07.25)
*
*   Contributor
*       Arime-chan
*/
#pragma once

#include <GLFW\glfw3.h>

namespace exw
{
    namespace utils
    {
        class Time
        {
        public:
            static float get_time_as_float()
            {
                return (float)glfwGetTime();
            }
        };

    }
}
