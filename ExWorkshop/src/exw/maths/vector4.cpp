// ;
#include "expch.h"
#include "exw\maths\vector4.h"

#include "exw\maths\vector2.h"
#include "exw\maths\vector3.h"

namespace exw
{
    namespace maths
    {
        vector4::vector4(const vector2& _vct)
            : x(_vct.x), y(_vct.y), z(0.0f), w(0.0f)
        {}

        vector4::vector4(const vector3& _vct)
            : x(_vct.x), y(_vct.y), z(_vct.z), w(0.0f)
        {}
        bool vector4::operator==(const vector3& _other)
        {
            return (this->x == _other.x && this->y == _other.y && this->z == _other.z);
        }

        std::string vector4::to_string(bool _longString) const
        {
            std::stringstream ss;
            if (_longString)
                ss << "vector4";
            ss << "(" << x << ", " << y << ", " << z << ", " << w << ")";
            return ss.str();
        }

        bool operator==(const vector4& _vct1, const vector3& _vct2)
        {
            return (_vct1.x == _vct2.x && _vct1.y == _vct2.y && _vct1.z == _vct2.z);
        }
    }
}
