// ;
#include "expch.h"
#include "matrix4.h"

namespace exw
{
    namespace maths
    {
        matrix4::matrix4(float _identity)
            : raw(_identity)
        {}

        matrix4::matrix4(const matrix4& _matrix)
            : raw(_matrix.raw)
        {}

        matrix4::matrix4(const glm::mat4& _raw)
            : raw(_raw)
        {}

        const matrix4& matrix4::invert()
        {
            raw = glm::inverse(raw);
            return *this;
        }

        matrix4 matrix4::inverse(const matrix4& _mat)
        {
            return matrix4(glm::inverse(_mat.raw));
        }

        matrix4 operator*(const matrix4& _mat1, const matrix4& _mat2)
        {
            return matrix4(_mat1.raw * _mat2.raw);
        }

        vector4 operator*(const matrix4& _mat1, const vector4& _vec1)
        {
            return vector4(_mat1.raw * _vec1.raw);
        }
    }
}
