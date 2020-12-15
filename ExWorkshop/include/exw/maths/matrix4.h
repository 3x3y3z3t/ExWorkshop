// ;
#pragma once

#include "vector4.h"
#include <glm\mat4x4.hpp>

namespace exw
{
    namespace maths
    {
        struct matrix4
        {
            union
            {
                glm::mat4 raw;
                struct
                {
                    maths::vector4 columns[4];
                };
            };

            matrix4(float _identity = 0.0f);
            matrix4(const matrix4& _matrix);
            matrix4(const glm::mat4& _raw);

            const matrix4& invert();

            const vector4& operator[](uint8_t _index);

            friend matrix4 operator*(const matrix4& _mat1, const matrix4& _mat2);
            friend vector4 operator*(const matrix4& _mat1, const vector4& _vec1);
        };
    }
}

#include "matrix4.inl"
