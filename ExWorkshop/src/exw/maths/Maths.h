/*  Maths.h
*   Version: 1.0 (2022.07.22)
*
*   Contributor
*       Arime-chan
*/
#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <glm\glm.hpp>

namespace exw
{
    namespace maths
    {
        using vector2 = glm::vec2;
        using vector3 = glm::vec3;
        using vector4 = glm::vec4;

        using matrix3 = glm::mat3;
        using matrix4 = glm::mat4;
    }
}
