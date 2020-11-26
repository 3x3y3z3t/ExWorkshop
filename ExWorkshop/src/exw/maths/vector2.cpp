// ;
#include "expch.h"
#include "exw\maths\vector2.h"

#include "exw\maths\vector3.h"
#include "exw\maths\vector4.h"

namespace exw
{
    namespace maths
    {
        vector2::vector2()
            : x(0.0f), y(0.0f)
        {}

        vector2::vector2(float _x, float _y)
            : x(_x), y(_y)
        {}

        vector2::vector2(float _scalar)
            : x(_scalar), y(_scalar)
        {}

        vector2::vector2(const vector2& _vct)
            : x(_vct.x), y(_vct.y)
        {}

        vector2::vector2(const vector3& _vct)
            : x(_vct.x), y(_vct.y)
        {}

        vector2::vector2(const vector4& _vct)
            : x(_vct.x), y(_vct.y)
        {}

        vector2::vector2(const glm::vec2& _raw)
            : raw(_raw)
        {}
    }
}
