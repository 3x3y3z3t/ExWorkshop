// temporary name;
#pragma once

#include "matrix4.h"
#include "vector3.h"

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
//#include <glm\gtx\transform.hpp>

namespace exw::maths
{
    namespace
    {
        constexpr float Pi = (float)3.1415926535897932;
        constexpr float Pi_over_180d = Pi / 180.0f;
        constexpr float Pi_divides_180d = 180.0f / Pi;

        // ===== Degrees to Radians =====
        template <typename T>
        T to_radians(T _degrees) { return _degrees * Pi_over_180d; }

        // ===== Radians to Degrees =====
        template <typename T>
        T to_degrees(T _radians) { return _radians * Pi_divides_180d; }
        
        float sin(float _radians) { return glm::sin(_radians); }
        float cos(float _radians) { return glm::cos(_radians); }
        float atan(float _y, float _x) { return glm::atan(_y, _x); }

        float sqrt(float _value) { return glm::sqrt(_value); }
        float pow(float _base, float _power) { return glm::pow(_base, _power); }

        static float wrap_angle_deg(float _deg)
        {
            if (_deg > 180.0f) return _deg - 360.0f;
            if (_deg < -179.0f) return _deg + 360.0f;
            return _deg;
        }
        template <typename T>
        T sign(T _t) { if (_t > 0) return 1; if (_t < 0) return -1; return 0; }

        matrix4 translate(const matrix4& _mat, const vector3& _axis)
        {
            return matrix4(glm::translate(_mat.raw, _axis.raw));
        }

        matrix4 rotate(const matrix4& _mat, float _angle, const vector3& _axis)
        {
            return matrix4(glm::rotate(_mat.raw, _angle, _axis.raw));
        }

        matrix4 scale(const matrix4& _mat, const vector3& _axis)
        {
            return matrix4(glm::scale(_mat.raw, _axis.raw));
        }

        matrix4 orthographic(float _left, float _right, float _bottom, float _top, float _near, float _far)
        {
            return matrix4(glm::ortho(_left, _right, _bottom, _top, _near, _far));
        }

        matrix4 perspective(float _verticalFov, float _aspectRatio, float _near, float _far)
        {
            return matrix4(glm::perspective(_verticalFov, _aspectRatio, _near, _far));
        }
    }
}
