// ;
#include "expch.h"
#include "exw\maths\vector3.h"

#include "exw\maths\vector2.h"
#include "exw\maths\vector4.h"

namespace exw
{
    namespace maths
    {
        vector3::vector3(const vector2& _vct)
            : x(_vct.x), y(_vct.y), z(0.0f)
        {}

        vector3::vector3(const vector4& _vct)
            : x(_vct.x), y(_vct.y), z(_vct.z)
        {}

        bool vector3::operator==(const vector4& _other)
        {
            return (this->x == _other.x && this->y == _other.y && this->z == _other.z);
        }

        std::string vector3::to_string(bool _longString) const
        {
            // TODO: consider using fmt;
            std::stringstream ss;
            if (_longString)
                ss << "vector3";
            ss << "(" << x << ", " << y << ", " << z << ")";
            return ss.str();
        }

        bool operator==(const vector3& _vct1, const vector4& _vct2)
        {
            return (_vct1.x == _vct2.x && _vct1.y == _vct2.y && _vct1.z == _vct2.z);
        }
    }
}
