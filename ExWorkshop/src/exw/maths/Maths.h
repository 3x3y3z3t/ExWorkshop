/*  Maths.h
*   Version: 1.1 (2022.08.27)
*
*   Contributor
*       Arime-chan
*/
#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>

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
