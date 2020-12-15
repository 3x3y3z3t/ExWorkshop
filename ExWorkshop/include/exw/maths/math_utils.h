// temporary name;
#pragma once

#include "matrix4.h"
#include "vector2.h"
#include "vector3.h"
#include "vector4.h"
#include "quaternion.h"

namespace exw
{
    namespace maths
    {
        extern constexpr float Pi = (float)3.1415926535897932;
        extern constexpr float Pi_over_180d = Pi / 180.0f;
        extern constexpr float Pi_divides_180d = 180.0f / Pi;

        template <typename T>
        constexpr T sign(T _t);

        template <typename T>
        constexpr T min(T _t1, T _t2);

        template <typename T>
        constexpr T max(T _t1, T _t2);

        template <typename T>
        constexpr T to_radians(T _degrees);

        template <typename T>
        constexpr T to_degrees(T _radians);

        constexpr float wrap_angle_deg(float _deg);
        constexpr float wrap_angle_rad(float _rad);

        float sin(float _radians);
        float cos(float _radians);
        float atan(float _y, float _x);

        float sqrt(float _value);
        float pow(float _base, float _power);

        matrix4 inverse(const matrix4& _mat);
        matrix4 translate(const matrix4& _mat, const vector3& _axis);
        matrix4 rotate(const matrix4& _mat, float _angle, const vector3& _axis);
        #ifdef EXW_ENABLE_EXPERIMENTAL
        vector3 rotate(const quaternion& _quat, const vector3& _axis);
        #endif
        matrix4 scale(const matrix4& _mat, const vector3& _axis);

        matrix4 orthographic(float _left, float _right, float _bottom, float _top, float _near, float _far);
        matrix4 perspective(float _verticalFov, float _aspectRatio, float _near, float _far);
    }
}

#include "math_utils.inl"
#include "math_utils_matrix.inl"
