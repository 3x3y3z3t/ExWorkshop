// ;
#include "expch.h"
#include "vector4.h"

namespace exw
{
    namespace maths
    {
        vector4::vector4()
            : x(0.0f), y(0.0f), z(0.0f), w(0.0f)
        {}

        vector4::vector4(float _x, float _y, float _z, float _w)
            : x(_x), y(_y), z(_z), w(_w)
        {}

        vector4::vector4(float _scalar)
            : x(_scalar), y(_scalar), z(_scalar), w(_scalar)
        {}

        vector4::vector4(const vector4& _vct)
            : raw(_vct.raw)
        {}

        vector4::vector4(const glm::vec4& _raw)
            : raw(_raw)
        {}

        vector4 operator+(const vector4& _vct1, const vector4& _vct2)
        {
            return vector4(_vct1.raw + _vct2.raw);
        }
    }
}
