// ;
#include "expch.h"
#include "vector3.h"

#include "vector2.h"
#include "vector4.h"

namespace exw
{
    namespace maths
    {
        vector3::vector3()
            : x(0.0f), y(0.0f), z(0.0f)
        {}

        vector3::vector3(float _x, float _y, float _z)
            : x(_x), y(_y), z(_z)
        {}

        vector3::vector3(float _scalar)
            : x(_scalar), y(_scalar), z(_scalar)
        {}

        vector3::vector3(const vector2& _vct)
            : x(_vct.x), y(_vct.y), z(0.0f)
        {}

        vector3::vector3(const vector3& _vct)
            : x(_vct.x), y(_vct.y), z(_vct.z)
        {}

        vector3::vector3(const vector4& _vct)
            : x(_vct.x), y(_vct.y), z(_vct.z)
        {}

        vector3::vector3(const glm::vec3& _raw)
            : raw(_raw)
        {}
    }
}
