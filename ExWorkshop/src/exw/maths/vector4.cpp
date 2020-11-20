// ;
#include "expch.h"
#include "vector4.h"

#include "vector2.h"
#include "vector3.h"

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

        vector4::vector4(const vector2& _vct)
            : x(_vct.x), y(_vct.y), z(0.0f), w(0.0f)
        {}

        vector4::vector4(const vector3& _vct)
            : x(_vct.x), y(_vct.y), z(_vct.z), w(0.0f)
        {}

        vector4::vector4(const vector4& _vct)
            : raw(_vct.raw)
        {}

        vector4::vector4(const glm::vec4& _raw)
            : raw(_raw)
        {}

        bool vector4::operator==(const vector3& _other)
        {
            return (this->x == _other.x && this->y == _other.y && this->z == _other.z);
        }

        bool operator==(const vector4& _vct1, const vector3& _vct2)
        {
            return (_vct1.x == _vct2.x && _vct1.y == _vct2.y && _vct1.z == _vct2.z);
        }
    }
}
