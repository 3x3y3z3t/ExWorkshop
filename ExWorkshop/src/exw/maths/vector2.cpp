// ;
#include "expch.h"
#include "exw\maths\vector2.h"

#include "exw\maths\vector3.h"
#include "exw\maths\vector4.h"

namespace exw
{
    namespace maths
    {
        vector2::vector2(const vector3& _vct)
            : x(_vct.x), y(_vct.y)
        {}

        vector2::vector2(const vector4& _vct)
            : x(_vct.x), y(_vct.y)
        {}

        std::string vector2::to_string(bool _longString) const
        {
            std::stringstream ss;
            if (_longString)
                ss << "vector2";
            ss << "(" << x << ", " << y << ")";
            return ss.str();
        }
    }
}
