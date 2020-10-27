// ;
#include "expch.h"
#include "vector2.h"

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

        vector2::vector2(const glm::vec2& _raw)
            : raw(_raw)
        {}

        vector2 operator+(const vector2& _vct1, const vector2& _vct2)
        {
            return vector2(_vct1.raw + _vct2.raw);
        }


    }
}
